//protects user from including library twice
#ifndef Cube_h
#define Cube_h

//include arduino default data types and functions
#include "Arduino.h"

class Cube {
    public:
        Cube();
        // set all leds to 0
        void clearLeds();
        // set color by specifying x,y,z
        void setLed(byte x, byte y, byte z, byte color);
        // set color with unique led id (0-124)
        void setLed(byte id, byte color);
        // set color by specifying layer and led number on that layer
        void setLed(byte z, byte k, byte color);
        // returns the byte of the led at x,y,z
        byte getLed(byte x, byte y, byte z);
        // returns the byte of the led by unique led id (0-124)
        byte getLed(byte id);
        // color is returned in the format: 0b2b1g2g1r2r1
        byte getColor(byte r, byte g, byte b);

        void setPlane(byte axis, byte k, byte color);
        void setPlane(byte axis, byte k, byte colors[25]);
        void setPlane(byte axis, byte k, byte colors[25], byte blendMode); 
        void setPlane(byte axis, byte k, byte color, byte blendMode);    
};
#endif
