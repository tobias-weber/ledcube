//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "FadingCube.h"

//.............................................
// DESCRIPTION:
// please describe your animation briefly
//
//
//.............................................

void FadingCube::renderNextFrame() {
  // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
  if (frameIsToEarly()) {
    return;
  }    
  _cube->clearLeds();

  byte rand = random(3) * 2;
  byte channel = color & (0b11 << rand) >> rand;
  if (random(2)) {
      // 50 % chance
      if (channel != 0b11) channel++;
  } else {
      if (channel != 0) channel--;
  }

  color = color & (0b00111111 xor (0b11 << rand)) | (channel << rand);
  // _cube->setBlock(3,color, true, true, true);

  for (int i = 8; i > 0; i--)
  {
    colors[i] = colors[i-1];
  }
  colors[0] = color;
  for (int i = 0; i < 9; i++)
  {
    _cube->setDiagonalPlane(0,i,colors[i],0,false);
    _cube->setDiagonalPlane(1,i,colors[i],0,false);

  }
  

}

// C O N S T R U C T O R
FadingCube::FadingCube() {
  // Initialize class variables declared in the header files here.
  // Arrays cant be initialized with {} notation. Either initialize every element separately
  // or initialize it in the header file

  // set your Framerate here
  int fps = 10; 
  _frameDelta = 1000 / fps;
}
