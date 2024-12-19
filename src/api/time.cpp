#include "time.h"

#include <string>

#include <Arduino.h>

using namespace std;

bool NetworkTime::load(int timeout) {
    int gmtOffset = +7 * 60 * 60; // Thailand (GMT+7)
    int daylightOffset = 0;
    string mainServer = "pool.ntp.org";
    string backupServer = "time.nist.gov";

    configTime(gmtOffset, daylightOffset, mainServer.c_str(), backupServer.c_str());

    while (true) {
        if (time(nullptr)) break;

        if (timeout <= 0) {
            Serial.println("ntp timeout");
            return false;
        }
        
        delay(1000);
        timeout -= 1000;
    }

    tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("can not get local time");
        return false;
    }

    return true;
}

tm NetworkTime::get() {
    tm timeinfo;

    getLocalTime(&timeinfo);

    int yearOffset = 1900;
    timeinfo.tm_year += yearOffset;

    int monthOffset = 1;
    timeinfo.tm_mon += monthOffset;

    return timeinfo;
}

void NetworkTime::print() {
    tm timeinfo = NetworkTime::get();

    Serial.print(timeinfo.tm_mday);
    Serial.print('/');
    Serial.print(timeinfo.tm_mon);
    Serial.print('/');
    Serial.print(timeinfo.tm_year);

    Serial.print(' ');

    Serial.print(timeinfo.tm_hour);
    Serial.print(':');
    Serial.print(timeinfo.tm_min);
    Serial.print(':');
    Serial.print(timeinfo.tm_sec);

    Serial.print(' ');

    Serial.print("week ");
    Serial.print(timeinfo.tm_wday);
    Serial.print('d');

    Serial.print('|');

    Serial.print("year ");
    Serial.print(timeinfo.tm_yday);
    Serial.print("d");

    Serial.println();
}