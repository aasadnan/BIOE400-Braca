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
  
  // inflate if light pressure
  if (sensor < 400 && state != BLOWING) {
    switchOnPump(2, 100);// turn on blow pump
    switchOffPump(1);
    blow();
    state = BLOWING;
  }

  // deflate if heavy pressure
  else if (sensor > 700 && state != SUCKING) {
    switchOnPump(1, 100);// yurn on suck pump
    switchOffPump(2);
    suck();
    state = SUCKING;
  }

  //if in-between, vent (medium )
  else if (sensor >= 400 && sensor <= 700 && state != VENTING) {
    switchOffPumps();
    vent();
    state = VENTING;
  }

  delayWhileReadingPressure(200);
}
