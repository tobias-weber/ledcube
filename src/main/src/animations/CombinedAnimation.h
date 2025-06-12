// protects user from including library twice
#ifndef CombinedAnimation_h
#define CombinedAnimation_h

#include "../Animation.h"

// include animations here
#include "HSVdemo.h"
#include "SnakeGame.h"
#include "MatrixRain.h"
#include "SpeedTest.h"
#include "SineAnimation.h"
#include "FadingCube.h"
#include "MovingLight.h"
#include "Tornado.h"


class CombinedAnimation:public Animation {
    private:
        // Here you can add an animation to the list. Don't forget to include it.
        HSVdemo hsv;
        SnakeGame snake;
        MatrixRain matrix;
        SpeedTest speedtest;
        SineAnimation sineAnimation;
        FadingCube fading;
        MovingLight movingLight;
        Tornado tornado;
        Animation* animations[8] = {&tornado, &movingLight, &hsv, &sineAnimation, &snake, &matrix, &speedtest, &fading}; // define order,
        
        const int n = sizeof(animations) / sizeof(void*); // number of animations, should be the
        int current; // index of current animation
        bool isConfigured = false;

        int joyYPin = A1;
        int joyXPin = A2;
        int btnXPin = A3;
        int btnYPin = A4;

        void initAnimation();
        void cycleAnimation(int i);
        bool isBtnYReleased();
        bool isBtnXReleased();
        int getJoyY();
        bool btnXPressed = false;
        bool btnYPressed = false;
        const byte joyYnumOfRanges = 5;
        const int joyYRanges[4] = {180, 305, 430, 555};

        double preciseDimming = 0.9;
    public:
        void renderNextFrame();
        CombinedAnimation();
};
#endif
