#include <Arduino.h>

#include <port.cpp>

void setup() 
{
    Serial.begin(9600);
}

void loop() 
{
    Serial.println(SPEAKER);
}