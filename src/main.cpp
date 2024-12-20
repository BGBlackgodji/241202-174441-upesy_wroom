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

    if (!Network::connect("kiewdesktop", "abcde1234")) {
        while (true) {}
    }

    Serial.println(Network::GetLocalIPv4().c_str());

    if (!NetworkTime::load()) {
        while (true) {}
    }

    NetworkTime::print();

    CronJob::on(
        "test",
        "*/2 * * * *",
        []() {
            Serial.println("HI!");
        }
    );

    serverSetup();
}

void loop() 
{
    CronJob::tick();

    serverLoop();
}
