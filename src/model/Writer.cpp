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
  digitalWrite(_mosfetLayer0 + layer, LOW);
}

// blacks the whole cube
void Writer::blackout() {
  digitalWrite(_mosfetLayer0, HIGH);
  digitalWrite(_mosfetLayer0 + 1, HIGH);
  digitalWrite(_mosfetLayer0 + 2, HIGH);
  digitalWrite(_mosfetLayer0 + 3, HIGH);
  digitalWrite(_mosfetLayer0 + 4, HIGH);
}

// triggers the latch ofa the shift register
void Writer::triggerLatch() {
  digitalWrite(_serialLatch, LOW);
  digitalWrite(_serialLatch, HIGH);
}

// pushes a single high bit to the hardware cube
void Writer::pushHigh() {
  digitalWrite(_serialData, LOW);
  digitalWrite(_serialShift, LOW);
  digitalWrite(_serialShift, HIGH);
}

// pushes a single low bit to the hardware cube
void Writer::pushLow() {
  digitalWrite(_serialData, HIGH);
  digitalWrite(_serialShift, LOW);
  digitalWrite(_serialShift, HIGH);
}
