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

// ............................
// More advanced set methods
// ............................

// Set all leds in the k-th normal plane of axis to color.
// Axis can be 0 -> x     1 -> y     2 -> z (= set color of a layer)
void Cube::setPlane(byte axis, byte k, byte color) {

  switch(axis) {
    case 0: // x-Axis
      for (byte i = 0; i < 25; i++) {
        _cubearray[5 * i + k] = color;
      }
      break;

    case 1: // y-Axis
      for (byte z = 0; z < 5; z++) {
        for (byte x = 0; x < 5; x++) {
          _cubearray[25 * z + 5 * k + x] = color;
        }
      }
      break;

    case 2: // z-Axis
      for (byte i = 0; i < 25; i++) {
        _cubearray[25 * k + i] = color;
      }
      break;
  }
}
// Set all leds in the k-th normal plane of axis to values in colors.
void Cube::setPlane(byte axis, byte k, byte colors[25]) {
  byte i;
  switch(axis) {
    case 0: // x-Axis
      // i declared at top
      for (i = 0; i < 25; i++) {
        _cubearray[5 * i + k] = colors[i];
      }
      break;

    case 1: // y-Axis
      byte z;
      for (z = 0; z < 5; z++){
      byte x;
        for (x = 0; x < 5; x++) {
          _cubearray[25 * z + 5 * k + x] = colors[5 * z + x];
        }
      }
      break;

    case 2: // z-Axis
      // i declared at top
      for (i = 0; i < 25; i++) {
        _cubearray[25 * k + i] = colors[i];
      }
      break;
  }
}

// Set colors of a plane according to a blendMode:
// 0    default behavior
// 1    mask: only a color != 0 will have an effect
// 2    AND: store bitwise AND of current color and new color
// 3    OR: store bitwise OR of current color and new color
void Cube::setPlane(byte axis, byte k, byte colors[25], byte blendMode) {
  if (blendMode == 0) {
    setPlane(axis, k, colors);
  } else {
    switch(axis) {
      byte i;
      case 0: // x-Axis
        // i declared at top
        for (i = 0; i < 25; i++) {
          byte cubeIdx = 5 * i + k;

          if (blendMode == 1 && colors[i]) {
            _cubearray[cubeIdx] = colors[i];
          } else if (blendMode == 2) {
            _cubearray[cubeIdx] = _cubearray[cubeIdx] & colors[i];
          } else if (blendMode == 3) {
            _cubearray[cubeIdx] = _cubearray[cubeIdx] | colors[i];
          }
          
        }
        break;

      case 1: // y-Axis
      byte z;
        for (z = 0; z < 5; z++){
        byte x;
          for (x = 0; x < 5; x++) {
            byte cubeIdx = 25 * z + 5 * k + x;
            byte colorIdx = 5 * z + x;
            
            if (blendMode == 1 && colors[colorIdx]) {
              _cubearray[cubeIdx] = colors[colorIdx];
            } else if (blendMode == 2) {
              _cubearray[cubeIdx] = _cubearray[cubeIdx] & colors[colorIdx];
            } else if (blendMode == 3) {
              _cubearray[cubeIdx] = _cubearray[cubeIdx] | colors[colorIdx];
            }
          }
        }
        break;

      case 2: // z-Axis
        // i declared at top
        for (i = 0; i < 25; i++) {
          byte cubeIdx = 25 * k + i;

          if (blendMode == 1 && colors[i]) {
            _cubearray[cubeIdx] = colors[i];
          } else if (blendMode == 2) {
            _cubearray[cubeIdx] = _cubearray[cubeIdx] & colors[i];
          } else if (blendMode == 3) {
            _cubearray[cubeIdx] = _cubearray[cubeIdx] | colors[i];
          }
        }
        break;
  }
}
}
