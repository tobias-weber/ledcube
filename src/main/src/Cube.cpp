// include arduino default data types and functions
#include "Arduino.h"

// include header for Cube
#include "Cube.h"
        
// contructor
Cube::Cube() {
}

// set all leds to 0
void Cube::clearLeds() {
  for(int i = 0; i < 125; i++) {
    _cubearray[i] = 0;
  }
}

// set all leds to the color specified
void Cube::setLeds(byte color) {
  for(int i = 0; i < 125; i++) {
    _cubearray[i] = color;
  }
}

// set color by specifying x,y,z
void Cube::setLed(byte x, byte y, byte z, byte color) {
  _cubearray[x + 5 * y + 25 * z] = color;
}

// set color with unique led id (0-124)
void Cube::setLed(byte id, byte color) {
  _cubearray[id] = color;
}

// set color by specifying layer and led number on that layer
void Cube::setLed(byte z, byte k, byte color) {
  _cubearray[25 * z + k] = color;
}

byte Cube::getLed(byte x, byte y, byte z) {
  return _cubearray[x + 5 * y + 25 * z];
}

// returns the byte of the led by unique led id (0-124)
byte Cube::getLed(byte id) {
  return _cubearray[id];
}

// Color is stored in the format: 00b2b1g2g1r2r1
byte Cube::getColor(byte r, byte g, byte b) {
  return r + g << 2 + b << 4;
}

// return 6 bit color from hue, saturation and value. Warning: Slow
byte Cube::getColorFromHSV(int hue, float saturation, float value) {
  float C = value * saturation;
  float H = (hue % 360) / 60.f;
  float X = C * (1 - abs(fmod(H, 2) - 1));
  float m = value - C;
  float r,g,b;

  if(H < 1){
      r = C,g = X,b = 0;
  }
  else if(H < 2){
      r = X,g = C,b = 0;
  }
  else if(H < 3){
      r = 0,g = C,b = X;
  }
  else if(H < 4){
      r = 0,g = X,b = C;
  }
  else if(H < 5){
      r = X,g = 0,b = C;
  }
  else{
      r = C,g = 0,b = X;
  }
  byte R = (r+m)*3;
  byte G = (g+m)*3;
  byte B = (b+m)*3;
  return (R << 4) + (G << 2) + B;
}
// return 6 bit color from an index (0..18) that corresponds to the hue.
byte Cube::getSaturatedColor(byte index) {
  return _saturatedColors[index % 18];
}


// ............................
// More advanced set methods
// ............................

// set color of single Led with blendMode
void Cube::setBlendedLed(byte id, byte color, byte blendMode) {
  if (color == 0 && blendMode == 1) return;

  switch (blendMode)
  {
  case 2:
    _cubearray[id] &= color;
    break;

  case 3:
    _cubearray[id] |= color;
    break;

  case 4:
    _cubearray[id] ^= color;
    break;

  case 5:
    if (_cubearray[id] == 0) _cubearray[id] = color;
    break;

  default:
    _cubearray[id] = color;
    break;
  }
}

// copy the contents of the given byte array(must have length 125) into the cubearray
void Cube::setCube(byte* src) {
  memcpy(_cubearray, src, 125);

}

// copy the contents of the cube array into the given byte array (must have length 125)
void Cube::copyCube(byte* dst) {
  memcpy(dst, _cubearray, 125);
}




