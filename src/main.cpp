#include <Arduino.h>

#include <api/network.h>
#include <api/rest.h>
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

    Rest::load();
}

void loop() 
{
    CronJob::tick();
    
    if (!Network::tick())
        return;

    Rest::tick();
}
