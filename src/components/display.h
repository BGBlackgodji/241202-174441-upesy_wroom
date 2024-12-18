#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <LiquidCrystal_I2C.h>

using namespace std;

class Display {
public:
    LiquidCrystal_I2C lcd;

    int column;
    int row;

    Display(int address = 0x27, int charactor = 16, int line = 2);

    void clear();
    void write(string message);
    void writeLine(string message);
};

#endif
