#ifndef CharacterLibrary_h
#define CharacterLibrary_h

class CharacterLibrary {
    public:
        CharacterLibrary();
        long getCharacter(byte charIndex);
        byte* getColoredCharacter(byte charIndex, byte color);
};
#endif
