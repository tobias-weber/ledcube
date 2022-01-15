byte cube[125];

// set all leds to 0
void clearLeds() {
  for(int i = 0; i < 125; i++) {
    cube[i] = 0;
  }
}


// set color by specifying x,y,z
void setLed(byte x, byte y, byte z, byte color) {
  cube[x + 5 * y + 25 * z] = color;
}

// set color with unique led id (0-124)
void setLed(byte id, byte color) {
  cube[id] = color;
}

// set color by specifying layer and led number on that layer
void setLed(byte z, byte k, byte color) {
  cube[25 * z + k] = color;
}

byte getLed(byte x, byte y, byte z, byte color) {
  return cube[x + 5 * y + 25 * z];
}

// Color is stored in the format: 00b2b1g2g1r2r1
byte getColor(byte r, byte g, byte b) {
  return r + g << 2 + b << 4;
}
