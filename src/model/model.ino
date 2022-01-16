#include "Animation.h"
#include "Cube.h"
#include "Writer.h"

// pin out
const byte FRAMERATE = 12; // framerate of the cube
const byte SERIAL_DATA = 8; // pin used to output serial data
const byte SERIAL_SHIFT = 9; // pin used to shift registers
// pin the mosfet for the layer nr.0 is connected to
// other layers use incrementing pin ids from layer0 onwards
const byte LAYER0 = 10;

float frameDelta;
unsigned long startTime;
Animation animation(SERIAL_DATA, SERIAL_SHIFT, LAYER0);

void setup() {
  frameDelta = 1/FRAMERATE;
}

void loop() {
  startTime = millis();
  animation.renderNextFrame();
  animation.showNextFrame(); // pwm cycle 0
  animation.showNextFrame(); // pwm cycle 1
  animation.showNextFrame(); // pwm cycle 2
  animation.showNextFrame(); // pwm cycle 3
  pace(startTime, millis());
}

void pace(unsigned long startTime, unsigned long currentTime) {
  if (frameDelta - (currentTime - startTime) > 0) {
    delay(frameDelta - (currentTime - startTime));
  }
  
}

//@Tobi W: Ich ha din code nach src/cube.ccp gmoved
