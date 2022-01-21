//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "TemplateAnimation.h"

//.............................................
//BEGIN: Variables used by this animation...
//.............................................

void TemplateAnimation::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }
    letter++;
}
