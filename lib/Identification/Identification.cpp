#include <Arduino.h>
#include <math.h>

// int bit4 = 34, bit3 = 35, bit2 = 32, bit1 = 33;
const int numPins = 4;
int pins[numPins] = {32, 33, 25, 26};
int bits[numPins];

// sets id to the device using pins to gnd
int idSetup () {

    int id = 0;

    // setup pins for input with pullup
    for (int i = 0; i < numPins; i++) {
        pinMode(pins[i], INPUT_PULLUP);

        int state = digitalRead(pins[i]);
        state = !state;
        bits[i] = state;

        id = id + bits[i] * pow(2,i);
    }

    return id;
}