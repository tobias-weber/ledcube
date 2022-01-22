//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "TextAnimation.h"

//.............................................
//BEGIN: Variables used by this animation...
//.............................................
byte letter = 0;
byte axis = 0;
byte layer = 0;
byte color = 0;
byte letters[17] = {2, 1, 19, 2, 7, 28, 26, 67, 15, 17, 14, 9, 4, 10, 19, 67, 64};
byte colors[6] = {0b000001, 0b010001, 0b010000, 0b010100, 0b000100, 0b000101};

void TextExampleAnimation::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }
    if (color > 5) {
      direction = 0;
    }
    if (layer > 4) {
      direction = 0;
      letter++;
    }
    if (letter > 16) {
      leter = 0;
      axis++;
    }
    if (axis > 2) {
      axis = 0;
    }

    byte* plane;
    plane = _charLib->getColoredCharacter(letters[letter], colors[color]);
    _cube->setPlane(axis, layer, plane);
    free(plane);
    layer++;
    color++;
}
