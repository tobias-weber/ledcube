// include arduino default data types and functions
#include "Arduino.h"

// include header for Writer
#include "Writer.h"

// include header for cube

// Writer
Writer::Writer(byte serialData, byte serialShift, byte serialLatch, byte mosfetLayer0) {
    this->_serialData = serialData;
    this->_serialShift = serialShift;
    this->_serialLatch = serialLatch; 
    this->_mosfetLayer0 = mosfetLayer0;
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
  for(ledIndex = 124; ledIndex >= 0; ledIndex--) {
    // read pwm encoded intensity levels of each color
    ledData = _cube->getLed(ledIndex);
    for (colorIndex = 0; colorIndex < 6; colorIndex += 2) {
      if (ledData & (1 << colorIndex)) {
        pushHigh();
      } else {
        pushLow();
      }
    }
  }
  
}

// activates the selected layer
// int used to prevent cast from modulo operator
void Writer::setLayer(int layer) {
  int pinIncrement;
  for (pinIncrement = 0; pinIncrement < 4; pinIncrement++) {
    if (layer == pinIncrement) {
      digitalWrite(_mosfetLayer0 + pinIncrement, HIGH);
      continue;
    }
    digitalWrite(_mosfetLayer0 + pinIncrement, LOW);
  }
}

// triggers the latch ofa the shift register
void Writer::triggerLatch() {
  digitalWrite(_serialLatch, LOW);
  digitalWrite(_serialLatch, HIGH);
}

// pushes a single high bit to the hardware cube
void Writer::pushHigh() {
  digitalWrite(_serialData, HIGH);
  digitalWrite(_serialShift, LOW);
  digitalWrite(_serialShift, HIGH);
}

// pushes a single low bit to the hardware cube
void Writer::pushLow() {
  digitalWrite(_serialData, LOW);
  digitalWrite(_serialShift, LOW);
  digitalWrite(_serialShift, HIGH);
}
