#include <Arduino.h>

#include <api/wifi.h>
#include <api/server.h>

#include <core/setting.h>

void setup() 
{
    Network::connect("KIEW_DESKTOP", "Nk5gmiSsgbGHBZxIeqJ5eg");

    serverSetup();
}

void loop() 
{
    serverLoop();
}
