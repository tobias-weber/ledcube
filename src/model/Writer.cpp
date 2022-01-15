// include arduino default data types and functions
#include "Arduino.h"

// include header for Writer
#include "Writer.h"

// include header for cube
#include "Cube.h"


// Writer
Writer::Writer(Cube &cube, byte serialData, byte serialShift) {
    _cube = cube;
    this->_serialData = serialData;
    this->_serialShift = serialShift;
    this->_pwmCounter = 0;
}

// pushes the next pwm cycle of the current cube to the hardware
void Writer::writeCube() {
  // reset counter if previous pwm cycle is over
  if (_pwmCounter > 2) {
    _pwmCounter = 0;
  }
  // increases pwm counter AFTER call
  writeCube(_pwmCounter++);
}

// pushes the specified pwm cacle of the current cube to hardware
void Writer::writeCube(byte pwmCycle) {
  int ledIndex;
  byte ledData;
  byte redBits;
  byte greenBits;
  byte blueBits;
  // read led bytes in reverse order
  for(ledIndex = 124; ledIndex >= 0; ledIndex--) {
    // read pwm encoded intensity levels of each color
    ledData = _cube.getLed(ledIndex);
    blueBits = ledData & 0b11;
    ledData = ledData >> 2;
    greenBits = ledData & 0b11;
    ledData = ledData >> 2;
    redBits = ledData & 0b11;
    // set leds according to curren pwm cycle
    if (blueBits > pwmCycle) {
      pushHigh();
    } else {
      pushLow();
    }
    if (greenBits > pwmCycle) {
      pushHigh();
    } else {
      pushLow();
    }
    if (redBits > pwmCycle) {
      pushHigh();
    } else {
      pushLow();
    }
  }
}

// pushes a single high bit to the hardware cube
void Writer::pushHigh() {
  digitalWrite(_serialShift, LOW);
  digitalWrite(_serialData, HIGH);
  digitalWrite(_serialShift, HIGH);
}

// pushes a single low bit to the hardware cube
void Writer::pushLow() {
  digitalWrite(_serialShift, LOW);
  digitalWrite(_serialData, LOW);
  digitalWrite(_serialShift, HIGH);
}
