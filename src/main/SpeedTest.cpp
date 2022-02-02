//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "SpeedTest.h"

//.............................................
// DESCRIPTION:
// please describe your animation briefly
//
//
//.............................................

void SpeedTest::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }    
    
    _cube->setLed(index, 0);
    color++;
    if (color == 7) {
      color = 0;
      if (index == 124) {
        index = 0;
      } else {
        index++;
      }
    }
    _cube->setLed(index, colors[color]);
}

// C O N S T R U C T O R
SpeedTest::SpeedTest() {
  // Initialize class variables declared in the header files here.
  // Arrays cant be initialized with {} notation. Either initialize every element separately
  // or initialize it in the header file

  // set your Framerate here
  int fps = 1000; 
  _frameDelta = 1000 / fps;
}
