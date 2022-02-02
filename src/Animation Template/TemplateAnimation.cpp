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

void TemplateAnimation::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }
    _cube->clearLeds(); // Can be removed if the whole cube doesn't need to be reset every frame
}

// C O N S T R U C T O R
TemplateAnimation::TemplateAnimation() {
  // Initialize class variables declared in the header files here.
  // Arrays cant be initialized with {} notation. Either initialize every element separately
  // or initialize it in the header file

  // set your Framerate here
  //int fps = 2; 
  //_frameDelta = 1000 / fps;
}
