//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "HSVdemo.h"

//.............................................
// DESCRIPTION:
// Shows a rainbow effect that moves diagonally through the cube.
// To make the transition smoother (and thus allow for a slower smooth movement of the rainbow), 
// the leds are updated randomly instead of every single frame.
// By using the joystick, the speed of the animation can be temporarily changed.
//.............................................

void HSVdemo::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }

    if(_cube->getLed(0) == 0) _cube->setLeds(COL_WHITE); // in the beginning, set the cube to white

    if (digitalRead(btnXPin) && isBtnYReleased()) {
      _cube->setBlock(3, COL_CYAN, true, true, true);
    }

    byte calibratedY = getCalibratedY();
    for (byte x = 0; x < 5; x++) {
      for (byte y = 0; y < 5; y++) {
        byte rand = random(25 - 3 * calibratedY); // Select a random diagonal plane that becomes editable (the highest plane inside the cube is 12)
        for (byte z = 0; z < 5; z++) {
          byte distance = x+y+z;
          if (rand == distance) { // if the led is in the editable plane, update its color
            byte color = _cube->getSaturatedColor(hue + distance);
            _cube->setLed(x,4-y, 4-z, color); // animation starts at x=4, y=0, z=0
          }
        }
      }
      
    }
    counter++;
    if (counter >= velocities[calibratedY]) { // go to the next color every n frames
      counter = 0;
      hue = (hue + 1) % 18;
    }
}

int HSVdemo::getCalibratedY() {
  int val = analogRead(joyYPin);
  byte calibratedVal = 0;
  for (byte i = 0; i < joyYnumOfRanges-1; i++) {
    if (val < joyYRanges[i]) break;
    calibratedVal++;
  }
  return calibratedVal;
}

bool HSVdemo::isBtnXReleased() {
  bool isPressed = digitalRead(btnXPin);
  if (isPressed) {
    btnXPressed = true;
  } else if (btnXPressed){
    btnXPressed = false;
    return true;
  }
  return false;
}

bool HSVdemo::isBtnYReleased() {
  bool isPressed = digitalRead(btnYPin);
  if (isPressed) {
    btnYPressed = true;
  } else if (btnYPressed){
    btnYPressed = false;
    return true;
  }
  return false;
}

// C O N S T R U C T O R
HSVdemo::HSVdemo() {
  // Initialize class variables declared in the header files here.
  // Arrays cant be initialized with {} notation. Either initialize every element separately
  // or initialize it in the header file

  // set your Framerate here
  int fps = 60; 
  _frameDelta = 1000 / fps;

  
  joyYPin = A1;
  joyXPin = A2;
  btnXPin = A3;
  btnYPin = A4;
}
