#include "programmable_air.h"
#include <Adafruit_NeoPixel.h>

#define DEBUG 1

int sensorpin = A0;
int sensor;
int atmospheric_pressure = 508;
int cycle_number = 0;

void setup() {
  Serial.begin(9600);
  initializePins();
}

void loop() {
  Serial.print("Cycle #");
  Serial.println(++cycle_number);

  // Inflate
  Serial.println("Inflating...");
  switchOnPump(2, 100); // Inflate pump ON
  switchOffPump(1);   
  blow();
  delay(3000);          // Hold for 3 seconds

  // Deflate
  Serial.println("Deflating...");
  switchOnPump(1, 100); // Suck pump ON
  switchOffPump(2);    
  suck();
  delay(1000);          // Run suck for a short burst (adjust if needed)
  switchOffPumps();     // Stop both pumps

  // // Wait 5 seconds and record pressure for creep assessment
  // Serial.println("Waiting for 5s to assess creep...");
  // delay(5000);
  // sensor = analogRead(sensorpin);
  // Serial.print("Residual pressure reading (creep): ");
  // Serial.println(sensor);
  
  // Rest before next cycle
  Serial.println("Resting 5s before next cycle...");
  delay(5000);
}
