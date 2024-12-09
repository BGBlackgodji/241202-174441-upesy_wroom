
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
LiquidCrystal_I2C lcd2(0x26, 16, 2);


void Save2Memory();

#define BUTTON_A 7
#define BUTTON_B 60
#define BUTTON_OK 8
#define BUTTON_EDIT 10
#define BUTTON_SWITCHER 9

char key;

struct DateTimer {
  int32_t timerDate[6] = { 0, 0, 0, 0, 0, 0 };
  unsigned long long int timerUnix = 0;
} ServoTimer[15];


void lcdInit() {

  lcd.begin();
  lcd.backlight();

  // เซอร์โวตัวที่ 0              ปี    เดือน  วัน  ชั่วโมง นาที วินาที
  ServoTimer[0].timerDate[0] = 2023;
  ServoTimer[0].timerDate[1] = 0;
  ServoTimer[0].timerDate[2] = 0;
  ServoTimer[0].timerDate[3] = 0;
  ServoTimer[0].timerDate[4] = 0;
  ServoTimer[0].timerDate[5] = 0;

  ServoTimer[1].timerDate[0] = 2023;
  ServoTimer[1].timerDate[1] = 0;
  ServoTimer[1].timerDate[2] = 0;
  ServoTimer[1].timerDate[3] = 0;
  ServoTimer[1].timerDate[4] = 0;
  ServoTimer[1].timerDate[5] = 0;

  // Continue this pattern for the remaining elements
  ServoTimer[2].timerDate[0] = 2023;
  ServoTimer[2].timerDate[1] = 0;
  ServoTimer[2].timerDate[2] = 0;
  ServoTimer[2].timerDate[3] = 0;
  ServoTimer[2].timerDate[4] = 0;
  ServoTimer[2].timerDate[5] = 0;

  ServoTimer[3].timerDate[0] = 2023;
  ServoTimer[3].timerDate[1] = 0;
  ServoTimer[3].timerDate[2] = 0;
  ServoTimer[3].timerDate[3] = 0;
  ServoTimer[3].timerDate[4] = 0;
  ServoTimer[3].timerDate[5] = 0;

  ServoTimer[4].timerDate[0] = 2023;
  ServoTimer[4].timerDate[1] = 5;
  ServoTimer[4].timerDate[2] = 5;
  ServoTimer[4].timerDate[3] = 5;
  ServoTimer[4].timerDate[4] = 25;
  ServoTimer[4].timerDate[5] = 0;

  ServoTimer[5].timerDate[0] = 2023;
  ServoTimer[5].timerDate[1] = 6;
  ServoTimer[5].timerDate[2] = 6;
  ServoTimer[5].timerDate[3] = 6;
  ServoTimer[5].timerDate[4] = 26;
  ServoTimer[5].timerDate[5] = 0;

  ServoTimer[6].timerDate[0] = 2023;
  ServoTimer[6].timerDate[1] = 7;
  ServoTimer[6].timerDate[2] = 7;
  ServoTimer[6].timerDate[3] = 7;
  ServoTimer[6].timerDate[4] = 27;
  ServoTimer[6].timerDate[5] = 0;

  ServoTimer[7].timerDate[0] = 2023;
  ServoTimer[7].timerDate[1] = 8;
  ServoTimer[7].timerDate[2] = 8;
  ServoTimer[7].timerDate[3] = 8;
  ServoTimer[7].timerDate[4] = 28;
  ServoTimer[7].timerDate[5] = 0;

  ServoTimer[8].timerDate[0] = 2023;
  ServoTimer[8].timerDate[1] = 9;
  ServoTimer[8].timerDate[2] = 9;
  ServoTimer[8].timerDate[3] = 9;
  ServoTimer[8].timerDate[4] = 29;
  ServoTimer[8].timerDate[5] = 0;

  ServoTimer[9].timerDate[0] = 2023;
  ServoTimer[9].timerDate[1] = 10;
  ServoTimer[9].timerDate[2] = 10;
  ServoTimer[9].timerDate[3] = 10;
  ServoTimer[9].timerDate[4] = 30;
  ServoTimer[9].timerDate[5] = 0;

  ServoTimer[10].timerDate[0] = 2023;
  ServoTimer[10].timerDate[1] = 11;
  ServoTimer[10].timerDate[2] = 11;
  ServoTimer[10].timerDate[3] = 11;
  ServoTimer[10].timerDate[4] = 31;
  ServoTimer[10].timerDate[5] = 0;

  ServoTimer[11].timerDate[0] = 2023;
  ServoTimer[11].timerDate[1] = 12;
  ServoTimer[11].timerDate[2] = 12;
  ServoTimer[11].timerDate[3] = 12;
  ServoTimer[11].timerDate[4] = 32;
  ServoTimer[11].timerDate[5] = 0;

  ServoTimer[12].timerDate[0] = 2023;
  ServoTimer[12].timerDate[1] = 13;
  ServoTimer[12].timerDate[2] = 13;
  ServoTimer[12].timerDate[3] = 13;
  ServoTimer[12].timerDate[4] = 33;
  ServoTimer[12].timerDate[5] = 0;

  ServoTimer[13].timerDate[0] = 2023;
  ServoTimer[13].timerDate[1] = 14;
  ServoTimer[13].timerDate[2] = 14;
  ServoTimer[13].timerDate[3] = 14;
  ServoTimer[13].timerDate[4] = 34;
  ServoTimer[13].timerDate[5] = 0;

  ServoTimer[14].timerDate[0] = 2023;
  ServoTimer[14].timerDate[1] = 0;
  ServoTimer[14].timerDate[2] = 0;
  ServoTimer[14].timerDate[3] = 0;
  ServoTimer[14].timerDate[4] = 0;
  ServoTimer[14].timerDate[5] = 0;
}

