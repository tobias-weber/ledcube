//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "DiagonalPlaneAnimation.h"

//.............................................
// DESCRIPTION:
// please describe your animation briefly
//
//
//.............................................

//.............................................
//BEGIN: Variables used by this animation...
//.............................................
byte dpCounter = 0;
boolean dpFlip = false;

void DiagonalPlaneAnimation::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }
    _cube->clearLeds(); // Can be removed if the whole cube doesn't need to be reset every frame
    int k;
    _cube->setDiagonalPlane(0, dpCounter, 0b010000, 3, dpFlip);
    _cube->setDiagonalPlane(1, dpCounter, 0b000100, 3, dpFlip);
    _cube->setDiagonalPlane(2, dpCounter, 0b000001, 3, dpFlip);
    dpCounter++;
    if (dpCounter == 9) {
      dpCounter = 0;
    }
}

void DiagonalPlaneAnimation::initialize() {
  // set your Framerate here
  int fps = 2; 
  _frameDelta = 1000 / fps;
}
