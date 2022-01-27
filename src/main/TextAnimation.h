// protects user from including library twice
#ifndef TextAnimation_h
#define TextAnimation_h

#include "Animation.h"

class TextAnimation:public Animation {
    private:
        byte letter = 0;
        byte axis = 0;
        byte textLayer = 0;
        byte color = 0;
        byte letters[17] = {2, 0, 19, 2, 7, 28, 27, 67, 15, 17, 14, 9, 4, 10, 19, 67, 64};
        byte colors[6] = {0b000001, 0b010001, 0b010000, 0b010100, 0b000100, 0b000101};
    public:
        void renderNextFrame();
        TextAnimation();
        // Declare your own methods here
};
#endif
