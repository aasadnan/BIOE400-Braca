#include "programmable_air.h"

#include <Adafruit_NeoPixel.h>

#define DEBUG 1

int state = UN_KNOWN;

int atmospheric_pressure = 508; // should be around 508
int threshold = 8;

int sensorpin = A0;
int sensor;

void setup() {
  Serial.begin(9600);
  initializePins();
}

void loop() {
  sensor = analogRead(sensorpin);
  Serial.println(sensor);
  
  showPressure();
  
  // inflate if light pressure
  if (sensor > 1 && sensor < 10 && state != BLOWING) {
    switchOnPump(2, 100);// turn on blow pump
    switchOffPump(1);
    blow();
    state = BLOWING;
  }

  // deflate if heavy pressure
  else if (sensor > 30 && state != SUCKING) {
    switchOnPump(1, 100);// turn on suck pump
    switchOffPump(2);
    suck();
    state = SUCKING;
  }

  //if in-between, vent (medium )
  else if (sensor < 1 || sensor >= 10 && sensor <= 30 && state != VENTING) {
    switchOffPumps();
    vent();
    state = VENTING;
  }

  delayWhileReadingPressure(200);
}
