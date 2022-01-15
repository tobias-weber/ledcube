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
        Animation();
        // calculates the next frame and updates the cube object
        void renderNextFrame();
        // writes the next frame to the hardware
        void showNextFrame();
    private:
        Cube *_cube;
        Writer *_writer;
        const byte _serialData;
        const byte _serialShift;
};
#endif