String lcd_cursor[4] = { " ", " ", " ", " " };
int lcd_index = -1;
int lcd_lastindex;
int lcd_loadindex = -1;
int lcd_pages = 0;
boolean un_active_cursor = false;

static int8_t lcdRowStep = 0;

void lcdSelectorUp() {
  if (un_active_cursor == false) {
    if (lcd_loadindex != -1 && lcd_index != 1) {  //checking lastindex don't have value
      lcd_index--;                                // decrease lcd index
      lcd_loadindex = lcd_index - 1;              // set last loadindex to index - 1
    } else {
      lcd_cursor[lcd_index] = " ";  // else found lastindex == -1 and found lcd index == 0 --> create blank on lcd index
    }

    if (lcd_cursor[lcd_loadindex] == " ") {  // if lastcursor index == blank
      lcd_cursor[lcd_index] = " ";           // set selected index to blank
      lcd_cursor[lcd_loadindex] = ">";       // adding > to lastindex
    }
  } else {
    if (lcdRowStep < 3) {
      lcdRowStep++;
    } else {
      lcdRowStep = 3;
    }
  }
}

void lcdSelectorDown() {
  if (un_active_cursor == false) {
    if (lcd_index < 4) {                       //limit user can't select over 3
      if (lcd_cursor[lcd_loadindex] == ">") {  // if last cursor >=
        lcd_cursor[lcd_loadindex] = " ";       // delete last cursor to blank
      }
      lcd_cursor[lcd_index] = ">";    // adding > to new lcd cursor
      lcd_index++;                    // move/ index
      lcd_loadindex = lcd_index - 1;  // last cursor = index - 1
    }
  } else {
    if (lcdRowStep > 0) {
      lcdRowStep--;
    } else {
      lcdRowStep = 0;
    }
  }
}





