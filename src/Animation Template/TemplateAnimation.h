// protects user from including library twice
#ifndef TemplateAnimation_h
#define TemplateAnimation_h

#include "Animation.h"

class TemplateAnimation:public Animation {
    private:
        // Declare your class variables and your own methods here. 
    public:
        void renderNextFrame();
        TemplateAnimation();
};
#endif
