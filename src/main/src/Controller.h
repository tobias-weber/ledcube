#ifndef Controller_h
#define Controller_h

#include "Arduino.h"

class Controller {
    private:
        const int joyYPin = A1;
        const int joyXPin = A2;
        const int btnXPin = A3;
        const int btnYPin = A4;
        bool btnXPressed = false;
        bool btnYPressed = false;
        bool btnXReleased = false;
        bool btnYReleased = false;
        const byte joyXnumOfRanges = 5;
        const int joyXRanges[4] = {150, 300, 400, 550};
        const byte joyYnumOfRanges = 5;
        const int joyYRanges[4] = {180, 305, 430, 555};
        bool tickBtnX();
        bool tickBtnY();
    public:
        void tick();
        int getJoyX();
        int getJoyY();
        bool isBtnXPressed();
        bool isBtnYPressed();
        bool isBtnXReleased();
        bool isBtnYReleased();
};
#endif