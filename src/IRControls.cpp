#include <Arduino.h>
#include <IRremote.h>

#include "IRControls.h"

bool playPausePressed = false; // 0x43
bool minusPressed = false; // 0x7
bool plusPressed = false; // 0x15
bool nextPressed = false; // 0x40
bool previousPressed = false; // 0x44

IRControls::IRControls() {
  IrReceiver.begin(IR_RECEIVE_PIN);
}

void IRControls::loop() {
  // Reset
  playPausePressed = false;
  minusPressed = false;
  plusPressed = false;
  nextPressed = false;
  previousPressed = false;

  static long currentMillis;
  if (millis() - currentMillis >= receiveInterval) {
    if (IrReceiver.decode()) {
      if (IrReceiver.decodedIRData.command == 0x43) {
        playPausePressed = true;
      } else if (IrReceiver.decodedIRData.command == 0x7) {
        minusPressed = true;
      } else if (IrReceiver.decodedIRData.command == 0x15) {
        plusPressed = true;
      } else if (IrReceiver.decodedIRData.command == 0x40) {
        nextPressed = true;
      } else if (IrReceiver.decodedIRData.command == 0x44) {
        previousPressed = true;
      }
      IrReceiver.resume();  
    }

    currentMillis = millis();
  } 
}

bool IRControls::isPlayPausePressed() {
  return playPausePressed;
}

bool IRControls::isMinusPressed() {
  return minusPressed;
}

bool IRControls::isPlusPressed() {
  return plusPressed;
}

bool IRControls::isNextPressed() {
  return nextPressed;
}

bool IRControls::isPreviousPressed() {
  return previousPressed;
}
