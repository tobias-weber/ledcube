#include "Animation.h"
#include "Cube.h"
#include "Writer.h"

// cube object representing the Cube
Cube cube;
// writer used to write cube to hardware
const byte SERIAL_DATA = 0;
const byte SERIAL_SHIFT = 1;
const byte SERIAL_LATCH = 2;
const byte MOS_LAYER_0 = 3;
Writer writer(SERIAL_DATA, SERIAL_SHIFT, SERIAL_LATCH, MOS_LAYER_0);
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
