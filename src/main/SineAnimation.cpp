//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "SineAnimation.h"

//.............................................
// DESCRIPTION:
// please describe your animation briefly
//
//
//.............................................

//.............................................
//BEGIN: Variables used by this animation...
//.............................................
float sineCounter = 0;
float edge = PI * 3 / 5;
byte sineColors[] = {0b000001, 0b000101, 0b000100, 0b010100, 0b010000};

void SineAnimation::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }
    _cube->clearLeds(); // Can be removed if the whole cube doesn't need to be reset every frame
    float z;
    int Z;
    float phase = sineCounter;
    for(int x = 0; x < 5; x++){
      for(int y = 0; y < 5; y++){
        z = sin(phase + sqrt(pow(fmap(x,0,4,-edge,edge),2) + pow(fmap(y,0,4,-edge,edge),2)));
        Z = round(fmap(z,-1,1,0.25,3.75));
        _cube->setLed(x,y,Z, sineColors[Z]);
      }
    }
    sineCounter += 0.2;
    if (sineCounter > 2 * PI) {
      sineCounter = 0;
    }
}

float SineAnimation::fmap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void SineAnimation::initialize() {
  // set your Framerate here
  int fps = 15; 
  _frameDelta = 1000 / fps;
}
