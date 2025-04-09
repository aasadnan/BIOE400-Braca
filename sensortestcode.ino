#include "programmable_air.h"

#include <Adafruit_NeoPixel.h>

#define DEBUG 1

int state = UN_KNOWN;

int atmospheric_pressure = 508; // should be around 508
int threshold = 8;

int sensorpin = A0;
int sensor;

void setup() {
  initializePins();
}

void loop() {
  sensor = analogRead(sensorpin);
  Serial.println(sensor);

  showPressure();
  // deflate
  if (sensor>9 && state != SUCKING) {
    // switch on pumps to 50% power
    switchOnPump(1, 100);
    switchOffPump(2);
    suck();
    state = SUCKING;
  }
  // inflate
  else if (2<sensor<9 && state != BLOWING) {
    // switch on pumps to 50% power
    switchOnPump(2, 100);
    switchOffPump(1);
    blow();
    state = BLOWING;
  }
  // if neither button is pressed, vent
  else if (sensor<2 && state != VENTING) {
    switchOffPumps();
    vent();
    state = VENTING;
  }

  delayWhileReadingPressure(200);
}