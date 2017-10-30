#include <Homie.h>
#include "climate.hpp"

Climate::Climate() :
  _dht(),
  _datum(0, 0) {
  _TEMPERATURE_INTERVAL = _dht.getMinimumSamplingPeriod();
  _lastDHTRead = 0;
}

void Climate::setup(const UpdateHandler& updateHandler) {
  _datum.setUpdateHandler(updateHandler);
  _dht.setup(DHT_PIN);
}

void Climate::loop() {
  if (millis() - _lastDHTRead >= _TEMPERATURE_INTERVAL || _lastDHTRead == 0) {
    float temperature = _dht.getTemperature();
    float humidity = _dht.getHumidity();
    _datum.update(temperature, humidity);
    _lastDHTRead = millis();
  }
}

ClimateDatum::ClimateDatum(float temperature, float humidity) :
  _handler(NULL) {
  _temperature = temperature;
  _humidity = humidity;
}

void ClimateDatum::update(float temperature, float humidity) {
  _temperature = temperature;
  _humidity = humidity;

  if( _handler != NULL ) {
    _handler(*this);
  }
}

void ClimateDatum::setUpdateHandler(const UpdateHandler& handler) {
  _handler = handler;
}

const float ClimateDatum::getTemperatureC() {
  return _temperature;
}

const float ClimateDatum::getTemperatureF() {
  return _temperature * 9.0 / 5.0 + 32;
}

const float ClimateDatum::getHumidity() {
  return _humidity;
}