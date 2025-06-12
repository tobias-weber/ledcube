//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "CombinedAnimation.h"

//.............................................
// DESCRIPTION:
// Adds an additional layer between main loop and animation that allows to
// switch between several different animations. This is achieved by holding
// X and pressing Y, or the other way around. That way users can cycle between
// animations.
// To change the brightness: hold X and Y and move the joystick in the 
// Y direction (fps of current animation determin change speed)
//.............................................

void CombinedAnimation::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    //_cube->setLed(0, COL_RED);
    if (!isConfigured) {
      initAnimation();
    }
    bool yReleased = isBtnYReleased();
    bool xReleased = isBtnXReleased();
    if (digitalRead(btnXPin) && yReleased) {
      cycleAnimation(1);
    } else if (digitalRead(btnYPin) && xReleased) {
      cycleAnimation(n-1);
    } else if (digitalRead(btnXPin) && digitalRead(btnYPin)) {
      //if (current == 0) _dimmingFactor = animations[current]->_dimmingFactor; // Only the first animation can set the dimming factor
      preciseDimming *= (1.0 + (2 - getJoyY()) / 30.0);
      if (preciseDimming > 255) preciseDimming = 255;
      if (preciseDimming < 0.9) preciseDimming = 0.9;
      _dimmingFactor = preciseDimming;
    } else {
      animations[current]->renderNextFrame();
    }
}

void CombinedAnimation::initAnimation() {
  for (int i = 0; i < n; i++) {
    animations[i]->assignCube(_cube);
    animations[i]->assignCharacterLibrary(_charLib);
    animations[i]->assignWriter(_writer);
  }
  isConfigured = true;
}

void CombinedAnimation::cycleAnimation(int i) {
  delay(500);
  if (!digitalRead(btnXPin) && !digitalRead(btnYPin)) {
    current = (current + i) % n;
    _frameDelta = animations[current]->_frameDelta;
    _cube->clearLeds();
  }
}

bool CombinedAnimation::isBtnXReleased() {
  bool isPressed = digitalRead(btnXPin);
  if (isPressed) {
    btnXPressed = true;
  } else if (btnXPressed){
    btnXPressed = false;
    return true;
  }
  return false;
}

bool CombinedAnimation::isBtnYReleased() {
  bool isPressed = digitalRead(btnYPin);
  if (isPressed) {
    btnYPressed = true;
  } else if (btnYPressed){
    btnYPressed = false;
    return true;
  }
  return false;
}

int CombinedAnimation::getJoyY() {
  int val = analogRead(joyYPin);
  byte calibratedVal = 0;
  for (byte i = 0; i < joyYnumOfRanges-1; i++) {
    if (val < joyYRanges[i]) break;
    calibratedVal++;
  }
  return calibratedVal;
}

// C O N S T R U C T O R
CombinedAnimation::CombinedAnimation() {
  // Initialize class variables declared in the header files here.
  // Arrays cant be initialized with {} notation. Either initialize every element separately
  // or initialize it in the header file

  // set your Framerate here
}
