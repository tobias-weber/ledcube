// include arduino default data types and functions
#include "Arduino.h"

// include header for Cube
#include "Cube.h"

// include header for Animation
#include "Animation.h"

// contructor
Animation::Animation() {
}

//.............................................
//BEGIN: VARIABLES USED BY THIS ANIMATION...
//.............................................

float x_pos = 0;
float y_pos = 1;
float z_pos = 2;

float x_change = 1;
float y_change = 1;
float z_change = 1;

byte color = 0;
byte colors[] = {0b000001, 0b000100, 0b000101, 0b010000, 0b010001, 0b010100, 0b010101};

//...........................................
//END: VARIABLES USED BY THIS ANIMATION...
//...........................................

// assigns a cube to this animation
void Animation::assignCube(Cube* cube){
  _cube = cube;
}
// assigns a writer to this animation
void Animation::assignWriter(Writer* writer) {
  _writer = writer;
}
// calculates the next frame and updates the cube object
void Animation::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }
   
    //...................................
    //FRAME CALCULATION STARTS HERE...
    //...................................
    
    // turn of previous led
    _cube->setLed(round(x_pos), round(x_pos), round(x_pos), 0b0);
    // update position
    x_pos += x_change;
    y_pos += y_change;
    z_pos += z_change;
    // turn on new led
    _cube->setLed(round(x_pos), round(x_pos), round(x_pos), colors[color]);
    //update direction
    if (x_pos < 1 or x_pos > 4) {
      x_change = -x_change + randomDeviation();
      color = (color++ % 7);
    }
    if (y_pos < 1 or y_pos > 4){
      y_change = -y_change + randomDeviation();
      color = (color++ % 7);
    }
    if (z_pos < 1 or z_pos > 4){
      z_change = -z_change + randomDeviation();
      color = (color++ % 7);
    }
    
    //...................................
    //FRAME CALCULATION ENDS HERE...
    //...................................
}
// writes the next frame to the hardware
void Animation::showNextFrame() {
  // check if rewriting of current frame is already necessary. Minimizes jitter
  if (refreshIsToEarly()) {
      return;
  }
  _writer->writeCube();
}

// creates a random number from -0.4 to 0.4
float Animation::randomDeviation() {
  return (random(9) - 4) / 10.0;
}

// checks if the current frame is to early
bool Animation::frameIsToEarly() {
  if (millis() - _lastFrame < _frameDelta) {
    return true;
  }
   _lastFrame = millis();
   return false;
}

// checks if the current refresh is to early
bool Animation::refreshIsToEarly() {
  if (millis() - _lastRefresh < _refreshDelta) {
    return true;
  }
  _lastRefresh = millis();
  return false;
}
