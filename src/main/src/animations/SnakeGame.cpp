//include arduino default data types and functions
#include "Arduino.h"

//include class header
#include "SnakeGame.h"

//.............................................
// DESCRIPTION:
// please describe your animation briefly
//
//
//.............................................

void SnakeGame::renderNextFrame() {
    // check if calculation of next frame is already necessary. Else skip to refreshing current frame for less flicker
    if (frameIsToEarly()) {
      return;
    }
    alwaysRainbow = false; // weird bug sets this to true...
    if (gameState == 0) {
      setDirection();
      if (frameCounter == 0) {
        // time to move
        if (controlsReleased) {
          axis = nextAxis;
          isPositiveDirection = isNextPositiveDirection;
          controlsReleased = false;
        }
        byte nextPos = getNextPos();
        if (!doesCollide(nextPos)) {
          moveSnake(nextPos);
          if (food == 255) {
            if (!hasWon()) {
              setNewFood();
            } else {
              gameState = 1;
            }
          }
        } else {
          gameState = 2;
        }
      }
      
    } else if ((gameState == 1 || gameState == 2) && isBtnXReleased()) {
      gameState = 3;
      selectedSetting = 2;
      initSnake();
      food = 255;
    } else if (gameState == 3) {
      updateSettings();
      if (isBtnXReleased()) {
        maxFrameCounter = fps / speedSettings[selectedSpeed];
        lengthNeededForWin = scoreSettings[selectedScore];
        gameState = 0;
        randomSeed(micros());
        setNewFood();
      }
    }

    renderGame();

    frameCounter++;
    if (frameCounter >= maxFrameCounter) frameCounter = 0;
}

// C O N S T R U C T O R
SnakeGame::SnakeGame() {
  // Initialize class variables declared in the header files here.
  // Arrays cant be initialized with {} notation. Either initialize every element separately
  // or initialize it in the header file

  // set your Framerate here
  _frameDelta = 1000 / fps;
  initSnake();
  updateScoreDigits();
}

void SnakeGame::initSnake() {
  for (byte i = 1; i < 125; i++) {
    snake[i] = 255;
  }
  snake[0] = 61; // startpos
  snake[1] = 60;
  tail = 1;

  axis = 0;
  isPositiveDirection = true;
  nextAxis = 0;
  isNextPositiveDirection = true;
}

void SnakeGame::moveSnake(byte nextPos) {
  if (nextPos == food) {
    food = 255;
    tail++;
  }
  for (byte i = tail; i > 0; i--) {
    snake[i] = snake[i-1];
  }
  snake[0] = nextPos;
}

byte SnakeGame::getNextPos() {
  byte nextPos = snake[0];
  if (isPositiveDirection) {
    nextPos += steps[axis];
  } else {
    nextPos -= steps[axis];
  }
  
  // check for wall
  if (hasWallBetween(snake[0], nextPos)) return 255;
  return nextPos;
}

byte SnakeGame::getPreviewPos() {
  byte nextPos = snake[0];
  if (isNextPositiveDirection) {
    nextPos += steps[nextAxis];
  } else {
    nextPos -= steps[nextAxis];
  }
  if (nextPos > 124) return snake[0];
  return nextPos;
}

bool SnakeGame::hasWallBetween(byte curr, byte next) {
  if (axis == 0) {
    return (curr / 5) != (next / 5);
  } else if (axis == 1) {
    return (curr / 25) != (next / 25);
  } else {
    return next > 124;
  }
}

bool SnakeGame::doesCollide(byte nextPos) {
  if (nextPos > 124) return true;
  for (byte i = 3; i < tail; i++) {
    if (snake[i] == nextPos) return true;
  }
  return false;
}

void SnakeGame::setNewFood() {
  byte nextFood = random(125);
  while (isInSnake(nextFood)) {
    nextFood = random(125);
  }
  food = nextFood;
}

bool SnakeGame::isInSnake(byte pos) {
  for (byte i = 0; i <= tail; i++) {
    if (snake[i] == pos) return true;
  }
  return false;
}

