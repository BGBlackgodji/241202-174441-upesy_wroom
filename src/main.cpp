#include <Arduino.h>
#include <ESP32Servo.h>

#include <api/wifi.h>
#include <api/server.h>

#include <core/setting.h>

Servo servo01;

void setup() 
{
    Network::connect("KIEW_DESKTOP", "Nk5gmiSsgbGHBZxIeqJ5eg");

    serverSetup();
}

void loop() 
{
    serverLoop();
}
