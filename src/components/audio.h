#ifndef AUDIO_H
#define AUDIO_H

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

class Audio {
    private:
        static SoftwareSerial swSerial;
        static DFRobotDFPlayerMini player;

    public:
        static int timeout;

        /** 
         * @param rxPort reception
         * @param txPort transmission
         * 
         * @return is success
         */
        static bool load(int rxPort, int txPort);

        /**
         * SD_CARD\01\002.mp3
         */
        static void play(int folderNum, int fileNum);
        static void pause();
}; 

#endif