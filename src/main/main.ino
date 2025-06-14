#include "src/animations/CombinedAnimation.h"
#include "src/Cube.h"
#include "src/Writer.h"
#include "src/CharacterLibrary.h"

// init character library
CharacterLibrary characterLibrary;
// cube object representing the Cube
Cube cube;
// writer used to write cube to hardware
// constants only used for pin setup. To change output pins also modify writer.cpp!
const byte SERIAL_DATA = 5;
const byte SERIAL_SHIFT = 6;
const byte SERIAL_LATCH = 7;
const byte MOS_LAYER_0 = 0;
Writer writer;
// animation to display
CombinedAnimation animation;           // <------------- CHOOSE ANIMATION HERE --------------

void setup() {
  //Serial.begin(9600);
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

}

void loop() {
  animation.renderNextFrame();
  animation.showNextFrame();
}
