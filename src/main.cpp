#include <Arduino.h>

#include <api/wifi.h>
#include <api/server.h>

#include <core/setting.h>

void setup() 
{
    Serial.begin(9600);

    Network::connect("KIEW_DESKTOP", "Nk5gmiSsgbGHBZxIeqJ5eg");

    Serial.println(Network::GetIPv4().c_str());

    serverSetup();
}

void loop() 
{
    serverLoop();
}
