//include arduino default data types and functions
#include "Arduino.h"

//include header for Cube
#include "Cube.h"

//include header for Writer
#include "Writer.h"

Cube *_cube;
Writer *_writer;
const byte _serialData = 13; // serial data pin
const byte _serialShift = 13; // serial shift pin

Animation:Animation() {
  *_cube = new Cube();
  *_writer = new Writer(*_cube, _serialData, _serialShift);
}

// calculates the next frame and updates the cube object
void renderNextFrame() {
  //TODO_ implementation
}

// writes the next frame to the hardware
void showNectFrame() {
  _writer.writeCube();
}