bool SnakeGame::hasWon() {
  return tail >= lengthNeededForWin-1;
}


// R E N D E R I N G
void SnakeGame::renderGame() {
  _cube->clearLeds();

  byte bodyColor, headColor;
  if (gameState == 0) { // normal
    _cube->setBlock(3, aliveCubeColor, true, false, false);
    if (previewMove) _cube->setLed(getPreviewPos(), previewColor);
    bodyColor = snakeBodyAliveColor;
    headColor = snakeHeadAliveColor;
    if (alwaysRainbow) {
      for (byte i = 0; i <= tail; i++) {
        _cube->setLed(snake[tail-i], _cube->getSaturatedColor(colorAnimationCounter+i)); // Draw Snake Body
      }
      colorAnimationCounter++;
      if (colorAnimationCounter == 18) colorAnimationCounter = 0;
    } else {
      // Default rendering
      for (byte i = 1; i <= tail; i++) {
        _cube->setLed(snake[i], bodyColor); // Draw Snake Body
      }
      _cube->setLed(snake[0], headColor);
    }


  } else if (gameState == 1) { // game won
    _cube->setBlock(3, wonCubeColor, true, false, false);
    
    for (byte i = 0; i <= tail; i++) {
      _cube->setLed(snake[tail-i], _cube->getSaturatedColor(colorAnimationCounter+i)); // Draw Snake Body
    }
    colorAnimationCounter++;
    if (colorAnimationCounter == 18) colorAnimationCounter = 0;

  } else if (gameState == 2) { // game lost
    _cube->setBlock(3, deadCubeColor, true, false, false);
    bodyColor = snakeBodyDeadColor;
    headColor = snakeHeadDeadColor;

    for (byte i = 1; i <= tail; i++) {
      _cube->setLed(snake[i], bodyColor); // Draw Snake Body
    }
    _cube->setLed(snake[0], headColor);

  } else if (gameState == 3) {
    _cube->setBlock(3, aliveCubeColor, true, false, false);
    bodyColor = snakeBodyAliveColor;
    headColor = snakeHeadAliveColor;
    if (alwaysRainbow) {
      for (byte i = 0; i <= tail; i++) {
        _cube->setLed(snake[tail-i], _cube->getSaturatedColor(colorAnimationCounter+i)); // Draw Snake Body
      }
      colorAnimationCounter++;
      if (colorAnimationCounter == 18) colorAnimationCounter = 0;
    } else {
      // Default rendering
      for (byte i = 1; i <= tail; i++) {
        _cube->setLed(snake[i], bodyColor); // Draw Snake Body
      }
      _cube->setLed(snake[0], headColor);

      if (selectedSetting == 0) {
        drawSpeedSetting();
      } else if (selectedSetting == 1) {
        drawScoreSetting();
      }
    }
  }

  _cube->setLed(food, foodColor); // Draw Food
}

void SnakeGame::drawSpeedSetting() {
    byte* plane = _charLib->getColoredCharacter(selectedSpeed + 27, 0b110000);
    _cube->setPlane(0, 4, plane, 1);
    free(plane);
}

void SnakeGame::drawScoreSetting() {
  if (millis() - startTime < displayTime) {
    if (digits[0] != 0) {
      byte* plane = _charLib->getColoredCharacter(digits[0] + 26, COL_PURPLE);
      _cube->setPlane(0, 4, plane, 1);
      free(plane);
    }
  } else if (millis() - startTime < 2 * displayTime) {
    byte* plane = _charLib->getColoredCharacter(digits[1] + 26, COL_MAGENTA);
    _cube->setPlane(0, 4, plane, 1);
    free(plane);
  } else if (millis() - startTime < 3 * displayTime) {
    byte* plane = _charLib->getColoredCharacter(digits[2] + 26, COL_PINK);
    _cube->setPlane(0, 4, plane, 1);
    free(plane);
  } else if (millis() - startTime > 5 * displayTime) {
    startTime = millis();
  }

}

