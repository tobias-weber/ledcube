//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "Tornado.h"

//.............................................
// DESCRIPTION:
// A colorful tornado thats turning around the center axis of the cube.
// Speed can be changed on the fly by holding Y and moving the joystick y axis.
//
//.............................................

void Tornado::renderNextFrame() {
    //unsigned long startTime = millis();
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }
    controller.tick();
    if (controller.isBtnYPressed()) speedSelection = controller.getJoyY();
    if (controller.isBtnXReleased()) reversed = !reversed;

    if (reversed) {
      time -= speed[speedSelection];
      if (time < 0) time += 16;
    } else {
      time += speed[speedSelection];
      if (time > 16) time -= 16;
    }
    byte index;
    for (byte i = 0; i < 5; i++) {
      for (byte pos = 0; pos < 16; pos++) {
        
        for (index = round(1.125*(pos+i+time)); index >= 18; index -= 18);
        byte col = allColors[index];
        //byte col = allColors[round(1.125*(pos+i+time))%18]; // mod is less efficient than for loop...
        _cube->setLed(circle[pos] + 25 * i, col);
      }

      for (byte pos = 0; pos < 8; pos++) {
        for (index = round(1.125*(2*pos+i+time)); index >= 18; index -= 18);
        byte col = allColors[index];
        //byte col = allColors[round(1.125*(2*pos+i+time))%18]; // mod is less efficient than for loop...
        _cube->setLed(square[pos] + 25 * i, col);
      }     
    }
    _cube->setStraightLine(2,12,5,COL_WHITE,0);
    
}

// C O N S T R U C T O R
Tornado::Tornado() {
  // Initialize class variables declared in the header files here.
  // Arrays cant be initialized with {} notation. Either initialize every element separately
  // or initialize it in the header file

  // set your Framerate here
  int fps = 50; 
  _frameDelta = 1000 / fps;
}
