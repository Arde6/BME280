# BME280 setup with unique id on ESP32
#### Might work on Arduino with no changes

## BME280 and LCD
I2C runs on pins 21 and 22, both screen and sensor. 22 is SCL and 21 SDA.

## ID system
Pins 33, 32, 25, 26 are used to set id as a binary (pin 33 is 1st) by wiring the wanted 1's to ground.