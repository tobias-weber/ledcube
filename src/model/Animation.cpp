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
    int ledIdx;
    for (ledIdx = 0; ledIdx < 25; ledIdx++) {
       _cube->setLed(ledIdx, 0b000001);
    }
    for (ledIdx = 25; ledIdx < 50; ledIdx++) {
       _cube->setLed(ledIdx, 0b000100);
    }
    for (ledIdx = 50; ledIdx < 75; ledIdx++) {
       _cube->setLed(ledIdx, 0b010000);
    }
    for (ledIdx = 75; ledIdx < 100; ledIdx++) {
       _cube->setLed(ledIdx, 0b000101);
    }
    for (ledIdx = 100; ledIdx < 125; ledIdx++) {
       _cube->setLed(ledIdx, 0b010000);
    }
}
// writes the next frame to the hardware
void Animation::showNextFrame() {
  _writer->writeCube();
}
