// include arduino default data types and functions
#include "Arduino.h"

// include header for Cube
#include "Cube.h"

// include header for Animation
#include "Animation.h"

int counter = 0;

// contructor
Animation::Animation() {
}

// assigns a cube to this animation
void Animation::assignCube(Cube* cube){
  _cube = cube;
}
// assigns a writer to this animation
void Animation::assignWriter(Writer* writer) {
  _writer = writer;
}
// calculates the next frame and updates the cube object
void Animation::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (millis() - _lastFrame < _frameDelta) {
      return;
    }
    _lastFrame = millis();
    // animation...
    _cube->clearLeds();
    if (counter > 1270) {
      counter = 0;
    }
    _cube->setLed((counter/10 + 1) % 125, 0b010101);
    _cube->setLed(counter/10 % 125, 0b000001);
    _cube->setLed((counter/10-1) % 125, 0b000001);
    _cube->setLed((counter/10-2) % 125, 0b000101);
    _cube->setLed((counter/10-3) % 125, 0b000100);
    _cube->setLed((counter/10-4) % 125, 0b010100);
    _cube->setLed((counter/10-5) % 125, 0b010000);
    _cube->setLed((counter/10-6) % 125, 0b010001);
    counter++;
}
// writes the next frame to the hardware
void Animation::showNextFrame() {
  // check if rewriting of current frame is already necessary. Minimizes jitter
  if (millis() - _lastRefresh < _refreshDelta) {
      return;
  }
  _lastRefresh = millis();
  _writer->writeCube();
}
