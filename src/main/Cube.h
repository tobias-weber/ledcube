//protects user from including library twice
#ifndef Cube_h
#define Cube_h

//include arduino default data types and functions
#include "Arduino.h"

class Cube {
    private:
        byte _cubearray[125] = {0};
        byte _saturatedColors[18] = {
            0b110000,
            0b110100,
            0b111000,
            0b111100,
            0b101100,
            0b011100,
            0b001100,
            0b001101,
            0b001110,
            0b001111,
            0b001011,
            0b000111,
            0b000011,
            0b010011,
            0b100011,
            0b110011,
            0b110010,
            0b110001};
    public:
        Cube();
        // set all leds to 0
        void clearLeds();
        // set all leds to the color specified
        void setLeds(byte color);
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
        // return 6 bit color from hue, saturation and value. Warning: Slow
        byte getColorFromHSV(int hue, float saturation, float value);
        // return 6 bit color from an index (0..18) that corresponds to the hue.
        byte getSaturatedColor(byte index);
        



        // B L E N D M O D E S
        // 0    default behavior
        // 1    mask: only a color != 0 will have an effect
        // 2    AND: store bitwise AND of current color and new color
        // 3    OR: store bitwise OR of current color and new color
        // 4    XOR: store bitwise XOR of current color and new color
        // 5    oldHasPriority: only if the previously stored color is 0, the new color will be stored

        // set color of single Led with blendMode
        void setBlendedLed(byte id, byte color, byte blendMode);
        // copy the contents of the given byte array(must have length 125) into the cubearray
        void setCube(byte* src);
        // copy the contents of the cube array into the given byte array (must have length 125)
        void copyCube(byte* dst);

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
};
#endif
