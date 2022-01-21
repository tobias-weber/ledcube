// include arduino default data types and functions
#include "Arduino.h"

#include <avr/pgmspace.h>

// include header for char LUT
#include "CharacterLUT.h"

// include header for Animation
#include "CharacterLibrary.h"

CharacterLibrary::CharacterLibrary() {
}

long CharacterLibrary::getCharacter(byte charIndex) {
    return pgm_read_dword(&CharacterLUT::_char_table[charIndex]);
}
