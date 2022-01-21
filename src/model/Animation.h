// protects user from including library twice
#ifndef Animation_h
#define Animation_h

// include arduino default data types and functions
#include "Arduino.h"

//include header for Cube
#include "Cube.h"

//include header for Writer
#include "Writer.h"

//include header for char lib
#include "CharacterLibrary.h"

class Animation {
    public:
        Animation();
        // calculates the next frame and updates the cube object
        virtual void renderNextFrame() = 0;
        // writes the next frame to the hardware
        void showNextFrame();
        // assigns a cube to this animation
        void assignCube(Cube* cube);
        // assigns a writer to this animation
        void assignWriter(Writer* writer);
        // assigns a character library to the animation
        void assignCharacterLibrary(CharacterLibrary* characterLibrary);
        // pointer to the writer responsible for writing the cube
        Writer *_writer;
        // pointer to the cube used to store the next frame
        Cube *_cube;
        //pointer to the character library
        CharacterLibrary *_charLib;
        // time since last render
        long _lastFrame;
        // time since last write
        long _lastRefresh;
        // refresh rate of cube >>> D O N ' T  T O U C H! <<<
        const float _refreshDelta = 0;
        // framerate of the animation
        const float _frameDelta = 1000 / 2;
        // checks if frame is to early
        bool frameIsToEarly();
        // checks if frame is to early
        bool refreshIsToEarly();
};
#endif
