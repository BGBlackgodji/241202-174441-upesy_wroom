#include "audio.h"

SoftwareSerial Audio::swSerial;
DFRobotDFPlayerMini Audio::player;

int Audio::timeout = 10 * 1000;

bool Audio::load(int rxPort, int txPort) {
    // pinMode(rxPort, INPUT);
    // pinMode(txPort, OUTPUT);

    int band = 9600;
    EspSoftwareSerial::Config config = SWSERIAL_8N1;
    Audio::swSerial.begin(band, config, rxPort, txPort);

    Audio::player.begin(Audio::swSerial);

    if(!Audio::player.waitAvailable(Audio::timeout)) {
        Serial.println("audio timeout");
        return false;
    }

    Audio::pause();

    return true;
}

void Audio::play(int folderNum, int fileNum) {
    Audio::player.start();

    Audio::player.playFolder(folderNum, fileNum);
}

void Audio::pause() {
    Audio::player.stop();
}