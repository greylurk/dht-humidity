#include <Homie.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "climate.hpp"

HomieNode climateNode("climate", "climate");
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
Climate climate;

void updateClimate(ClimateDatum datum) {
  String temperatureF = String(datum.getTemperatureF());
  String humidity = String(datum.getHumidity());
  climateNode.setProperty("temperature.c").send(String(datum.getTemperatureC()));
  climateNode.setProperty("temperature.f").send(temperatureF);
  climateNode.setProperty("humidity").send(humidity);
  lcd.setCursor(0,0);
  lcd.print(temperatureF);
  lcd.setCursor(0,1);
  lcd.print(humidity);
}

void setupHandler() {
  climateNode.advertise("temperature.c");
  climateNode.advertise("temperature.f");
  climateNode.advertise("humidity");
  climate.setup(updateClimate);
  // initialize library
  lcd.begin(16,2);
  // blink backlight three times
  lcd.backlight();
}

void loopHandler() {
  climate.loop();
}

void setup() {
  Serial.begin(115200);
  Homie_setFirmware("ness-multi-sensor", "1.0.0");
  Homie
    .setSetupFunction(setupHandler)
    .setLoopFunction(loopHandler);

  Homie.setup();
}

void loop() {
  Homie.loop();
}