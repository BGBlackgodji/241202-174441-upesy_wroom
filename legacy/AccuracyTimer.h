uint32_t rtcUnixTimer = 0;
int32_t rtcGetYears = 2023;

uint8_t servonum01 = 0;
uint8_t servonum02 = 1;
uint8_t servonum03 = 2;
uint8_t servonum04 = 3;
uint8_t servonum05 = 4;
uint8_t servonum06 = 5;
uint8_t servonum07 = 6;
uint8_t servonum08 = 7;
uint8_t servonum09 = 8;
uint8_t servonum10 = 9;
uint8_t servonum11 = 10;
uint8_t servonum12 = 11;
uint8_t servonum13 = 12;
uint8_t servonum14 = 13;
uint8_t servonum15 = 14;

//LiquidCrystal_I2C lcd(0x27, 20, 4);
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
ThreeWire myWire(4, 5, 2);  // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);




void ConvertDate2Unix(int32_t timerDate[], unsigned long long int& TimerStart) {
  tmElements_t tmA;

  tmA.Year = rtcGetYears > 0 ? rtcGetYears - 1970 : timerDate[0] - 1970;  // Years since 1970
  tmA.Month = timerDate[1];
  tmA.Day = timerDate[2];
  tmA.Hour = timerDate[3];
  tmA.Minute = timerDate[4];
  tmA.Second = timerDate[5];

  TimerStart = makeTime(tmA);
  // Serial.println("Unix : " + String(TimerStart));
}


void printDateTime(const RtcDateTime& dt) {
  char datestring[20];

  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             dt.Day(),
             dt.Month(),
             dt.Year(),
             dt.Hour(),
             dt.Minute(),
             dt.Second());

             
  lcd2.setCursor(0, 0);
  lcd2.print("DATE");
  lcd2.setCursor(6, 0);
  lcd2.print(dt.Day());
  lcd2.print("/");
  lcd2.print(dt.Month());
  lcd2.print("/");
  lcd2.print(dt.Year());

  lcd2.setCursor(0, 1);
  lcd2.print("TIME");
  lcd2.setCursor(7, 1);
  lcd2.print(dt.Hour());
  lcd2.print(":");
  lcd2.print(dt.Minute());
  lcd2.print(":");
  lcd2.print(dt.Second());
  // Serial.println(datestring);
}

