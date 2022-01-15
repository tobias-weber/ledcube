// include arduino default data types and functions
#include "Arduino.h"

// include header for Cube
#include "Cube.h"

byte _cubearray[125] = {0};
        
// contructor
Cube::Cube() {
}

// set all leds to 0
void Cube::clearLeds() {
  for(int i = 0; i < 125; i++) {
    _cubearray[i] = 0;
  }
}

// set color by specifying x,y,z
void Cube::setLed(byte x, byte y, byte z, byte color) {
  _cubearray[x + 5 * y + 25 * z] = color;
}

// set color with unique led id (0-124)
void Cube::setLed(byte id, byte color) {
  _cubearray[id] = color;
}

// set color by specifying layer and led number on that layer
void Cube::setLed(byte z, byte k, byte color) {
  _cubearray[25 * z + k] = color;
}

byte Cube::getLed(byte x, byte y, byte z) {
  return _cubearray[x + 5 * y + 25 * z];
}

// returns the byte of the led by unique led id (0-124)
byte Cube::getLed(byte id) {
  return _cubearray[id];
}

// Color is stored in the format: 00b2b1g2g1r2r1
byte Cube::getColor(byte r, byte g, byte b) {
  return r + g << 2 + b << 4;
}
