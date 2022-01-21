//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "TextExampleAnimation.h"

//.............................................
//BEGIN: Variables used by this animation...
//.............................................
byte letter = 0;
byte letters[13] = {5, 20, 2, 10, 67, 24, 14, 20, 39, 67, 64, 67, 67};
byte kack = 0b010000;

void TextExampleAnimation::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }
    if (letter > 12) {
      letter = 0;
      kack = round(random(0, 2)) + (round(random(0, 2)) << 2) + (round(random(0, 2)) << 4);
    }
    byte* plane;
    plane = _charLib->getColoredCharacter(letters[letter], kack);
    _cube->setPlane(0, 4, plane);
    free(plane);
    letter++;
}
