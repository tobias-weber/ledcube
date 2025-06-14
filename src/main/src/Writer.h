// protects user from including library twice
#ifndef Writer_h
#define Writer_h

// include arduino default data types and functions
#include "Arduino.h"

// include cube object
#include "Cube.h"

class Writer {
    public:
        Writer();
        // assigns the cube to the writer
        void assignCube(Cube* cube);
        // writes the current state of the cube object to the hardware
        void writeCube();
        // like write, but allows for dimming controll (0-255). Results in fewer fps!
        void writeCube(byte dim);
        // resets the writers pwm cycle counter
        void reset();
        // returns the current write status (current pwm cycle or all HI if in standby)
        byte getState();
    private:
        // pointer to the cube the writer is responsible for
        Cube *_cube;
        // push time compensation
        // the higher this value, the shorter layer 0 will light up compared to the other layers
        const byte _PUSH_TIME_COMPENSATION_DIVISOR = 10;
        // counter for the pwn subframes
        byte _pwmSubframe = 0;

        // Gamma corrected intensity values. 
        // Defines for how many subframes a color-channel of an led will be active,
        // depending on its intensity value (that indexes this array).
        // Entry with index 0b11 defines total number of subframes.
        void writeSubframe();
        byte _gammaIntensities[4] = {0, 1, 4, 10};

        byte _gammaLevelR = 0;
        byte _gammaLevelG = 0;
        byte _gammaLevelB = 0;

        // Dimming
        int _dimPauseMicros = 2500; // Total dimming time is _dimPauseMicros * _gammaIntensities[3]
};
#endif
