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



        // B L E N D M O D E S
        // 0    default behavior
        // 1    mask: only a color != 0 will have an effect
        // 2    AND: store bitwise AND of current color and new color
        // 3    OR: store bitwise OR of current color and new color

        // Set colors of a plane according to a blendMode
        void setPlane(byte axis, byte k, byte color);
        void setPlane(byte axis, byte k, byte colors[25]);
        void setPlane(byte axis, byte k, byte colors[25], byte blendMode); 
        void setPlane(byte axis, byte k, byte color, byte blendMode);

        // Size 1..3
        void setBlock(byte size, byte color, bool drawEdges, bool drawFaces, bool drawFill);

        // Size in 1..6. Watch out: 6 is too large to fit in 5x5x5 cube
        void setSphere(byte size, byte color, bool drawSurface, bool drawFill);

        // Draws a diagonal plane.
        // axis: the axis in which the plane lies
        // k: the k-th diagonal plane will be drawn
        // blendMode: 1 = Mask doesn't really make sense here
        // isFlipped: If true, plane is turned around axis by 90 degrees
        void setDiagonalPlane(byte axis, byte k, byte color, byte blendMode, bool isFlipped);

        // Draws a single straight line. The line starts at start, goes in the (+) direction of axis and
        // extends for length leds
        void setStraightLine(byte axis, byte start, byte length, byte color, byte blendMode);

        // Draws the edges of a rotated cube
        // Rotation: 0..3   (0 is unrotated, the next rotation after 3 would be 0 again)
        void setRotatedBlock(byte rotation, byte color);
};
#endif
