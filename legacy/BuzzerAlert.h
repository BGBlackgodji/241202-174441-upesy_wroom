#include "esp32-hal-gpio.h"

bool buzzerTicker = false;
bool buzzerAlarm = false;
bool buzzerAlarmOnetime = false;
int16_t buzzerAlarmTime = 20;
bool buzzerOnetime = false;
void buzzerTimer() {
  static unsigned long premillis = 0;
  static unsigned long premillisTimer = 0;
  if (buzzerTicker == true) {
    premillis = millis();
    buzzerOnetime = true;
    buzzerTicker = false;
  }
  if (buzzerTicker == false && buzzerOnetime) {
    if (millis() - premillis <= 500) {
      //   playerPaddleTone();
      digitalWrite(BUZZ, HIGH);
    } else {
      //   wallTone();
      digitalWrite(BUZZ, LOW);
      buzzerOnetime = false;
    }
  }

  if (buzzerAlarm == true) {
    premillisTimer = millis();
    buzzerAlarmOnetime = true;
    buzzerAlarm = false;
  }

  if (buzzerAlarm == false && buzzerAlarmOnetime) {
    static unsigned long previousMillis = 0;
    if (millis() - premillisTimer <= (buzzerAlarmTime * 1000)) {
      if (millis() - previousMillis >= 300) {
        digitalWrite(BUZZ, !digitalRead(BUZZ));
        previousMillis = millis();
      }
    } else {
      digitalWrite(BUZZ, LOW);
      buzzerAlarmOnetime = false;
    }
  }
}

void sendBuzzerInterval(int16_t interval) {
  if (buzzerAlarmOnetime == false && buzzerAlarm == false) {
    buzzerAlarmTime = interval;
    buzzerAlarm = true;
  }
}

void sendBuzzer() {
  if (buzzerOnetime == false) {
    buzzerTicker = true;
  }
}