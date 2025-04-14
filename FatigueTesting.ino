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
  // === Step 1: Inflate bladder ===
  switchOnPump(2, 100);  // Pump 2 inflates
  switchOffPump(1);      // Ensure suck pump is off
  digitalWrite(valvePin, LOW); // Ensure valve is closed
  delay(3000); // Inflate duration (you can replace this with pressure-based logic if needed)
  switchOffPumps();

  // === Step 2: Hold pressure ===
  delay(3000);  // Hold for 3 seconds

  // === Step 3: Deflate ===
  digitalWrite(valvePin, HIGH); // Open valve
  delay(2000);                  // Valve stays open for 2 seconds
  digitalWrite(valvePin, LOW);  // Close valve

  // === Step 4: Wait and record creep ===
  delay(5000);  // Wait 5 seconds after deflation
  sensor = analogRead(sensorpin);
  Serial.print("Creep pressure reading: ");
  Serial.println(sensor);

  // === Step 5: Rest ===
  delay(5000);  // Wait 5 seconds before next cycle
}
