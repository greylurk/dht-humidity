#include <Homie.h>
#include <DHT.h>

#ifndef climate_h
#define climate_h

#define DHT_PIN 2

typedef std::function<void(const class ClimateDatum& datum)> UpdateHandler;

class ClimateDatum {
    friend class Climate;

public:
    ClimateDatum(float, float);
    void setUpdateHandler(const UpdateHandler&);
    const float getTemperatureC();
    const float getTemperatureF();
    const float getHumidity();

private:
    float _temperature;
    float _humidity;

    UpdateHandler _handler;

protected:
    void update(float, float);
};

class Climate {
public:
    Climate();
    void loop();
    void setup(const UpdateHandler&);
private:
    ClimateDatum _datum;
    DHT _dht;
    unsigned long _lastDHTRead;
    int _TEMPERATURE_INTERVAL;
};

#endif