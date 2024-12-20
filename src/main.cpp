#include <Arduino.h>

#include <api/network.h>
#include <api/server.h>
#include <api/ntime.h>

#include <core/setting.h>
#include <core/cron.h>

void setup() 
{
    Serial.begin(9600);
    Serial.println();

    if (!Network::load("kiewdesktop", "abcde1234")) {
        while (true) {}
    }

    if (!NetworkTime::load()) {
        while (true) {}
    }

    Server::load();
}

void loop() 
{
    Server::tick();

    CronJob::tick();
}
