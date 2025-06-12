// protects user from including library twice
#ifndef MovingLight_h
#define MovingLight_h

#include "../Animation.h"
#include "../Controller.h"

class MovingLight:public Animation {
    private:
        // Declare your class variables and your own methods here. 
        //int x=32,y=32,z=32;
        //int vx = 3, vy=2, vz=1;
        int xR[3] = {32, 32, 32};
        int xG[3] = {32, 32, 32};
        int xB[3] = {32, 32, 32};

        int vR[3] = {1, 2, 3};
        int vB[3] = {3, 1, 2};
        int vG[3] = {2, 3, 1};

        int* x[3] = {xR, xG, xB};
        int* v[3] = {vR, vG, vB};

        int sizeL[5] = {256,512,1024,2048,4096}; // 1024 is half the cube side, 4096 is full
        int sizeM[5] = {64,128,256,768,2048};
        int sizeS[5] = {32,64,128,256,640};
        int size = 2;

        Controller controller;

        int distanceToLed(byte id);
        int distanceToLed(int x, int y, int z, byte channel);
        int distance(int, int, int, int, int, int);
        byte colorFromDistance(int d);
        void reset();

    public:
        void renderNextFrame();
        MovingLight();
};
#endif