// U S E R - I N T E R A C T I O N
void SnakeGame::setDirection() {
  byte jx = getCalibratedX();
  byte jy = getCalibratedY();
  bool x = isBtnXReleased();
  bool y = isBtnYReleased();

  if (!controlsReleased) {
    if (jx > 0 && jy > 0 && jx < 4 && jy < 4 && x == false && y == false) controlsReleased = true;
    return;
  }

  // Allows to play just with the joystick, or additionally with buttons
  if (jx == 0) {
    if (axis != 1) {
      nextAxis = 1;
      isNextPositiveDirection = false;
    } else {
      nextAxis = 2; 
      isNextPositiveDirection = isPositiveDirection;
    }
  } else if (jx == 4) {
    if (axis != 1) {
      nextAxis = 1;
      isNextPositiveDirection = true;
    } else {
      nextAxis = 2;
      isNextPositiveDirection = !isPositiveDirection;  
    }
  } else if (jy == 0) {
    if (axis != 0) {
      nextAxis = 0;
      isNextPositiveDirection = true;
    } else {
      nextAxis = 2;
      isNextPositiveDirection = !isPositiveDirection;
    }
  } else if (jy == 4) {
    if (axis != 0) {
      nextAxis = 0;
      isNextPositiveDirection = false;
    } else {
      nextAxis = 2;
      isNextPositiveDirection = isPositiveDirection;
    }
  } else if (x && axis != 2) {
    nextAxis = 2;
    isNextPositiveDirection = false;
  } else if (y && axis != 2) {
    nextAxis = 2;
    isNextPositiveDirection = true;   
  } else {
    controlsReleased = true;
  }

}

void SnakeGame::updateSettings() {
  if (isBtnYReleased()) {
    selectedSetting++;
    if (selectedSetting > 2) selectedSetting = 0;
  }
  byte jy = getCalibratedY();
  if (!controlsReleased) {
    if (jy > 0 && jy < 4) controlsReleased = true;
    return;
  } else {
    if (jy == 0) {
      if (selectedSetting == 0) {
        if (selectedSpeed != 0) selectedSpeed--;
      } else if (selectedSetting == 1) {
        if (selectedScore != 0){
          selectedScore--;
          updateScoreDigits();
        }
      }
      controlsReleased = false;
    } else if (jy == 4) {
      if (selectedSetting == 0) {
        if (selectedSpeed != 5) selectedSpeed++;
      } else if (selectedSetting == 1) {
        if (selectedScore != 10) {
          selectedScore++;
          updateScoreDigits();
          }
      }
      controlsReleased = false;
    }
  }
}

void SnakeGame::updateScoreDigits() {
  byte scoreVal = scoreSettings[selectedScore];
  digits[2] = scoreVal % 10;
  scoreVal /= 10;
  digits[1] = scoreVal % 10;
  scoreVal /= 10;
  digits[0] = scoreVal;
  startTime = millis();
}

int SnakeGame::getCalibratedX() {
  int val = analogRead(joyXPin);
  byte calibratedVal = 0;
  for (byte i = 0; i < joyXnumOfRanges-1; i++) {
    if (val < joyXRanges[i]) break;
    calibratedVal++;
  }
  return calibratedVal;
}

int SnakeGame::getCalibratedY() {
  int val = analogRead(joyYPin);
  byte calibratedVal = 0;
  for (byte i = 0; i < joyYnumOfRanges-1; i++) {
    if (val < joyYRanges[i]) break;
    calibratedVal++;
  }
  return calibratedVal;
}

bool SnakeGame::isBtnXReleased() {
  bool isPressed = digitalRead(btnXPin);
  if (isPressed) {
    btnXPressed = true;
  } else if (btnXPressed){
    btnXPressed = false;
    return true;
  }
  return false;
}

bool SnakeGame::isBtnYReleased() {
  bool isPressed = digitalRead(btnYPin);
  if (isPressed) {
    btnYPressed = true;
  } else if (btnYPressed){
    btnYPressed = false;
    return true;
  }
  return false;
}