int16_t keyPressNumber(char keys, int8_t lcdMode) {
  static String buffer;
  if (isdigit(keys)) {
    buffer += keys;
  } else if (keys == 'C') {
    int16_t bufferInt = buffer.toInt();

    if (lcdMode == 0) {
      if (bufferInt > 31) {
        bufferInt = 31;
      } else if (bufferInt < 0) {
        bufferInt = 0;
      }
    } else if (lcdMode == 1) {
      if (bufferInt > 12) {
        bufferInt = 12;
      } else if (bufferInt < 0) {
        bufferInt = 0;
      }
    } else if (lcdMode == 2) {
      if (bufferInt > 23) {
        bufferInt = 23;
      } else if (bufferInt < 0) {
        bufferInt = 0;
      }
    } else if (lcdMode == 3) {
      if (bufferInt > 59) {
        bufferInt = 59;
      } else if (bufferInt < 0) {
        bufferInt = 0;
      }
    } else {
      if (bufferInt > 59) {
        bufferInt = 59;
      } else if (bufferInt < 0) {
        bufferInt = 0;
      }
    }


    buffer = "";
    return bufferInt;
  }

  return -1;  // Return -1 if not a valid number
}



int32_t assignNumber[4];
static bool cursorBlinking = false;

void lcdPagesChanger(int8_t index) {
  int currentPage = index / 15;

  // Row 1
  lcd.setCursor(0, 0);
  lcd.print(String(lcd_cursor[0]));
  lcd.setCursor(1, 0);
  lcd.print("P");  // 0
  lcd.print(index);
  lcd.print(":");

  if (lcd_index > 0 && lcd_index == 1 && un_active_cursor == true) {

    int16_t getKeyNumber = keyPressNumber(key, lcdRowStep);
    if (getKeyNumber >= 0) {
      assignNumber[lcdRowStep] = getKeyNumber;
    }

    static bool onetime = false;

    if (key == '*') {
      if (onetime == false) {
        int servoIndex = index;
        if (lcdRowStep == 0)
          ServoTimer[servoIndex].timerDate[2] = assignNumber[0];
        else if (lcdRowStep == 1)
          ServoTimer[servoIndex].timerDate[1] = assignNumber[1];
        else if (lcdRowStep == 2)
          ServoTimer[servoIndex].timerDate[3] = assignNumber[2];
        else if (lcdRowStep == 3)
          ServoTimer[servoIndex].timerDate[4] = assignNumber[3];

        Save2Memory();
        buzzerTicker = true;
        onetime = true;
      }
    }

    lcd.print(cursorBlinking && lcdRowStep == 0 ? "-" : String(ServoTimer[index].timerDate[2]));
    lcd.print("/");
    lcd.print(cursorBlinking && lcdRowStep == 1 ? "-" : String(ServoTimer[index].timerDate[1]));
    lcd.print("   ");
    lcd.print(cursorBlinking && lcdRowStep == 2 ? "-" : String(ServoTimer[index].timerDate[3]));
    lcd.print(":");
    lcd.print(cursorBlinking && lcdRowStep == 3 ? "-" : String(ServoTimer[index].timerDate[4]));
    lcd.print("   ");

  } else {
    lcd.print(ServoTimer[index].timerDate[2]);
    lcd.print("/");
    lcd.print(ServoTimer[index].timerDate[1]);
    lcd.print("   ");
    lcd.print(ServoTimer[index].timerDate[3]);
    lcd.print(":");
    lcd.print(ServoTimer[index].timerDate[4]);
    lcd.print("   ");
  }

  // Row 2
  lcd.setCursor(0, 1);
  lcd.print(String(lcd_cursor[1]));
  lcd.setCursor(1, 1);
  lcd.print("P");  // 0
  lcd.print(index + 1);
  lcd.print(":");


  if (lcd_index > 0 && lcd_index == 2 && un_active_cursor == true) {

    int16_t getKeyNumber = keyPressNumber(key, lcdRowStep);
    if (getKeyNumber >= 0) {
      assignNumber[lcdRowStep] = getKeyNumber;
    }

    if (key == '*') {
      int servoIndex = index + 1;
      if (lcdRowStep == 0)
        ServoTimer[servoIndex].timerDate[2] = assignNumber[0];
      else if (lcdRowStep == 1)
        ServoTimer[servoIndex].timerDate[1] = assignNumber[1];
      else if (lcdRowStep == 2)
        ServoTimer[servoIndex].timerDate[3] = assignNumber[2];
      else if (lcdRowStep == 3)
        ServoTimer[servoIndex].timerDate[4] = assignNumber[3];

      Save2Memory();
      buzzerTicker = true;
    }

    lcd.print(cursorBlinking && lcdRowStep == 0 ? "-" : String(ServoTimer[index + 1].timerDate[2]));
    lcd.print("/");
    lcd.print(cursorBlinking && lcdRowStep == 1 ? "-" : String(ServoTimer[index + 1].timerDate[1]));
    lcd.print("   ");
    lcd.print(cursorBlinking && lcdRowStep == 2 ? "-" : String(ServoTimer[index + 1].timerDate[3]));
    lcd.print(":");
    lcd.print(cursorBlinking && lcdRowStep == 3 ? "-" : String(ServoTimer[index + 1].timerDate[4]));
    lcd.print("   ");



  } else {
    lcd.print(ServoTimer[index + 1].timerDate[2]);
    lcd.print("/");
    lcd.print(ServoTimer[index + 1].timerDate[1]);
    lcd.print("   ");
    lcd.print(ServoTimer[index + 1].timerDate[3]);
    lcd.print(":");
    lcd.print(ServoTimer[index + 1].timerDate[4]);
    lcd.print("   ");
  }

  // Row 3
  lcd.setCursor(0, 2);
  lcd.print(String(lcd_cursor[2]));
  lcd.setCursor(1, 2);
  lcd.print("P");  // 0
  lcd.print(index + 2);
  lcd.print(":");


  if (lcd_index > 0 && lcd_index == 3 && un_active_cursor == true) {

    int16_t getKeyNumber = keyPressNumber(key, lcdRowStep);
    if (getKeyNumber >= 0) {
      assignNumber[lcdRowStep] = getKeyNumber;
    }

    if (key == '*') {
      int servoIndex = index + 2;
      if (lcdRowStep == 0)
        ServoTimer[servoIndex].timerDate[2] = assignNumber[0];
      else if (lcdRowStep == 1)
        ServoTimer[servoIndex].timerDate[1] = assignNumber[1];
      else if (lcdRowStep == 2)
        ServoTimer[servoIndex].timerDate[3] = assignNumber[2];
      else if (lcdRowStep == 3)
        ServoTimer[servoIndex].timerDate[4] = assignNumber[3];
      Save2Memory();
      buzzerTicker = true;
    }

    lcd.print(cursorBlinking && lcdRowStep == 0 ? "-" : String(ServoTimer[index + 2].timerDate[2]));
    lcd.print("/");
    lcd.print(cursorBlinking && lcdRowStep == 1 ? "-" : String(ServoTimer[index + 2].timerDate[1]));
    lcd.print("   ");
    lcd.print(cursorBlinking && lcdRowStep == 2 ? "-" : String(ServoTimer[index + 2].timerDate[3]));
    lcd.print(":");
    lcd.print(cursorBlinking && lcdRowStep == 3 ? "-" : String(ServoTimer[index + 2].timerDate[4]));
    lcd.print("   ");


  } else {
    lcd.print(ServoTimer[index + 2].timerDate[2]);
    lcd.print("/");
    lcd.print(ServoTimer[index + 2].timerDate[1]);
    lcd.print("   ");
    lcd.print(ServoTimer[index + 2].timerDate[3]);
    lcd.print(":");
    lcd.print(ServoTimer[index + 2].timerDate[4]);
    lcd.print("   ");
  }

  // Row 4
  lcd.setCursor(0, 3);
  lcd.print(String(lcd_cursor[3]));
  lcd.setCursor(1, 3);
  lcd.print("P");  // 0
  lcd.print(index + 3);
  lcd.print(":");


  if (lcd_index > 0 && lcd_index == 4 && un_active_cursor == true) {

    int16_t getKeyNumber = keyPressNumber(key, lcdRowStep);
    if (getKeyNumber >= 0) {
      assignNumber[lcdRowStep] = getKeyNumber;
    }

    if (key == '*') {
      int servoIndex = index + 3;
      if (lcdRowStep == 0)
        ServoTimer[servoIndex].timerDate[2] = assignNumber[0];
      else if (lcdRowStep == 1)
        ServoTimer[servoIndex].timerDate[1] = assignNumber[1];
      else if (lcdRowStep == 2)
        ServoTimer[servoIndex].timerDate[3] = assignNumber[2];
      else if (lcdRowStep == 3)
        ServoTimer[servoIndex].timerDate[4] = assignNumber[3];

      Save2Memory();

      buzzerTicker = true;
    }

    lcd.print(cursorBlinking && lcdRowStep == 0 ? "-" : String(ServoTimer[index + 3].timerDate[2]));
    lcd.print("/");
    lcd.print(cursorBlinking && lcdRowStep == 1 ? "-" : String(ServoTimer[index + 3].timerDate[1]));
    lcd.print("   ");
    lcd.print(cursorBlinking && lcdRowStep == 2 ? "-" : String(ServoTimer[index + 3].timerDate[3]));
    lcd.print(":");
    lcd.print(cursorBlinking && lcdRowStep == 3 ? "-" : String(ServoTimer[index + 3].timerDate[4]));
    lcd.print("   ");


  } else {
    lcd.print(ServoTimer[index + 3].timerDate[2]);
    lcd.print("/");
    lcd.print(ServoTimer[index + 3].timerDate[1]);
    lcd.print("   ");
    lcd.print(ServoTimer[index + 3].timerDate[3]);
    lcd.print(":");
    lcd.print(ServoTimer[index + 3].timerDate[4]);
    lcd.print("   ");
  }
}



