//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "RandomColorsAnimation.h"

//.............................................
// DESCRIPTION:
// Every LED gets a random color assigned.
// After rcStart Frames, the randomness gets "swiped away" by
// a plane coming from a random direction.
//.............................................

void RandomColorsAnimation::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }
    //_cube->clearLeds(); // Can be removed if the whole cube doesn't need to be reset every frame
    byte i;
    for (i = 0; i < 125; i++) {
      _cube->setLed(i, rcColors[random(0,7)]);
    }
    if (rcFrame > rcStart) {
      if (rcLayerPos < 5) {
        
        for (i = 0; i <= rcLayerPos; i++) {
          _cube->setPlane(rcLayerAxis, i, rcLayerColor);
        }
      } else {
        
        for (i = rcLayerPos - 4; i <= 4; i++) {
          _cube->setPlane(rcLayerAxis, i, rcLayerColor);
        }
      }
      
      if (rcFrame == rcStart+10) {
        rcFrame = 0;
        rcLayerPos = 0;
        rcLayerAxis = random(0,3);
        rcLayerColor = rcColors[random(0,7)];
      } else {
        rcLayerPos++;
      }
    }
    
    rcFrame++;
}

RandomColorsAnimation::RandomColorsAnimation() {
  // set your Framerate here
  //int fps = 2; 
  //_frameDelta = 1000 / fps;
}
