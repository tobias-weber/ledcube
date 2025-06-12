// protects user from including library twice
#ifndef Tornado_h
#define Tornado_h

#include "../Animation.h"
#include "../Controller.h"

class Tornado:public Animation {
    private:
        // Declare your class variables and your own methods here. 
        Controller controller;

        //byte circle[12] = {1,2,3,9,14,19,23,22,21,15,10,5};
        byte circle[16] = {0,1,2,3,4,9,14,19,24,23,22,21,20,15,10,5};
        byte square[8] = {6,7,8,13,18,17,16,11};
        double phase = 0;
        double time = 0;
        bool reversed = false;
        byte speedSelection = 2;
        //double speed[5] = {0.25,0.5,0.75,1.5,3};
        double speed[5] = {0.01,0.12,0.3,0.6,1};
        byte colors[12] = {
            0b110000,//            0b110100,
            0b111000,
            0b111100,
            0b101100,//            0b011100,
            0b001100,
            0b001101,//            0b001110,
            0b001111,
            0b001011,//            0b000111,
            0b000011,
            0b010011,//            0b100011,
            0b110011,//            0b110010//,            
            0b110001
            };
        byte allColors[18] = {
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
        byte getOffset(double time);
    public:
        void renderNextFrame();
        Tornado();
};
#endif
