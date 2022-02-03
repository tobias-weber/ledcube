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
        // gamma corrected intensity values
        byte _gammaIntensities[4] = {0, 1, 4, 8};
};
#endif
