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
byte spawn = 125;
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
        if (_cube->getLed(25 * layer + ledID) == 0 && _cube->getLed(25 * (layer + 1) + ledID) > 0) {
          _cube->setLed(layer, ledID, 0b000101);

        } else if (_cube->getLed(25 * (layer + 1) + ledID) > 0){
          _cube->setLed(layer, ledID, 0b000100);

        } else {
          _cube->setLed(layer, ledID, 0);
        }
      }
    }

    for (layer = 0; layer < 4; layer++) {
      for (ledID = 0; ledID < 25; ledID++) {
        if (_cube->getLed(25 * layer + ledID) == 0 && _cube->getLed(25 * (layer + 1) + ledID) > 0) {
        }
      }
    }
    // clear upper layer
    _cube->setPlane(2, 4, (byte) 0);
    // add trail of previous drop
    if (spawn < 125) {
      _cube->setLed(spawn, 0b000100);
    }
    // spawn new drop
    if (random(0, 99) < spawnProbability) {
      if (random(0,4) <= 2) {
        // 75 %
        spawn = random(0, 25) + 100;
        _cube->setLed(spawn, 0b000100);
      }
    } else {
      spawn = 125;
    }
    // set new drop
}

void MatrixRain::initialize() {
  // set your Framerate here
  int fps = 10; 
  _frameDelta = 1000 / fps;
}
