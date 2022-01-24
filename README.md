# ledcube
Arduino Code for controlling a 5 x 5 x 5 RGB LED Cube with 74hc595 ICs

## How to write and execute your own Animations
1. Copy `TemplateAnimation.cpp` and `TemplateAnimation.h` into the `main` folder.
2. Rename the two files to the name your animation should have.
3. By using search and replace, replace all occurences of `TemplateAnimation` with the name of your animation.
4. Write your own animation code. If you declare new methods, write their signatures into the header file.
5. Go to `main.ino`, add a statement to include your animation header file.
6. Change the type of the animation object to your animation.

**Good to know:**
- Variables defined outside of a method are global and thus **MUST HAVE A UNIQUE NAME!** 
(for example start all variables with a unique prefix for your animation).
- Look at Cube.h to get an idea of what is already implemented to change leds.
- Framerate can be set in the initialize() method of your animation.
- Default Framerate for all animations that don't specify a framerate can be changed in Animation.h

## How to add new methods to change the led colors to the cube
1. Write your method in `Cube.cpp`.
2. Add your method signature to `Cube.h`.
