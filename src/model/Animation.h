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
        // assigns a cube to this animation
        void assignCube(Cube* cube);
        // assigns a writer to this animation
        void assignWriter(Writer* writer);
        // pointer to the writer responsible for writing the cube
        Writer *_writer;
        // pointer to the cube used to store the next frame
        Cube *_cube;
};
#endif
