#include "Variable.h"
#include "ExternalCore.h"
#include "Boot.h"


void printData() {
  Serial.println("Data in ServoTimer array:");

  for (int i = 0; i < 15; i++) {
    Serial.print("Entry ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print("Year: ");
    Serial.print(ServoTimer[i].timerDate[0]);
    Serial.print(", Month: ");
    Serial.print(ServoTimer[i].timerDate[1]);
    Serial.print(", Day: ");
    Serial.print(ServoTimer[i].timerDate[2]);
    Serial.print(", Hour: ");
    Serial.print(ServoTimer[i].timerDate[3]);
    Serial.print(", Minute: ");
    Serial.print(ServoTimer[i].timerDate[4]);
    Serial.print(", Second: ");
    Serial.print(ServoTimer[i].timerDate[5]);
    Serial.print(", Unix Timestamp: ");
    Serial.println(ServoTimer[i].timerUnix);
  }
}


void setup() {
  pinMode(BUZZ , OUTPUT);
  digitalWrite(BUZZ, LOW);

  Serial.begin(9600);
  SPIFFMemoryInitial();
  ReadFromMemory();
  printData();

  Wire.begin();                    // เรียกการเชื่อมต่อ Wire
  keypad.begin(makeKeymap(keys));  // เรียกกาเชื่อมต่อ
  lcdInit();


  Serial.print("compiled: ");
  Serial.print(__DATE__);
  Serial.println(__TIME__);


  initCore();
}
void loop() {
  // สร้างตัวแปรชื่อ key ชนิด char เพื่อเก็บตัวอักขระที่กด
  //set timer

  lcdTimer();
  buzzerTimer();
  // Press C Next Page
  // Press D Previous Page
  // Press A Up Cursor
  // Press B Down Cursor

  // Press # Select Item
  // - Press A Next Left
  // - Press B Next Right
  // Key Your Value
  // - Press C to use Value
  // - Press * to set value;
  // Press # Again to back
}
