// protects user from including library twice
#ifndef Animation_h
#define Animation_h

// include arduino default data types and functions
#include "Arduino.h"

//include header for Cube
#include "Cube.h"

//include header for Writer
#include "Writer.h"

class Animation {
    public:
        Animation(byte serialData, byte serialShift, byte layer0);
        // calculates the next frame and updates the cube object
        void renderNextFrame();
        // writes the next frame to the hardware
        void showNextFrame();
        // pin used for serial data
        byte _serialData;
        // pin used for serial shift 
        byte _serialShift;
        // pin used for first mosfet (layer 0)
        byte _mosfetLayer0;
        // pointer to the writer used to write animation to cube
        Writer *_writer;
};
#endif
