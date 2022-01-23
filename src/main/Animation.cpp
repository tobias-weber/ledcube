// include arduino default data types and functions
#include "Arduino.h"

// include header for Cube
#include "Cube.h"

// include header for Animation
#include "Animation.h"

// include character lut
#include "CharacterLUT.h"

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

void Animation::initialize() {
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
