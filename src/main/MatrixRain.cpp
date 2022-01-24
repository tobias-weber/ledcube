//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "MatrixRain.h"

//.............................................
// DESCRIPTION:
// please describe your animation briefly
//
// green reindops falling down, similar to the
// famous green letter rain animation in matrix
//.............................................

//.............................................
//BEGIN: Variables used by this animation...
//.............................................
byte spawn = 0;
byte spawnProbability = 100;

void MatrixRain::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }
    // make drops fall
    byte layer;
    byte ledID;
    for (layer = 0; layer < 4; layer++) {
      for (ledID = 0; ledID < 25; ledID++) {
        _cube->setLed(layer, ledID, _cube->getLed(25 * layer + ledID))
      }
    }
    // clear upper layer
    _cube->setPlane(2, 4, 0);
    // add trail of previous drop
    _cube->setLed(spawn, 0b000100);
    // spawn new drop
    if (random(0, 99) < spawnProbability) {
      spawn = random(0, 25);
    } else {
      spawn = 0;
    }
    // set new drop
    _cube->setLed(spawn, 0b000100);
}

void MatrixRain::initialize() {
  // set your Framerate here
  int fps = 5; 
  _frameDelta = 1000 / fps;
}
