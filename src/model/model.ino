#include "Animation.h"
#include "Cube.h"
#include "Writer.h"

// cube object representing the Cube
Cube cube;
// writer used to write cube to hardware
const byte SERIAL_DATA = 13;
const byte SERIAL_SHIFT = 14;
const byte MOS_LAYER_0 = 1;
Writer writer(SERIAL_DATA, SERIAL_SHIFT, MOS_LAYER_0);
// animation to display
Animation animation;

void setup() {
  animation.assignCube(&cube);
  writer.assignCube(&cube);
  animation.assignWriter(&writer);
}

void loop() {
  animation.renderNextFrame();
  animation.showNextFrame();
}
