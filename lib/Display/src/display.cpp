#include "display.hpp"
#include <Wire.h>
#include <Arduino.h>

bool Display_isPresent() {
    byte error;
    Wire.beginTransmission(DISPLAY_ADDRESS);
    error = Wire.endTransmission();
    return error != 0 && error != 4;
}

Display::Display():
    lcd(DISPLAY_ADDRESS, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE) // Initialize LCD
{

}

void Display::init() {
    lcd.begin(16,2);
    lcd.backlight();
}

void Display::clear() {

}

void Display::print(int lineNumber, String string) {
  lcd.setCursor(0,lineNumber);
  lcd.print(string);
}

