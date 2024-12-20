#include "box.h"

#include <core/cron.h>

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

    CronJob::on(
        pillName,
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
}

void Box::openInTime(int timeout) {
    open();

    delay(timeout);

    close();
}

void Box::close() {
    servo.write(0);
}
