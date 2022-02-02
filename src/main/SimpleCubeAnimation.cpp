//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "SimpleCubeAnimation.h"

void SimpleCubeAnimation::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }
    _cube->clearLeds();

    if (counter == colorsTableSize) {
      counter = 0;
    }
    
    _cube->setBlock(1, colorsTable[(counter+3) % colorsTableSize], true, false, false);
    _cube->setBlock(2, colorsTable[(counter+2) % colorsTableSize], false, true, false);
    
    _cube->setBlock(2, colorsTable[(counter+1) % colorsTableSize], true, false, false);
    _cube->setBlock(3, colorsTable[(counter+1) % colorsTableSize], false, true, false);
    
    _cube->setBlock(3, colorsTable[counter % colorsTableSize], true, false, false);
    
    counter++;
}

SimpleCubeAnimation::SimpleCubeAnimation() {
  // set your Framerate here
  //int fps = 2; 
  //_frameDelta = 1000 / fps;
}