// Set all leds in the k-th normal plane of axis to color.
// Axis can be 0 -> x     1 -> y     2 -> z (= set color of a layer)
void Cube::setPlane(byte axis, byte k, byte color) {

  switch(axis) {
    case 0: // x-Axis
      for (byte i = 0; i < 25; i++) {
        _cubearray[5 * i + k] = color;
      }
      break;

    case 1: // y-Axis
      for (byte z = 0; z < 5; z++) {
        for (byte x = 0; x < 5; x++) {
          _cubearray[25 * z + 5 * k + x] = color;
        }
      }
      break;

    case 2: // z-Axis
      for (byte i = 0; i < 25; i++) {
        _cubearray[25 * k + i] = color;
      }
      break;
  }
}
// Set all leds in the k-th normal plane of axis to values in colors.
void Cube::setPlane(byte axis, byte k, byte colors[25]) {
  byte i;
  switch(axis) {
    case 0: // x-Axis
      // i declared at top
      for (i = 0; i < 25; i++) {
        _cubearray[5 * i + k] = colors[i];
      }
      break;

    case 1: // y-Axis
      byte z;
      for (z = 0; z < 5; z++){
      byte x;
        for (x = 0; x < 5; x++) {
          _cubearray[25 * z + 5 * k + x] = colors[5 * z + x];
        }
      }
      break;

    case 2: // z-Axis
      // i declared at top
      for (i = 0; i < 25; i++) {
        _cubearray[25 * k + i] = colors[i];
      }
      break;
  }
}

// Set colors of a plane according to a blendMode
void Cube::setPlane(byte axis, byte k, byte colors[25], byte blendMode) {
  if (blendMode == 0) {
    setPlane(axis, k, colors);
  } else {
    switch(axis) {
      byte i;
      case 0: // x-Axis
        // i declared at top
        for (i = 0; i < 25; i++) {
          byte cubeIdx = 5 * i + k;

          if (blendMode == 1 && colors[i]) {
            _cubearray[cubeIdx] = colors[i];
          } else if (blendMode == 2) {
            _cubearray[cubeIdx] = _cubearray[cubeIdx] & colors[i];
          } else if (blendMode == 3) {
            _cubearray[cubeIdx] = _cubearray[cubeIdx] | colors[i];
          } else if (blendMode == 4) {
            _cubearray[cubeIdx] ^= colors[i];
          } else if (blendMode == 5 && _cubearray[cubeIdx] == 0) {
            _cubearray[cubeIdx] = colors[i];
          }
          
        }
        break;

      case 1: // y-Axis
      byte z;
        for (z = 0; z < 5; z++){
        byte x;
          for (x = 0; x < 5; x++) {
            byte cubeIdx = 25 * z + 5 * k + x;
            byte colorIdx = 5 * z + x;
            
            if (blendMode == 1 && colors[colorIdx]) {
              _cubearray[cubeIdx] = colors[colorIdx];
            } else if (blendMode == 2) {
              _cubearray[cubeIdx] = _cubearray[cubeIdx] & colors[colorIdx];
            } else if (blendMode == 3) {
              _cubearray[cubeIdx] = _cubearray[cubeIdx] | colors[colorIdx];
            }  else if (blendMode == 4) {
              _cubearray[cubeIdx] ^= colors[colorIdx];
            }  else if (blendMode == 5 && _cubearray[cubeIdx] == 0) {
              _cubearray[cubeIdx] = colors[i];
            }
          }
        }
        break;

      case 2: // z-Axis
        // i declared at top
        for (i = 0; i < 25; i++) {
          byte cubeIdx = 25 * k + i;

          if (blendMode == 1 && colors[i]) {
            _cubearray[cubeIdx] = colors[i];
          } else if (blendMode == 2) {
            _cubearray[cubeIdx] = _cubearray[cubeIdx] & colors[i];
          } else if (blendMode == 3) {
            _cubearray[cubeIdx] = _cubearray[cubeIdx] | colors[i];
          } else if (blendMode == 4) {
            _cubearray[cubeIdx] ^= colors[i];
          } else if (blendMode == 5 && _cubearray[cubeIdx] == 0) {
            _cubearray[cubeIdx] = colors[i];
          }
        }
        break;
    }
  }
}