void Notify2Line() {
  sendBuzzerInterval(20);
  if (isConnected) {
    LINE.notifySticker(1, 2);
    LINE.notify("สวัสดีค่ะ");
    LINE.notify("ขณะนี้ได้เวลารับประทานยาแล้วค่ะ");
  }
}
void AccuracyTimers() {
  static unsigned long premillis = 0;
  if (millis() - premillis >= 500) {
    RtcDateTime now = Rtc.GetDateTime();
    printDateTime(now);
    rtcUnixTimer = now.Unix32Time();

    if (!now.IsValid()) {

      Serial.println("RTC lost confidence in the DateTime!");
    } else {
      static bool oneTicker[10];
      ConvertDate2Unix(ServoTimer[0].timerDate, ServoTimer[0].timerUnix);
      if (rtcUnixTimer > ServoTimer[0].timerUnix && rtcUnixTimer < ServoTimer[0].timerUnix + 10) {  // p11
        if (oneTicker[0] == false) {
          pwm.setPWM(10, 0, 525);
          delay(1000);
          pwm.setPWM(10, 0, 125);
          delay(1000);
          Notify2Line();
          oneTicker[0] = true;
        }
      } else {
        oneTicker[0] = false;
      }

      ConvertDate2Unix(ServoTimer[1].timerDate, ServoTimer[1].timerUnix);
      if (rtcUnixTimer > ServoTimer[1].timerUnix && rtcUnixTimer < ServoTimer[1].timerUnix + 10) {
        if (oneTicker[1] == false) {
          pwm.setPWM(11, 0, 525);
          delay(1000);
          pwm.setPWM(11, 0, 125);
          delay(1000);
          Notify2Line();
          oneTicker[1] = true;
        }
      } else {
        oneTicker[1] = false;
      }

      ConvertDate2Unix(ServoTimer[2].timerDate, ServoTimer[2].timerUnix);
      if (rtcUnixTimer > ServoTimer[2].timerUnix && rtcUnixTimer < ServoTimer[2].timerUnix + 10) {
        if (oneTicker[2] == false) {
          pwm.setPWM(12, 0, 525);
          delay(1000);
          pwm.setPWM(12, 0, 125);
          delay(1000);
          Notify2Line();
          oneTicker[2] = true;
        }
      } else {
        oneTicker[2] = false;
      }

      ConvertDate2Unix(ServoTimer[3].timerDate, ServoTimer[0].timerUnix);
      if (rtcUnixTimer > ServoTimer[3].timerUnix && rtcUnixTimer < ServoTimer[3].timerUnix + 10) {
        if (oneTicker[3] == false) {
          pwm.setPWM(13, 0, 525);
          delay(1000);
          pwm.setPWM(13, 0, 125);
          delay(1000);
          Notify2Line();
          oneTicker[3] = true;
        }

      } else {
        oneTicker[3] = false;
      }

      ConvertDate2Unix(ServoTimer[4].timerDate, ServoTimer[4].timerUnix);
      if (rtcUnixTimer > ServoTimer[4].timerUnix && rtcUnixTimer < ServoTimer[4].timerUnix + 10) {
        if (oneTicker[4] == false) {
          pwm.setPWM(14, 0, 525);
          delay(1000);
          pwm.setPWM(14, 0, 125);
          delay(1000);
          Notify2Line();
          oneTicker[4] = true;
        }
      } else {
        oneTicker[4] = false;
      }

      ConvertDate2Unix(ServoTimer[5].timerDate, ServoTimer[5].timerUnix);
      if (rtcUnixTimer > ServoTimer[5].timerUnix && rtcUnixTimer < ServoTimer[5].timerUnix + 10) {
        if (oneTicker[5] == false) {
          pwm.setPWM(5, 0, 525);
          delay(1000);
          pwm.setPWM(5, 0, 125);
          delay(1000);
          Notify2Line();
          oneTicker[5] = true;
        }

      } else {
        oneTicker[5] = false;
      }

      ConvertDate2Unix(ServoTimer[6].timerDate, ServoTimer[6].timerUnix);
      if (rtcUnixTimer > ServoTimer[6].timerUnix && rtcUnixTimer < ServoTimer[6].timerUnix + 10) {
        if (oneTicker[6] == false) {
          pwm.setPWM(6, 0, 525);
          delay(1000);
          pwm.setPWM(6, 0, 125);
          delay(1000);
          Notify2Line();
          oneTicker[6] = true;
        }
      } else {
        oneTicker[6] = false;
      }

      ConvertDate2Unix(ServoTimer[7].timerDate, ServoTimer[7].timerUnix);
      if (rtcUnixTimer > ServoTimer[7].timerUnix && rtcUnixTimer < ServoTimer[7].timerUnix + 10) {
        if (oneTicker[7] == false) {
          pwm.setPWM(7, 0, 525);
          delay(1000);
          pwm.setPWM(7, 0, 125);
          delay(1000);
          Notify2Line();
          oneTicker[7] = true;
        }
      } else {
        oneTicker[7] = false;
      }

      ConvertDate2Unix(ServoTimer[8].timerDate, ServoTimer[8].timerUnix);
      if (rtcUnixTimer > ServoTimer[8].timerUnix && rtcUnixTimer < ServoTimer[8].timerUnix + 10) {
        if (oneTicker[8] == false) {
          pwm.setPWM(8, 0, 525);
          delay(1000);
          pwm.setPWM(8, 0, 125);
          delay(1000);
          Notify2Line();
          oneTicker[8] = true;
        }
      } else {
        oneTicker[8] = false;
      }

      ConvertDate2Unix(ServoTimer[9].timerDate, ServoTimer[9].timerUnix);
      if (rtcUnixTimer > ServoTimer[9].timerUnix && rtcUnixTimer < ServoTimer[9].timerUnix + 10) {
        if (oneTicker[9] == false) {
          pwm.setPWM(9, 0, 525);
          delay(1000);
          pwm.setPWM(9, 0, 125);
          delay(1000);
          Notify2Line();
          oneTicker[9] = true;
        }
      } else {
        oneTicker[9] = false;
      }

      ConvertDate2Unix(ServoTimer[10].timerDate, ServoTimer[10].timerUnix);
      if (rtcUnixTimer > ServoTimer[10].timerUnix && rtcUnixTimer < ServoTimer[10].timerUnix + 10) {
        if (oneTicker[10] == false) {

          pwm.setPWM(0, 0, 525);
          delay(1000);
          pwm.setPWM(0, 0, 125);
          delay(1000);
          Notify2Line();
          oneTicker[10] = true;
        }
      } else {
        oneTicker[10] = false;
      }

      ConvertDate2Unix(ServoTimer[11].timerDate, ServoTimer[11].timerUnix);
      if (rtcUnixTimer > ServoTimer[11].timerUnix && rtcUnixTimer < ServoTimer[11].timerUnix + 10) {
        if (oneTicker[11] == false) {
          pwm.setPWM(1, 0, 525);
          delay(1000);
          pwm.setPWM(1, 0, 125);
          delay(1000);
          Notify2Line();
          oneTicker[11] = true;
        }
      } else {
        oneTicker[11] = false;
      }

      ConvertDate2Unix(ServoTimer[12].timerDate, ServoTimer[12].timerUnix);
      if (rtcUnixTimer > ServoTimer[12].timerUnix && rtcUnixTimer < ServoTimer[12].timerUnix + 10) {
        if (oneTicker[12] == false) {
          pwm.setPWM(2, 0, 525);
          delay(1000);
          pwm.setPWM(2, 0, 125);
          delay(1000);
          Notify2Line();
          oneTicker[12] = true;
        }
      } else {
        oneTicker[12] = false;
      }

      ConvertDate2Unix(ServoTimer[13].timerDate, ServoTimer[13].timerUnix);
      if (rtcUnixTimer > ServoTimer[13].timerUnix && rtcUnixTimer < ServoTimer[13].timerUnix + 10) {
        if (oneTicker[13] == false) {
          pwm.setPWM(3, 0, 525);
          delay(1000);
          pwm.setPWM(3, 0, 125);
          delay(1000);
          Notify2Line();
          oneTicker[13] = true;
        }
      } else {
        oneTicker[13] = false;
      }

      ConvertDate2Unix(ServoTimer[14].timerDate, ServoTimer[14].timerUnix);
      if (rtcUnixTimer > ServoTimer[14].timerUnix && rtcUnixTimer < ServoTimer[14].timerUnix + 10) {
        if (oneTicker[14] == false) {
          pwm.setPWM(4, 0, 525);
          delay(1000);
          pwm.setPWM(4, 0, 125);
          delay(1000);
          Notify2Line();
          oneTicker[14] = true;
        }
      } else {
        oneTicker[14] = false;
      }
    }

    rtcGetYears = now.Year();
    premillis = millis();
  }
}

void AccuracyInit() {

  pwm.begin();
  pwm.setPWMFreq(60);



  pwm.setPWM(0, 0, 125);   //p11
  pwm.setPWM(1, 0, 125);   //p12
  pwm.setPWM(2, 0, 125);   //p13
  pwm.setPWM(3, 0, 125);   //p14
  pwm.setPWM(4, 0, 125);   //p15
  pwm.setPWM(5, 0, 125);   //p6
  pwm.setPWM(6, 0, 125);   //p7
  pwm.setPWM(7, 0, 125);   //p8
  pwm.setPWM(8, 0, 125);   //p9
  pwm.setPWM(9, 0, 125);   //p10
  pwm.setPWM(10, 0, 125);  //p1
  pwm.setPWM(11, 0, 125);  //p2
  pwm.setPWM(12, 0, 125);  //p3
  pwm.setPWM(13, 0, 125);  //p4
  pwm.setPWM(14, 0, 125);  //
}
