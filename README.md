# DHT Humidity
This is the firmware for a few ESP-8266 Wemos Mini's that I'm building for my home automation.  The first project is to put a few up for temperature and humidity sensors in various places in the house (one in the bedroom, one in the furnace room, one in the kitchen), then I'll be adding more features as time continues, including outdoor weather sensors, and a few other things.

I'm integrating them, and doing temperature readouts through MQTT to a [Home Assistant](https://home-assistant.io/) dashboard. The MQTT reporting is done through [Homie](https://github.com/marvinroger/homie-esp8266) to a [CloudMQTT](https://www.cloudmqtt.com/) broker.