void lcdTimer() {
  static unsigned long premillis = 0;
  static bool onetimeButton = false;
  static bool onetimeSelector = false;
  static bool buttonSelected = false;






  if (millis() - premillis >= 1) {
    static uint8_t previousKey = 0;
    key = keypad.getKey();

    if (key != previousKey) {
      sendBuzzer();
    }

    if (key == 'A') {
      lcdSelectorUp();
      Serial.println("up");
    } else if (key == 'B') {
      lcdSelectorDown();
      Serial.println("down");
    }

    if (un_active_cursor == true) {

      onetimeSelector = false;
    } else {
      if (onetimeSelector == false) {
        // lcdSelectorDown();
        onetimeSelector = true;
      }
    }

    if (key == '#') {
      if (onetimeButton == false) {
        un_active_cursor = !un_active_cursor;
        if (un_active_cursor == false) {
          // lcdSelectorDown();
        }
        onetimeButton = true;
      }
    } else {
      onetimeButton = false;
    }


    previousKey = key;

    premillis = millis();
  }

  //blinking selector
  static unsigned blinkingPremillis = 0;

  if (un_active_cursor == true) {
    if (millis() - blinkingPremillis >= 1000) {
      cursorBlinking = !cursorBlinking;
      blinkingPremillis = millis();
    }
  } else {
    lcdRowStep = 0;
  }
  static int indexer = 0;
  static boolean onetimer[2];  // = false;
  if (key == 'D' && un_active_cursor == false) {
    if (onetimer[0] == false) {
      if (indexer < 11) {
        indexer = (indexer + 1) % 15;
      } else {
        lcd.clear();
        indexer = 0;
      }
      onetimer[0] = true;
    }
  } else {
    onetimer[0] = false;
  }


  if (key == 'C' && un_active_cursor == false) {
    onetimer[0] = false;
    if (onetimer[1] == false) {
      if (indexer > 0) {
        indexer--;
      } else {
        indexer = 0;
      }
      onetimer[1] = true;
    }
  } else {
    onetimer[1] = false;
  }

  Serial.println(indexer);

  static unsigned long lcdPremillis = 0;
  if (millis() - lcdPremillis >= 1) {
    lcdPagesChanger(indexer);
    lcdPremillis = millis();
  }
}
