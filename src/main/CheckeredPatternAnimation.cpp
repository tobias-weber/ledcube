//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "CheckeredPatternAnimation.h"

//.............................................
// DESCRIPTION:
// Displays a nice (just 2 Frame long) Pattern
//
//
//.............................................

//.............................................
//BEGIN: Variables used by this animation...
//.............................................
byte cpFrame = 0;

void CheckeredPatternAnimation::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }
    _cube->clearLeds(); // Can be removed if the whole cube doesn't need to be reset every frame
    
    byte colors[] = {0b000001, 0b010000, 0b000100, 0b010100, 0b010001, 0b000101, 0b010101};
    byte* darkPlane0;
    byte* lightPlane0;
    byte* darkPlane1;
    byte* lightPlane1;
    
    darkPlane0 = _charLib->getColoredCharacter(66, colors[1]);
    lightPlane0 = _charLib->getColoredCharacter(65, colors[4]);
    darkPlane1 = _charLib->getColoredCharacter(66, colors[5]);
    lightPlane1 = _charLib->getColoredCharacter(65, colors[2]);

    
    byte i;
    for (i = 0; i < 5; i++) {
      if ((i+cpFrame) % 2) {
        _cube->setPlane(0, i, darkPlane0, 1);
        _cube->setPlane(0, i, lightPlane1, 1);
      } else {
        _cube->setPlane(0, i, lightPlane0, 1);
        _cube->setPlane(0, i, darkPlane1, 1);

      }
    }
    free(darkPlane0);
    free(lightPlane0);
    free(darkPlane1);
    free(lightPlane1);
    cpFrame = (cpFrame + 1) % 2;
}

void CheckeredPatternAnimation::initialize() {
  // set your Framerate here
  //int fps = 2; 
  //_frameDelta = 1000 / fps;
}
