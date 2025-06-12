// include arduino default data types and functions
#include "Arduino.h"

#if (defined(__AVR__))
#include <avr\pgmspace.h>
#else
#include <pgmspace.h>
#endif

// include header for char LUT
#include "CharacterLUT.h"

// include header for Animation
#include "CharacterLibrary.h"

CharacterLibrary::CharacterLibrary() {
}

long CharacterLibrary::getCharacter(byte charIndex) {
    return pgm_read_dword(&CharacterLUT::_char_table[charIndex]);
}

byte* CharacterLibrary::getColoredCharacter(byte charIndex, byte color) {
  long pattern = getCharacter(charIndex);
  byte* plane = (byte*) malloc(25*sizeof(byte));
  byte idx;
  for (idx = 25; idx > 0; idx--) {
    if (pattern & 0b1) {
      plane[idx-1] = color;
    } else {
      plane[idx-1] = 0;
    }
    pattern = pattern>>1;
  }
  return plane;
}
