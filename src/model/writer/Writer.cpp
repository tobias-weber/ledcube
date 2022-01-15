// include arduino default data types and functions
#include "Arduino.h"

// include header for Writer
#include "Writer.h"

// include header for cube
#include "Cube.h"

private Cube *_cube;
private byte _serialData;
private byte _serialShift
private byte _pwmCounter;

// Writer
Writer::Writer(Cube cube*, byte serialData, byte serialShift) {
    *_cube = cube;
    _serialData = serialData;
    _serialShift = serialShift;
    _pwmCounter = 0;
}

// pushes the next pwm cycle of the current cube to the hardware
Writer::writeCube() {
  // reset counter if previous pwm cycle is over
  if (_pwmCounter > 2) {
    _pwmCounter = 0;
  }
  // increases pwm counter AFTER call
  writeCube(_pwmCounter++)
}

// pushes the specified pwm cacle of the current cube to hardware
private Writer::writeCube(byte pwmCycle) {
  int ledIndex;
  byte ledData;
  byte redBits;
  byte greenBits;
  byte blueBits;
  // read led bytes in reverse order
  for(ledIndex = 124, ledIndex >= 0, ledIndex--) {
    // read pwm encoded intensity levels of each color
    ledData = Cube.getLed(ledIndex);
    blueBits = ledData & 0b11;
    ledBits = ledBits >> 2;
    greenBits = ledData & 0b11;
    ledBits = ledBits >> 2;
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
private Writer::pushHigh() {
  digitalWrite(_serialShift, LOW);
  digitalWrite(_serialData, HIGH);
  digitalWrite(_serialShift, Hight);
}

// pushes a single low bit to the hardware cube
private Writer::pushLow() {
  digitalWrite(_serialShift, LOW);
  digitalWrite(_serialShift, Hight);
}

