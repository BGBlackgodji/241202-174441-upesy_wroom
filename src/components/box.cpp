#include "box.h"

#include <core/cron.h>

int Box::_servoPort = -1;
int Box::timeout = 1000;

Box::Box() {}

Box::Box(int servoPort) {
    pinMode(servoPort, OUTPUT);

    servo = Servo();
    servo.attach(servoPort);

    Box::_servoPort = servoPort;

    close();
}

Box Box::create(int servoPort, string boxName, string cronString) {
    Box box(servoPort);
    box.name = boxName;

    CronJob::on(
        boxName,
        cronString,
        []() {
            Box timeBox(Box::_servoPort);
            timeBox.openInTime();
        }
    );

    return box;
}

void Box::open() {
    servo.write(90);

    delay(Box::timeout);
}

void Box::openInTime(int delayTime) {
    open();

    delay(delayTime);

    close();
}

void Box::close() {
    servo.write(0);

    delay(Box::timeout);
}
