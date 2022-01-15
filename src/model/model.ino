#include "Animation.h"
#include "Cube.h"
#include "Writer.h"

byte framerate = 12;
float frameDelta;
unsigned long startTime;
Animation animation;

void setup() {
  frameDelta = 1/framerate;
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
