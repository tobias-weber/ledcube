//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "TextAnimation.h"

void TextAnimation::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }
    _cube->clearLeds(); // Can be removed if the whole cube doesn't need to be reset every frame

    if (color > 5) {
      color = 0;
    }
    if (textLayer > 4) {
      textLayer = 0;
      letter++;
      color++;
    }
    if (letter > 16) {
      letter = 0;
      axis++;
    }
    if (axis > 2) {
      axis = 0;
    }

    byte* plane;
    plane = _charLib->getColoredCharacter(letters[letter], colors[color]);
    _cube->setPlane(axis, textLayer, plane);
    free(plane);
    textLayer++;

}

TextAnimation::TextAnimation() {
  // set your Framerate here
  //int fps = 2; 
  //_frameDelta = 1000 / fps;
}
