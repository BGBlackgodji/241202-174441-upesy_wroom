#include "box.h"

int Box::_servoPort = -1;

Box::Box() {}

Box::Box(int servoPort) {
    _servoPort = servoPort;

    servo = Servo();
    servo.attach(servoPort);

    close();
}

Box Box::create(int servoPort, string pillName, string cronString) {
    Box box(servoPort);
    box.name = pillName;

    // Cron.create(
    //     const_cast<char *>(cronString.c_str()),
    //     []() {
    //         Box timeBox(Box::_servoPort);
    //         timeBox.onTime();
    //     },
    //     false
    // );

    return box;
}

void Box::open() {
    servo.write(90);
}

void Box::close() {
    servo.write(0);
}

void Box::onTime() {
    open();

    int delayTime = 1000;
    delay(delayTime);

    close();
}