void Cube::setPlane(byte axis, byte k, byte color, byte blendMode) {
  if (blendMode == 0 || (blendMode == 1 && color != 0)) {
    setPlane(axis, k, color);
  } else if (blendMode == 1) {
    return;
  } else {
    switch(axis) {
      byte i;
      case 0: // x-Axis
        // i declared at top
        for (i = 0; i < 25; i++) {
          byte cubeIdx = 5 * i + k;
          if (blendMode == 2) {
            _cubearray[cubeIdx] = _cubearray[cubeIdx] & color;
          } else if (blendMode == 3) {
            _cubearray[cubeIdx] = _cubearray[cubeIdx] | color;
          } else if (blendMode == 4) {
            _cubearray[cubeIdx] ^= color;
          } else if (blendMode == 5 && _cubearray[cubeIdx] == 0) {
            _cubearray[cubeIdx] = color;
          }
          
        }
        break;

      case 1: // y-Axis
      byte z;
        for (z = 0; z < 5; z++){
        byte x;
          for (x = 0; x < 5; x++) {
            byte cubeIdx = 25 * z + 5 * k + x;
            
            if (blendMode == 2) {
              _cubearray[cubeIdx] = _cubearray[cubeIdx] & color;
            } else if (blendMode == 3) {
              _cubearray[cubeIdx] = _cubearray[cubeIdx] | color;
            } else if (blendMode == 4) {
              _cubearray[cubeIdx] ^= color;
            } else if (blendMode == 5 && _cubearray[cubeIdx] == 0) {
              _cubearray[cubeIdx] = color;
            }
          }
        }
        break;

      case 2: // z-Axis
        // i declared at top
        for (i = 0; i < 25; i++) {
          byte cubeIdx = 25 * k + i;

          if (blendMode == 2) {
            _cubearray[cubeIdx] = _cubearray[cubeIdx] & color;
          } else if (blendMode == 3) {
            _cubearray[cubeIdx] = _cubearray[cubeIdx] | color;
          }  else if (blendMode == 4) {
            _cubearray[cubeIdx] ^= color;
          } else if (blendMode == 5 && _cubearray[cubeIdx] == 0) {
            _cubearray[cubeIdx] = color;
          }
        }
        break;
    }
  }
}

