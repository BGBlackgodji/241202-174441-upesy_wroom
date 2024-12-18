#include "display.h"

Display::Display(int address, int charactor, int line) : lcd(address, charactor, line) {
    column = charactor;
    row = line;

    lcd.begin(column, row);
    lcd.backlight();
    lcd.autoscroll();

    clear();
}

void Display::clear() {
    lcd.clear();
    lcd.setCursor(0, 0);
}

void Display::write(string message) {
    lcd.print(message.c_str());
}

void Display::writeLine(string message) {
    lcd.println(message.c_str());
}