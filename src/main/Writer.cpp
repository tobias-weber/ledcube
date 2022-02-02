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
  int ledIndex;
  int colorIndex;
  byte ledData;
  // read led bytes in reverse order
  for(ledIndex = 124; ledIndex >= -1; ledIndex--) {
    // blackout after last push
    if (ledIndex == -1) {
      delay(_PUSH_TIME_COMPENSATION);
      blackout();
      break;
    }
    // read pwm encoded intensity levels of each color
    ledData = _cube->getLed(ledIndex);
    for (colorIndex = 0; colorIndex < 6; colorIndex += 2) {
      if (ledData & (1 << colorIndex)) {
        pushHigh();
      } else {
        pushLow();
      }
    }
    if (ledIndex % 25 == 0) {
      blackout();
      triggerLatch();
      setLayer(ledIndex / 25);
    }  
  }
}

// activates the selected layer
// int used to prevent cast from modulo operator
void Writer::setLayer(int layer) {
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

// blacks the whole cube
void Writer::blackout() {
  PORTD = PORTD | B00011111;
}

// triggers the latch ofa the shift register
void Writer::triggerLatch() {
  PORTD = PORTD & B01111111;
  PORTD = PORTD | B10000000;
}

// pushes a single high bit to the hardware cube
void Writer::pushHigh() {
  PORTD = PORTD & B10011111;
  PORTD = PORTD | B01000000;
}

// pushes a single low bit to the hardware cube
void Writer::pushLow() {
  PORTD = PORTD | B00100000;
  PORTD = PORTD & B10111111;
  PORTD = PORTD | B01000000;
}
