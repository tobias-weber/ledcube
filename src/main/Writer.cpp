// include arduino default data types and functions
#include "Arduino.h"

// include header for Writer
#include "Writer.h"

// include header for cube

// Writer
Writer::Writer() {
}

// assigns the cube to this writer
void Writer::assignCube(Cube* cube){
  _cube = cube;
}

// pushes the next pwm cycle of the current cube to the hardware
void Writer::writeCube() {
  byte colorIndex;
  byte ledIndex; // 0-124
  byte layerIndex; // 0-4
  byte positionIndex; // 0-24
  byte ledData;
  unsigned long currentMicros;
  unsigned long previousMicros = micros();
  // read led bytes in reverse order
  for(layerIndex = 4; layerIndex < 255; layerIndex--) { // because of byte overflow, < 255 is equivalent to >= 0
    for (positionIndex = 24; positionIndex < 255; positionIndex--) { // because of byte overflow, < 255 is equivalent to >= 0
      ledIndex = layerIndex * 25 + positionIndex;
      // read pwm encoded intensity levels of each color
      ledData = _cube->getLed(ledIndex);
      for (colorIndex = 1; colorIndex < 0b100000; colorIndex <<= 2) {
        if (ledData & colorIndex) {
          // pushes a single high bit to the hardware cube
          PORTD = PORTD & B10011111;
          PORTD = PORTD | B01000000;;
        } else {
          // pushes a single low bit to the hardware cube
          PORTD = PORTD | B00100000;
          PORTD = PORTD & B10111111;
          PORTD = PORTD | B01000000;
        }
      }
    }
    // blacks the whole cube
    PORTD = PORTD | B00011111;
    // triggers the latch of the shift register
    PORTD = PORTD & B01111111;
    PORTD = PORTD | B10000000;
    // activates the selected layer
    // int used to prevent cast from modulo operator
    if (layerIndex == 0) {
      PORTD = PORTD & B11111110;
    } else if (layerIndex == 1) {
      PORTD = PORTD & B11111101;
    } else if (layerIndex == 2) {
      PORTD = PORTD & B11111011;
    } else if (layerIndex == 3) {
      PORTD = PORTD & B11110111;
    } else {
      PORTD = PORTD & B11101111;
    }
  }
  // Compensate for last layer
  int sleepTimeMicros = (micros() - previousMicros) / _PUSH_TIME_COMPENSATION_DIVISOR;
  previousMicros = micros();
  currentMicros = micros();
  while (currentMicros - previousMicros < sleepTimeMicros) {
    currentMicros = micros();
  }
  // blacks the whole cube
  PORTD = PORTD | B00011111;
}

// activates the selected layer
// int used to prevent cast from modulo operator
void Writer::setLayer(int layer) {
  // activates the selected layer
  // int used to prevent cast from modulo operator
  if (layer == 0) {
    PORTD = PORTD & B11111110;
  } else if (layer == 1) {
    PORTD = PORTD & B11111101;
  } else if (layer == 2) {
    PORTD = PORTD & B11111011;
  } else if (layer == 3) {
    PORTD = PORTD & B11110111;
  } else {
    PORTD = PORTD & B11101111;
  }
}