// Size 1..3
void Cube::setBlock(byte size, byte color, bool drawEdges, bool drawFaces, bool drawFill) {
  switch (size)
  {
  case 1:
    if (drawEdges) _cubearray[62] = color;
    break;

  case 2:
    if (drawEdges) {
      _cubearray[31] = color;
      _cubearray[32] = color;
      _cubearray[33] = color;
      _cubearray[36] = color;
      _cubearray[38] = color;
      _cubearray[41] = color;
      _cubearray[42] = color;
      _cubearray[43] = color;
      _cubearray[56] = color;
      _cubearray[58] = color;
      _cubearray[66] = color;
      _cubearray[68] = color;
      _cubearray[81] = color;
      _cubearray[82] = color;
      _cubearray[83] = color;
      _cubearray[86] = color;
      _cubearray[88] = color;
      _cubearray[91] = color;
      _cubearray[92] = color;
      _cubearray[93] = color;
    }
    if (drawFaces) {
      _cubearray[37] = color;
      _cubearray[57] = color;
      _cubearray[61] = color;
      _cubearray[63] = color;
      _cubearray[67] = color;
      _cubearray[87] = color;
    }
    if (drawFill) {
      _cubearray[62] = color;
    }
    break;
  
  case 3:
    if (drawEdges) {
      _cubearray[0] = color;
      _cubearray[1] = color;
      _cubearray[2] = color;
      _cubearray[3] = color;
      _cubearray[4] = color;
      _cubearray[5] = color;
      _cubearray[9] = color;
      _cubearray[10] = color;
      _cubearray[14] = color;
      _cubearray[15] = color;
      _cubearray[19] = color;
      _cubearray[20] = color;
      _cubearray[21] = color;
      _cubearray[22] = color;
      _cubearray[23] = color;
      _cubearray[24] = color;
      
      _cubearray[25] = color;
      _cubearray[29] = color;
      _cubearray[45] = color;
      _cubearray[49] = color;
      
      _cubearray[50] = color;
      _cubearray[54] = color;
      _cubearray[70] = color;
      _cubearray[74] = color;

      _cubearray[75] = color;
      _cubearray[79] = color;
      _cubearray[95] = color;
      _cubearray[99] = color;
      
      _cubearray[100] = color;
      _cubearray[101] = color;
      _cubearray[102] = color;
      _cubearray[103] = color;
      _cubearray[104] = color;
      _cubearray[105] = color;
      _cubearray[109] = color;
      _cubearray[110] = color;
      _cubearray[114] = color;
      _cubearray[115] = color;
      _cubearray[119] = color;
      _cubearray[120] = color;
      _cubearray[121] = color;
      _cubearray[122] = color;
      _cubearray[123] = color;
      _cubearray[124] = color;
    }

    if (drawFaces) {
      _cubearray[6] = color;
      _cubearray[7] = color;
      _cubearray[8] = color;
      _cubearray[11] = color;
      _cubearray[12] = color;
      _cubearray[13] = color;
      _cubearray[16] = color;
      _cubearray[17] = color;
      _cubearray[18] = color;
      
      _cubearray[26] = color;
      _cubearray[27] = color;
      _cubearray[28] = color;
      _cubearray[30] = color;
      _cubearray[34] = color;
      _cubearray[35] = color;
      _cubearray[39] = color;
      _cubearray[40] = color;
      _cubearray[44] = color;
      _cubearray[46] = color;
      _cubearray[47] = color;
      _cubearray[48] = color;

      _cubearray[51] = color;
      _cubearray[52] = color;
      _cubearray[53] = color;
      _cubearray[55] = color;
      _cubearray[59] = color;
      _cubearray[60] = color;
      _cubearray[64] = color;
      _cubearray[65] = color;
      _cubearray[69] = color;
      _cubearray[71] = color;
      _cubearray[72] = color;
      _cubearray[73] = color;
      
      _cubearray[76] = color;
      _cubearray[77] = color;
      _cubearray[78] = color;
      _cubearray[80] = color;
      _cubearray[84] = color;
      _cubearray[85] = color;
      _cubearray[89] = color;
      _cubearray[90] = color;
      _cubearray[94] = color;
      _cubearray[96] = color;
      _cubearray[97] = color;
      _cubearray[98] = color;

      _cubearray[106] = color;
      _cubearray[107] = color;
      _cubearray[108] = color;
      _cubearray[111] = color;
      _cubearray[112] = color;
      _cubearray[113] = color;
      _cubearray[116] = color;
      _cubearray[117] = color;
      _cubearray[118] = color;
    }

    if (drawFill) setBlock(2, color, true, true, true);
  
  }
}

