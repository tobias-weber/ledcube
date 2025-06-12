//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "MovingLight.h"

//.............................................
// DESCRIPTION:
// please describe your animation briefly
//
//
//.............................................

void MovingLight::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }
    _cube->clearLeds(); // Can be removed if the whole cube doesn't need to be reset every frame
    controller.tick();
    if (controller.isBtnXReleased()) {
      _cube->setBlock(3, COL_WHITE, true, true, false);
      reset();
      return;
    }
    if (controller.isBtnYPressed()) size = controller.getJoyY();

    for (int channel = 0; channel < 3; channel++) {
      for (int i = 0; i < 3; i++) {
        x[channel][i] += v[channel][i];
        int xCurr = x[channel][i];
        int vCurr = v[channel][i];
        if ((vCurr > 0 && xCurr > 64-vCurr) || (vCurr < 0 && xCurr < -vCurr)) v[channel][i] = -vCurr;
      }
    }

    for (int x1 = 0; x1 < 5; x1++) {
      for (int y1 = 0; y1 < 5; y1++) {
        for (int z1 = 0; z1 < 5; z1++) {
          byte cR = colorFromDistance(distanceToLed(x1, y1, z1, 0));
          byte cG = colorFromDistance(distanceToLed(x1, y1, z1, 1));
          byte cB = colorFromDistance(distanceToLed(x1, y1, z1, 2));
          byte color = cR << 4 | cG << 2 | cB;
          _cube->setLed(x1, y1, z1, color);
        }
      }
    }
}

int MovingLight::distanceToLed(int x1, int y1, int z1, byte channel) {
  return distance(x1 << 4, y1 << 4, z1 << 4, x[channel][0], x[channel][1], x[channel][2]);
}

// Returns value between 0 and 128^2
int MovingLight::distance(int x1, int y1, int z1, int x2, int y2, int z2) {
  int dx = x1-x2;
  int dy = y1-y2;
  int dz = z1-z2;
  return dx*dx + dy*dy + dz*dz;
}

byte MovingLight::colorFromDistance(int d) {
  if (d > sizeL[size]) return 0b0;
  if (d > sizeM[size]) return 0b01;
  if (d > sizeS[size]) return 0b10;
  return 0b11;
}

void MovingLight::reset() {
  randomSeed(micros());
  for (int channel = 0; channel < 3; channel++) {
      for (int i = 0; i < 3; i++) {
        x[channel][i] = random(16, 49);
        v[channel][i] = random(1, 6);
        if (random(2) == 1) v[channel][i] = -v[channel][i];
      }
    }
}

// C O N S T R U C T O R
MovingLight::MovingLight() {
  // Initialize class variables declared in the header files here.
  // Arrays cant be initialized with {} notation. Either initialize every element separately
  // or initialize it in the header file

  // set your Framerate here
  int fps = 10; 
  _frameDelta = 1000 / fps;
  reset();
}
