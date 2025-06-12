#include "Controller.h"

// Must be called every single frame.
void Controller::tick() {
    tickBtnX();
    tickBtnY();
}

bool Controller::tickBtnX() {
  bool isPressed = digitalRead(btnXPin);
  if (isPressed) {
    btnXPressed = true;
  } else if (btnXPressed){
    btnXPressed = false;
    btnXReleased = true;
    return;
  }
  btnXReleased = false;
}

bool Controller::tickBtnY() {
  bool isPressed = digitalRead(btnYPin);
  if (isPressed) {
    btnYPressed = true;
  } else if (btnYPressed){
    btnYPressed = false;
    btnYReleased = true;
    return;
  }
  btnYReleased = false;
}

////////////// G E T T E R S //////////////

// at the current moment in time
int Controller::getJoyX() {
  int val = analogRead(joyXPin);
  byte calibratedVal = 0;
  for (byte i = 0; i < joyXnumOfRanges-1; i++) {
    if (val < joyXRanges[i]) break;
    calibratedVal++;
  }
  return calibratedVal;
}

int Controller::getJoyY() {
  int val = analogRead(joyYPin);
  byte calibratedVal = 0;
  for (byte i = 0; i < joyYnumOfRanges-1; i++) {
    if (val < joyYRanges[i]) break;
    calibratedVal++;
  }
  return calibratedVal;
}

// when tick was called
bool Controller::isBtnXPressed() {
  return btnXPressed;
}

bool Controller::isBtnYPressed() {
  return btnYPressed;
}

bool Controller::isBtnXReleased() {
  return btnXReleased;
}

bool Controller::isBtnYReleased() {
  return btnYReleased;
}