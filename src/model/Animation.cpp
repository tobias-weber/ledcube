// include arduino default data types and functions
#include "Arduino.h"

// include header for Cube
#include "Cube.h"

// include header for Animation
#include "Animation.h"

// include character lut
#include "CharacterLUT.h"

//.............................................
//BEGIN: Variables used by this animation...
//.............................................

int x_pos = 0;
int y_pos = 1;
int z_pos = 2;

int x_change = 1;
int y_change = 1;
int z_change = 1;

byte color = 0;
byte colors[] = {0b000001, 0b000100, 0b000101, 0b010000, 0b010001, 0b010100, 0b010101};

//...........................................
//END: Variables used by this animation...
//...........................................

// calculates the next frame and updates the cube object
void Animation::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }
   
    //...................................
    //BEGIN: Frame calculations...
    //...................................
    
    // turn of previous led
    
    _cube->setLed(lowByte(x_pos), lowByte(y_pos), lowByte(z_pos), 0b0);
    // update position
    x_pos = limit(x_pos + x_change);
    y_pos = limit(y_pos + y_change);
    z_pos = limit(z_pos + z_change);
    
    // turn on new led
    _cube->setLed(lowByte(x_pos), lowByte(y_pos), lowByte(z_pos), colors[color]);
    //update direction
    if (x_pos < 1 or x_pos > 3) {
      x_change = newDirection(x_change);
      color++;
      if (color > 6) {
        color = 0;
      }
    }
    if (y_pos < 1 or y_pos > 3){
      y_change = newDirection(y_change);
      color++;
      if (color > 6) {
        color = 0;
      }
    }
    if (z_pos < 1 or z_pos > 3){
      z_change = newDirection(z_change);
      color++;
      if (color > 6) {
        color = 0;
      }
    }
    _cube->setPlane(0,2,0b000001);
    _cube->setPlane(1,2,0b010000,3);
    _cube->setPlane(2,2,0b000100,3);
    //...................................
    //END: Frame calculations...
    //...................................
}

//.............................................
//BEGIN: Helper methods for animation...
//.............................................
// creates a random number from -0.4 to 0.4
int Animation::newDirection(int oldDirection) {
  int r = random(2) + 1;
  //int r = 1;
  if (oldDirection > 0) {
    r *= -1;
  }
  return r;
}

// maps positions outside of the cube to the nearest pixel
int Animation::limit(int coord) {
  if (coord < 0) {
    return 0;
  }
  if (coord > 5) {
    return 5;
  }
  return coord; 
}
//.............................................
//END: Helper methods for animation...
//.............................................

// contructor
Animation::Animation() {
}

// assigns a cube to this animation
void Animation::assignCube(Cube* cube){
  _cube = cube;
}

// assigns a writer to this animation
void Animation::assignWriter(Writer* writer) {
  _writer = writer;
}

void Animation::assignCharacterLibrary(CharacterLibrary* characterLibrary) {
  _charLib = characterLibrary;
}

// writes the next frame to the hardware
void Animation::showNextFrame() {
  // check if rewriting of current frame is already necessary. Minimizes jitter
  if (refreshIsToEarly()) {
      return;
  }
  _writer->writeCube();
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
