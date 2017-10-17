#include <Homie.h>
#include <DHT.h>


unsigned long lastDHTRead = 0;

DHT dht;
HomieNode climateNode("climate", "climate");

const int TEMPERATURE_INTERVAL = dht.getMinimumSamplingPeriod();

void setupHandler() {
  dht.setup(2);
}

void loopHandler() {
  if (millis() - lastDHTRead >= TEMPERATURE_INTERVAL * 1000UL || lastDHTRead == 0) {
    float temperature = dht.getTemperature();
    float humidity = dht.getHumidity();
    Homie.getLogger() << dht.getStatusString()
      << "Temperature: " << temperature << " °C" << endl
      << "Humidity: " << humidity << "%" << endl;
    climateNode.setProperty("temperature").send(String(temperature));
    climateNode.setProperty("humidity").send(String(humidity));
    lastDHTRead = millis();
  }
}

void setup() {
  Serial.begin(115200);
  Serial << endl << endl;
  Homie_setFirmware("awesome-temperature", "1.0.0");
  Homie.setSetupFunction(setupHandler).setLoopFunction(loopHandler);

  climateNode.advertise("temperature");
  climateNode.advertise("humidity");

  Homie.setup();
}

void loop() {
  Homie.loop();
}
