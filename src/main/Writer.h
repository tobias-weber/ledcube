// protects user from including library twice
#ifndef Writer_h
#define Writer_h

// include arduino default data types and functions
#include "Arduino.h"

// include cube object
#include "Cube.h"

class Writer {
    public:
        Writer(byte serialData, byte serialShift, byte serialLatch, byte mosfetLayer0);
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
        // pin number of pin used for serial data
        byte _serialData;
        // pin used for serial shift
        byte _serialShift;
        // pin used for first mosfet (layer 0)
        byte _mosfetLayer0;
        // pin used to trigger latch of shift register
        byte _serialLatch;
        // pushes a single high bit to the hardware cube
        void pushHigh();
        // pushes a single low bit to the hardware cube
        void pushLow();
        // activates the specified layer
        void setLayer(int layer);
        // blacks the whole cube
        void blackout();
        // enable latch of shift register
        void triggerLatch();
        // push time compensation
        const byte _PUSH_TIME_COMPENSATION = 1;
};
#endif
