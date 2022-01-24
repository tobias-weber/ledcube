#include "DiagonalPlaneAnimation.h"
#include "Cube.h"
#include "Writer.h"
#include "CharacterLibrary.h"

// init character library
CharacterLibrary characterLibrary;
// cube object representing the Cube
Cube cube;
// writer used to write cube to hardware
const byte SERIAL_DATA = 5;
const byte SERIAL_SHIFT = 6;
const byte SERIAL_LATCH = 7;
const byte MOS_LAYER_0 = 0;
Writer writer(SERIAL_DATA, SERIAL_SHIFT, SERIAL_LATCH, MOS_LAYER_0);
// animation to display
DiagonalPlaneAnimation animation;           // <------------- CHOOSE ANIMATION HERE --------------

void setup() {
  animation.assignCube(&cube);
  animation.assignCharacterLibrary(&characterLibrary);
  writer.assignCube(&cube);
  animation.assignWriter(&writer);

  pinMode(SERIAL_DATA, OUTPUT);
  pinMode(SERIAL_SHIFT, OUTPUT);
  pinMode(SERIAL_LATCH, OUTPUT);

  pinMode(MOS_LAYER_0, OUTPUT);
  pinMode(MOS_LAYER_0 + 1, OUTPUT);
  pinMode(MOS_LAYER_0 + 2, OUTPUT);
  pinMode(MOS_LAYER_0 + 3, OUTPUT);
  pinMode(MOS_LAYER_0 + 4, OUTPUT);

  animation.initialize();
}

void loop() {
  animation.renderNextFrame();
  animation.showNextFrame();
}
