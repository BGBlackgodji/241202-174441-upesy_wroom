#ifndef BOX_H
#define BOX_H

#include <string>
#include <ESP32Servo.h>

using namespace std;

class Box {
public:
    string name;
    Servo servo;

    static int _servoPort;

    Box();
    Box(int servoPort);
    static Box create(int servoPort, string pillName, string cronString);

    void open();
    void openInTime(int timeout = 10 * 1000);

    void close();
};

#endif
