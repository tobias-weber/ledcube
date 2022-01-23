//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "ExpandingSphereAnimation.h"

//.............................................
// DESCRIPTION:
// please describe your animation briefly
//
//
//.............................................

//.............................................
//BEGIN: Variables used by this animation...
//.............................................

int esCounter = 1;
byte esSize = 1;
byte esTargetSize = 4;
int esDirection = 1;
byte esColor = 0;
byte esInnerColor = 0;
byte esColors[] = {0b000001, 0b010000, 0b010100, 0b010001, 0b000101, 0b010101};

void ExpandingSphereAnimation::renderNextFrame() {
  // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
  if (frameIsToEarly()) {
    return;
  }
  _cube->clearLeds(); // Can be removed if the whole cube doesn't need to be reset every frame

  byte cageColor = 0b000100;
  switch (esCounter)
  {
  case 6:
    cageColor = 0b010001;
    break;

  case 5:
    cageColor = 0b010000;
    break;

  case 4:
    cageColor = 0b010100;
    break;
  }
  
  _cube->setLed(62, esColors[esColor]);
  _cube->setBlock(3, cageColor, true, false, false);

  _cube->setSphere(esCounter, esColors[esColor], true, false);
  _cube->setSphere(esCounter, esColors[esInnerColor], false, true);
  
  if (esCounter == 6) {
    _cube->setBlock(3, cageColor, true, true, false);
  }



  if (esCounter == esSize) {
    esDirection *= -1;
  } else if (esCounter == 0) {
    esDirection *= -1;

    esSize++;
    if (esSize > esTargetSize) {
      esSize = 1;
      esTargetSize = random(3, 7);
      esColor = random(0,6);
      esInnerColor = esColor; //(esColor+random(1,6)) % 6;
    }
  }
  esCounter += esDirection;

}

void ExpandingSphereAnimation::initialize() {
  int fps = 2; // set your Framerate here
  _frameDelta = 1000 / fps;
}
