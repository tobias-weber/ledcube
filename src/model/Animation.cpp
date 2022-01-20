// include arduino default data types and functions
#include "Arduino.h"

// include header for Cube
#include "Cube.h"

// include header for Animation
#include "Animation.h"

byte counter = 0;

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
    _cube->clearLeds();
    if (counter > 4) {
      counter = 0;
    }
    int ledIdx;
    for (ledIdx = 0; ledIdx < 120; ledIdx += 5) {
      _cube->setLed(ledIdx + counter, 0b10101);
    }
    counter++;
}
// writes the next frame to the hardware
void Animation::showNextFrame() {
  _writer->writeCube();
}
