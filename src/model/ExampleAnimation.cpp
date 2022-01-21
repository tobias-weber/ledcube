//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "ExampleAnimation.h"

//.............................................
//BEGIN: Variables used by this animation...
//.............................................


void ExampleAnimation::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }
   
}
