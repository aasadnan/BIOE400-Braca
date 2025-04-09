#include "programmable_air.h"

#include <Adafruit_NeoPixel.h>

#define DEBUG 1

int state = UN_KNOWN;

int atmospheric_pressure = 508; // should be around 508
int threshold = 8;

void setup() {
  initializePins();
}

void loop() {
  showPressure();
  // deflate
  if (readBtn(RED) && state != SUCKING) {
    // switch on pumps to 50% power
    switchOnPump(1, 100);
    switchOffPump(2);
    suck();
    state = SUCKING;
  }
  // inflate
  else if (readBtn(BLUE) && state != BLOWING) {
    // switch on pumps to 50% power
    switchOnPump(2, 100);
    switchOffPump(1);
    blow();
    state = BLOWING;
  }
  // if neither button is pressed, vent
  else if (!readBtn(BLUE) && !readBtn(RED) && state != VENTING) {
    switchOffPumps();
    vent();
    state = VENTING;
  }

  delayWhileReadingPressure(200);
}