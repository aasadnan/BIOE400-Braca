#include "programmable_air.h"
#include <Adafruit_NeoPixel.h>

#define DEBUG 1

int sensorpin = A0;
int sensor;
int atmospheric_pressure = 508;
int threshold = 8;

#define valvePin 6  // Solenoid valve pin

void setup() {
  Serial.begin(9600);
  initializePins();
  pinMode(valvePin, OUTPUT);
  digitalWrite(valvePin, LOW); // Keep valve closed initially
}

void loop() {
  // === Inflate bladder ===
  switchOnPump(2, 100);  // Pump 2 inflates
  switchOffPump(1);
  digitalWrite(valvePin, LOW); 
  delay(3000); // Inflate duration 
  switchOffPumps();

  delay(3000);  // Hold for 3 seconds

  // === Deflate ===
  digitalWrite(valvePin, HIGH); // Open valve
  delay(2000);
  digitalWrite(valvePin, LOW);  // Close valve

  delay(5000);  // Wait 5 seconds after deflation
  
}
