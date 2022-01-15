// protects user from including library twice
#ifndef Writer_h
#define Writer_h

// include arduino default data types and functions
#include "Arduino.h"

// include cube object
#include "Cube.h"

class Writer {
    public:
        Writer(Cube &cube, byte serialData, byte serialShift);
        // writes the current state of the cube object to the hardware
        void writeCube();
        // resets the writers pwm cycle counter
        void reset();
        // returns the current write status (current pwm cycle or all HI if in standby)
        byte getState();
    private:
        // pointer to the cube the writer is responsible for
        Cube &_cube;
        // current pwm cycle form 0 to 3 as byte
        byte _pwmCounter;
        // pin number of pin used for serial data
        byte _serialData;
        // pin used for serial shift
        byte _serialShift;
        // writes the nth pwm cycle to the hardware
        void writeCube(byte cycleCount);
        // pushes a single high bit to the hardware cube
        void pushHigh();
        // pushes a single low bit to the hardware cube
        void pushLow();
};
#endif
