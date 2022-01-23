//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "TemplateAnimation.h"

//.............................................
// DESCRIPTION:
// please describe your animation briefly
//
//
//.............................................

//.............................................
//BEGIN: Variables used by this animation...
//.............................................

void TemplateAnimation::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }
    _cube->clearLeds(); // Can be removed if the whole cube doesn't need to be reset every frame
}

void TemplateAnimation::initialize() {
  // set your Framerate here
  //int fps = 2; 
  //_frameDelta = 1000 / fps;
}
