#pragma once

#include <LiquidCrystal_I2C.h>

#define DISPLAY_ADDRESS 0x27

class Display {
private:
    LiquidCrystal_I2C lcd;
public:
    Display();
    void clear();
    void print(int lineNumber, String string);
    void init();
};

bool Display_isPresent();