// Size in 1..6. Watch out: 6 is too large to fit in 5x5x5 cube
void Cube::setSphere(byte size, byte color, bool drawSurface, bool drawFill) {
    switch (size)
    {
    case 1:
      if (drawSurface) _cubearray[62] = color;
      break;

    case 2:
      if (drawSurface) {
        _cubearray[37] = color;
        _cubearray[57] = color;
        _cubearray[61] = color;
        _cubearray[63] = color;
        _cubearray[67] = color;
        _cubearray[87] = color;
      }
      if (drawFill) _cubearray[62] = color;
      break;

    case 3:
      if (drawSurface) {
        _cubearray[32] = color;
        _cubearray[36] = color;
        _cubearray[37] = color;
        _cubearray[38] = color;
        _cubearray[42] = color;
        _cubearray[56] = color;
        _cubearray[57] = color;
        _cubearray[58] = color;
        _cubearray[61] = color;
        _cubearray[63] = color;
        _cubearray[66] = color;
        _cubearray[67] = color;
        _cubearray[68] = color;
        _cubearray[82] = color;
        _cubearray[86] = color;
        _cubearray[87] = color;
        _cubearray[88] = color;
        _cubearray[92] = color;
      }
      if (drawFill) {
        _cubearray[62] = color;
      }
      break;

    case 4:
      if (drawSurface) {
        _cubearray[12] = color;
        _cubearray[31] = color;
        _cubearray[32] = color;
        _cubearray[33] = color;
        _cubearray[36] = color;
        _cubearray[38] = color;
        _cubearray[41] = color;
        _cubearray[42] = color;
        _cubearray[43] = color;
        _cubearray[52] = color;
        _cubearray[56] = color;
        _cubearray[58] = color;
        _cubearray[60] = color;
        _cubearray[64] = color;
        _cubearray[66] = color;
        _cubearray[68] = color;
        _cubearray[72] = color;
        _cubearray[81] = color;
        _cubearray[82] = color;
        _cubearray[83] = color;
        _cubearray[86] = color;
        _cubearray[88] = color;
        _cubearray[91] = color;
        _cubearray[92] = color;
        _cubearray[93] = color;
        _cubearray[112] = color;
      }
      if (drawFill) {
        setSphere(2, color, true, true);
      }
      break;

    case 5:
      if (drawSurface) {
        _cubearray[7] = color;
        _cubearray[11] = color;
        _cubearray[12] = color;
        _cubearray[13] = color;
        _cubearray[17] = color;
        _cubearray[27] = color;
        _cubearray[31] = color;
        _cubearray[33] = color;
        _cubearray[35] = color;
        _cubearray[39] = color;
        _cubearray[41] = color;
        _cubearray[43] = color;
        _cubearray[47] = color;
        _cubearray[51] = color;
        _cubearray[52] = color;
        _cubearray[53] = color;
        _cubearray[55] = color;
        _cubearray[59] = color;
        _cubearray[60] = color;
        _cubearray[64] = color;
        _cubearray[65] = color;
        _cubearray[69] = color;
        _cubearray[71] = color;
        _cubearray[72] = color;
        _cubearray[73] = color;
        _cubearray[77] = color;
        _cubearray[81] = color;
        _cubearray[83] = color;
        _cubearray[85] = color;
        _cubearray[89] = color;
        _cubearray[91] = color;
        _cubearray[93] = color;
        _cubearray[97] = color;
        _cubearray[107] = color;
        _cubearray[111] = color;
        _cubearray[112] = color;
        _cubearray[113] = color;
        _cubearray[117] = color;

      }
      if (drawFill) {
        setSphere(3, color, true, true);
      }
      break;

    case 6: // To large to fit in 5x5x5 cube
      if (drawSurface) {
        _cubearray[2] = color;
        _cubearray[6] = color;
        _cubearray[8] = color;
        _cubearray[10] = color;
        _cubearray[14] = color;
        _cubearray[16] = color;
        _cubearray[18] = color;
        _cubearray[22] = color;
        _cubearray[26] = color;
        _cubearray[27] = color;
        _cubearray[28] = color;
        _cubearray[30] = color;
        _cubearray[34] = color;
        _cubearray[35] = color;
        _cubearray[39] = color;
        _cubearray[40] = color;
        _cubearray[44] = color;
        _cubearray[46] = color;
        _cubearray[47] = color;
        _cubearray[48] = color;
        _cubearray[50] = color;
        _cubearray[51] = color;
        _cubearray[52] = color;
        _cubearray[53] = color;
        _cubearray[54] = color;
        _cubearray[55] = color;
        _cubearray[59] = color;
        _cubearray[60] = color;
        _cubearray[64] = color;
        _cubearray[65] = color;
        _cubearray[69] = color;
        _cubearray[70] = color;
        _cubearray[71] = color;
        _cubearray[72] = color;
        _cubearray[73] = color;
        _cubearray[74] = color;
        _cubearray[76] = color;
        _cubearray[77] = color;
        _cubearray[78] = color;
        _cubearray[80] = color;
        _cubearray[84] = color;
        _cubearray[85] = color;
        _cubearray[89] = color;
        _cubearray[90] = color;
        _cubearray[94] = color;
        _cubearray[96] = color;
        _cubearray[97] = color;
        _cubearray[98] = color;
        _cubearray[102] = color;
        _cubearray[106] = color;
        _cubearray[108] = color;
        _cubearray[110] = color;
        _cubearray[114] = color;
        _cubearray[116] = color;
        _cubearray[118] = color;
        _cubearray[122] = color;

      }
      if (drawFill) {
        _cubearray[7] = color;
        _cubearray[11] = color;
        _cubearray[12] = color;
        _cubearray[13] = color;
        _cubearray[17] = color;
        _cubearray[31] = color;
        _cubearray[33] = color;
        _cubearray[41] = color;
        _cubearray[43] = color;
        _cubearray[81] = color;
        _cubearray[83] = color;
        _cubearray[91] = color;
        _cubearray[93] = color;
        _cubearray[107] = color;
        _cubearray[111] = color;
        _cubearray[112] = color;
        _cubearray[113] = color;
        _cubearray[117] = color;
        setSphere(3, color, true, true);


      }
      break;
      
    }
  }

