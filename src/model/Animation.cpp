//include arduino default data types and functions
#include "Arduino.h"

//include header for Cube
#include "Cube.h"

//include header for Writer
#include "Writer.h"

// include header for Animation
#include "Animation.h"

const byte _serialData = 13; 
const byte _serialShift = 13;

Cube _cube;
Writer _writer(_cube, _serialData, _serialShift);;

Animation::Animation() {
}

// calculates the next frame and updates the cube object
void Animation::renderNextFrame() {
  //TODO_ implementation
}

// writes the next frame to the hardware
void Animation::showNextFrame() {
  _writer.writeCube();
}
