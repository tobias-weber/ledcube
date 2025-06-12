// protects user from including library twice
#ifndef SnakeGame_h
#define SnakeGame_h

#include "../Animation.h"

class SnakeGame:public Animation {
    private:
        // Declare your class variables and your own methods here. 
        const byte fps = 30; // change fps here (36 is ideal)
        bool alwaysRainbow = false;
        bool previewMove = false;

        byte frameCounter = 1; 
        byte maxFrameCounter = fps / 1.5; // value not important, it is overridden at start;

        byte gameState = 3; // 0: play game, 1: game won, 2: game over, 3: init new game
        byte lengthNeededForWin;
        byte selectedSetting = 2; // 0: speed, 1: score, 2: settings closed
        float speedSettings[6] = {1, 1.25, 1.5, 2., 3., 4.5};
        byte selectedSpeed = 2;
        byte scoreSettings[11] = {10, 15, 20, 25, 30, 35, 40, 50, 75, 100, 125};
        byte selectedScore = 3;

        byte snake[125]; // array list containing the led indices of the bodyparts. (255 if unused).
        byte tail; // index of the last snake part;
        byte food = 255; // led index of the cube
        byte axis = 0; // current axis the snake is moving in.
        byte nextAxis;
        bool isPositiveDirection; // true if in positive axis direction, else false.
        bool isNextPositiveDirection;
        const byte steps[3] = {1, 5, 25}; // length of a single move, depending on the axis

        const byte snakeHeadAliveColor = COL_LIME;
        const byte snakeBodyAliveColor = COL_GREEN;
        const byte snakeHeadDeadColor = COL_PINK;
        const byte snakeBodyDeadColor = COL_RED;
        const byte previewColor = COL_DARK_BLUE;
        const byte foodColor = COL_ORANGE;
        const byte aliveCubeColor = COL_LIGHT_GREY;
        const byte deadCubeColor = COL_YELLOW;
        const byte wonCubeColor = COL_BLACK;
        byte colorAnimationCounter = 0; // needed for rainbow effect when the game is won
        unsigned long startTime = 0; // time for digit animation
        byte digits[3] = {0,0,0};
        int displayTime = 500; // time per digit in millis

        // Controller
        const int joyYPin = A1;
        const int joyXPin = A2;
        const int btnXPin = A3;
        const int btnYPin = A4;
        bool btnXPressed = false;
        bool btnYPressed = false;
        const byte joyXnumOfRanges = 5;
        const int joyXRanges[4] = {150, 300, 400, 550};
        const byte joyYnumOfRanges = 5;
        const int joyYRanges[4] = {180, 305, 430, 555};
        bool controlsReleased = true; // removes accidental double direction changes

        // Methods
        void initSnake();
        void moveSnake(byte nextPos);
        byte getNextPos();
        byte getPreviewPos();
        bool hasWallBetween(byte curr, byte next);
        bool doesCollide(byte nextPos);
        void setNewFood();
        bool isInSnake(byte pos);
        bool hasWon();
        void setDirection();
        void updateSettings();
        void renderGame();
        void drawSpeedSetting();
        void drawScoreSetting();
        void updateScoreDigits();
        int getCalibratedX();
        int getCalibratedY();
        bool isBtnXReleased();
        bool isBtnYReleased();
    public:
        void renderNextFrame();
        SnakeGame();
};
#endif
