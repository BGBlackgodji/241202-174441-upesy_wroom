#include <Arduino.h>
#include <ESP32Servo.h>

#include <port.cpp>

Servo servo01;

void setup() 
{
    servo01.attach(25);
}

void loop() 
{
    servo01.write(0);
    servo01.write(90);
    servo01.write(0);
} 