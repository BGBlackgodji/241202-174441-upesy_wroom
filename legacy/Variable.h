#define BUZZER 17
#define BUZZ 15
#include "BuzzerAlert.h"
#include <TimeLib.h>
#include <Adafruit_PWMServoDriver.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>
#include <Wire.h>

#include <Keypad_I2C.h>
#include <Keypad.h>

#include <TridentTD_LineNotify.h>
#define SSID "Minn"
#define PASSWORD "00112233"
#define LINE_TOKEN "l4arM0BJzA6u1OtFJrB4YiQOVhU0FgFJZ6wnQxR0RQ2"

boolean isConnected = false;

#define I2CADDR 0x21  // กำหนด Address ของ I2C
// วิธีการหา Address ของ I2C สามารถดูได้จากลิงค์ข้างล่าง
// https://www.myarduino.net/article/98

const byte ROWS = 4;  // กำหนดจำนวนของ Rowsx
const byte COLS = 4;  // กำหนดจำนวนของ Columns

// กำหนด Key ที่ใช้งาน (4x4)
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// กำหนด Pin ที่ใช้งาน (4x4)
byte rowPins[ROWS] = { 0, 1, 2, 3 };  // เชื่อมต่อกับ Pin แถวของปุ่มกดv
byte colPins[COLS] = { 4, 5, 6, 7 };  // เชื่อมต่อกับ Pin คอลัมน์ของปุ่มกด

// makeKeymap(keys) : กำหนด Keymap
// rowPins : กำหนด Pin แถวของปุ่มกด
// colPins : กำหนด Pin คอลัมน์ของปุ่มกด
// ROWS : กำหนดจำนวนของ Rows
// COLS : กำหนดจำนวนของ Columns
// I2CADDR : กำหนด Address ขอ i2C
// PCF8574 : กำหนดเบอร์ IC
Keypad_I2C keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574);


#include "lcdModule.h"
#include "AccuracyTimer.h"