// Draws a diagonal plane.
// axis: the axis in which the plane lies
// k: the k-th diagonal plane will be drawn
// blendMode:  1 = "Mask" doesn't really make sense here
// isFlipped: If true, plane is turned around axis by 90 degrees
void Cube::setDiagonalPlane(byte axis, byte k, byte color, byte blendMode, bool isFlipped) {
  if (k > 8 || axis > 2) return;

  byte i;
  byte nLines = 0; // Number of lines that this plane consists of
  byte offsets[] = {30, 20, 24, 26, 6, 4}; //difference of the startpoints of two lines in a single plane
  byte offset; // the difference used for this specific plane
  byte start; // the startpoint of the first line of this specific plane

  // set offset
  if (isFlipped) {
    offset = offsets[2 * axis + 1];
  } else {
    offset = offsets[2 * axis];
  }

  // set nLines and start
  switch (axis)
  {
  case 0:
    if (k < 5) {
      nLines = k + 1;
      start = (isFlipped) ? k * 5 : 20 - 5 * k;
    } else {
      nLines = 9 - k;
      start = (isFlipped) ? 20 + 25 * (k - 4) : 25 * (k - 4);
    }
    break;

  case 1:
    if (k < 5) {
      nLines = k + 1;
      start = (isFlipped) ? 4 - k : k;
    } else {
      nLines = 9 - k;
      start = (isFlipped) ? 25 * (k - 4): 4 + 25 * (k - 4);
    }
    break;

  case 2:
    if (k < 5) {
      nLines = k + 1;
      start = (isFlipped) ? k : 20 - 5 * k;
    } else {
      nLines = 9 - k;
      start = (isFlipped) ? 4 + 5 * (k - 4) : k - 4;
    }
    break;
  }

  // Draw plane, consisting of nLines straight lines.
  for (i = 0; i < nLines; i++) {
    setStraightLine(axis, start + offset * i, 5, color, blendMode);
  }
}

// Draws a single straight line. The line starts at start, goes in the (+) direction of axis and
// extends for length leds
void Cube::setStraightLine(byte axis, byte start, byte length, byte color, byte blendMode) {
  if (blendMode == 1 && color == 0 || length > 5) {
    return;
  }

  int i;
  byte offset = 1;
  if (axis == 1) {
    offset = 5;
  } else if (axis == 2) {
    offset = 25;
  }

  switch (blendMode)
  {
  case 2:
    for (i = 0; i < length; i++) _cubearray[start + i * offset] &= color;
    break;

  case 3:
    for (i = 0; i < length; i++) _cubearray[start + i * offset] |= color;
    break;

  case 4:
    for (i = 0; i < length; i++) _cubearray[start + i * offset] ^= color;
    break;

  case 5:
    for (i = 0; i < length; i++) {
      if (_cubearray[start + i * offset] == 0) _cubearray[start + i * offset] = color;
    }
    break;

  default:
    for (i = 0; i < length; i++) _cubearray[start + i * offset] = color;
    break;
  }
}

