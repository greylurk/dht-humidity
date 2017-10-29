#include <Homie.h>
#include <Wire.h>
#include "climate.hpp"
#include "display.hpp"

HomieNode climateNode("climate", "climate");
Display display;
Climate climate;
bool displayPresent;

void updateClimate(ClimateDatum datum) {
  String temperatureF = String(datum.getTemperatureF());
  String humidity = String(datum.getHumidity());
  climateNode.setProperty("temperature.c").send(String(datum.getTemperatureC()));
  climateNode.setProperty("temperature.f").send(temperatureF);
  climateNode.setProperty("humidity").send(humidity);
  if( displayPresent ) {
    display.print(0, temperatureF);
    display.print(1, humidity);
  }
}

void setupHandler() {
  climateNode.advertise("temperature.c");
  climateNode.advertise("temperature.f");
  climateNode.advertise("humidity");
  climate.setup(updateClimate);
  displayPresent = Display_isPresent();
  if( displayPresent ) {
    display.init();
  }
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