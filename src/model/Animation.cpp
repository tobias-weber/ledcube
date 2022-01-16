//include arduino default data types and functions
#include "Arduino.h"

//include header for Cube
#include "Cube.h"

//include header for Writer
#include "Writer.h"

// include header for Animation
#include "Animation.h"

Cube _cube;

Animation::Animation(byte serialData, byte serialShift, byte layer0) {
  this->_serialData = serialData;
  this->_serialShift = serialShift;
  this->_mosfetLayer0 = layer0;
  this->_writer = new Writer(_cube, _serialData, _serialShift, _mosfetLayer0);
}

// calculates the next frame and updates the cube object
void Animation::renderNextFrame() {
  //TODO_ implementation
}

// writes the next frame to the hardware
void Animation::showNextFrame() {
  _writer->writeCube();
}
