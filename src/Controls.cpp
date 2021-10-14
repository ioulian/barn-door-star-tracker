#include <Arduino.h>
#include <ezButton.h>
#include <Rotary.h>

#include "Controls.h"

short rotation = 0;
bool buttonPressed = false;

Rotary rotary = Rotary(CLK, DT);
ezButton button(SW);

Controls::Controls() {
  button.setDebounceTime(50);
  rotary.begin(true);
}

void Controls::loop() {
  // Reset
  rotation = 0;
  buttonPressed = false;
  
  loopRotation();
  loopButton();
}

short Controls::getRotation() {
  return rotation;
}

bool Controls::getButtonPressed() {
  return buttonPressed;
}

void Controls::loopRotation() {
  unsigned char result = rotary.process();
  if (result) {
    rotation = result == DIR_CW ? -1 : 1;
  }
}

void Controls::loopButton() {
  button.loop();

  if (button.isPressed()) {
    buttonPressed = true;
  }
}
