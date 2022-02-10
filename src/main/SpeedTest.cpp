//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "SpeedTest.h"

//.............................................
// DESCRIPTION:
// please describe your animation briefly
//
//
//.............................................

void SpeedTest::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }

    if (state == 0) {
      state++;
      startTime = millis();

    } else if (state == 1) {
      if (millis() - startTime < runTime) {
        _cube->setLed(index, 0);
        color++;
        if (color == 7) {
          color = 0;
          if (index == 124) {
            index = 0;
          } else {
            index++;
          }
        }
        _cube->setLed(index, colors[color]);
        counter++;
      } else {
        state++;
        int framerate = counter * 1000 / runTime;
        digits[3] = framerate % 10;
        framerate /= 10;
        digits[2] = framerate % 10;
        framerate /= 10;
        digits[1] = framerate % 10;
        framerate /= 10;
        digits[0] = framerate % 10;
        startTime = millis();
      }

    } else if (state == 2) {
      _cube->clearLeds();
      if (millis() - startTime < displayTime) {
        byte* plane = _charLib->getColoredCharacter(digits[0] + 26, 0b110000);
        _cube->setPlane(0, 4, plane);
        free(plane);
      } else if (millis() - startTime < 2 * displayTime) {
        byte* plane = _charLib->getColoredCharacter(digits[1] + 26, 0b001100);
        _cube->setPlane(0, 4, plane);
        free(plane);
      } else if (millis() - startTime < 3 * displayTime) {
        byte* plane = _charLib->getColoredCharacter(digits[2] + 26, 0b000011);
        _cube->setPlane(0, 4, plane);
        free(plane);
      } else if (millis() - startTime < 4 * displayTime) {
        byte* plane = _charLib->getColoredCharacter(digits[3] + 26, 0b111100);
        _cube->setPlane(0, 4, plane);
        free(plane);
      } else if (millis() - startTime > 6 * displayTime) {
        startTime = millis();
      }

    }
}

// C O N S T R U C T O R
SpeedTest::SpeedTest() {
  // Initialize class variables declared in the header files here.
  // Arrays cant be initialized with {} notation. Either initialize every element separately
  // or initialize it in the header file

  // set your Framerate here
  int fps = 2000; // everything above 1000 yields the same result
  _frameDelta = 1000 / fps;
}
