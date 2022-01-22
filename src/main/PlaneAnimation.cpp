//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "PlaneAnimation.h"

//.............................................
//BEGIN: Variables used by this animation...
//.............................................
byte state = 0;
byte layer = 0;

void PlaneAnimation::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }
    _cube->clearLeds() // Can be removed if the whole cube doesn't need to be reset every frame
    if (layer > 4) {
      layer = 0;
      state++;
    }
    if (state > 3) {
      state = 0;
    }

    // axis 0 solo
    if (state = 0) {
      _cube->setPlane(0, layer, 0b010000);
    } else if (state = 1) {
      _cube->setPlane(1, layer, 0b000100);
    } else if (state = 2) {
      _cube->setPlane(2, layer, 0b000001);
    } else if (state = 3) {
      _cube->setPlane(0, layer, 0b010000);
      _cube->setPlane(1, layer, 0b000100, 3);
      _cube->setPlane(2, layer, 0b000001, 3);
    }
    layer++;
}
