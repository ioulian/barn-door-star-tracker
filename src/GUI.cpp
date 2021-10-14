#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#include "Globals.h"
#include "GUI.h"

SSD1306AsciiWire oled;
uint32_t tickTime = 0;

float motorSpeedAdjust = 0.0;
bool isAdjustingSpeed = false;

short motorDirection = motor.getDirection();
bool isAdjustingMotorDirection = false;

/**
 * Pages:
 * 0 = Overview
 * 1 = Motor speed
 * 2 = Motor direction
 * 3 = Motor control
 * 4 = Battery
 */
unsigned short currentPage = 0;
const unsigned short totalPages = 5;
bool isSplashPage = true;

String padString(String str, short pad){
  for(int i = 0; i < (16 - str.length()); i++) {
    str += ' ';  
  }

  return str;
}

GUI::GUI() {
  Wire.begin();
  Wire.setClock(400000L);
  
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(Adafruit5x7);
}

void GUI::loop() {
  loopControls();

  static long currentMillis;
  if (millis() - currentMillis >= batteryDisplayInterval) {
    oled.clearField(
      oled.displayWidth() - oled.strWidth("000%"),
      0,
      4
    );
    drawBatterySummary();

    currentMillis = millis();
  }
}

void GUI::loopControls() {
  loopControlRotation();
  loopControlButton();
  loopIRControls();
}

void GUI::loopControlRotation() {
  short rotation = controls.getRotation();

  if (!isSplashPage && rotation != 0) {
    if (isAdjustingSpeed) {
      motorSpeedAdjust += motorSpeedAdjustStep * (float)rotation;
    } else if (isAdjustingMotorDirection) {
      motorDirection *= -1;
    } else {
      if (rotation == 1) {
        currentPage = currentPage == totalPages - 1 ? 0 : currentPage + 1;
      } else if (rotation == -1) {
        currentPage = currentPage == 0 ? totalPages - 1 : currentPage - 1;
      }
    }
  
    drawPage();
  }
}

void GUI::loopControlButton() {
  bool buttonPressed = controls.getButtonPressed();

  if (buttonPressed) {
    if (isSplashPage) {
      isSplashPage = !isSplashPage;
      motor.start();
    } else {
      if (currentPage == 1) {
        if (isAdjustingSpeed) {
          motor.setSpeed(motorSpeedAdjust);
        }
        
        isAdjustingSpeed = !isAdjustingSpeed;
      }

      if (currentPage == 2) {
        if (isAdjustingMotorDirection) {
          motor.setDirection(motorDirection);
        }
        
        isAdjustingMotorDirection = !isAdjustingMotorDirection;
      }

      if (currentPage == 3) {
        if (motor.isMotorRunning()) {
          motor.stop();
        } else {
          motor.start();
        }
      }
    }
  
    drawPage();
  }
}

void GUI::loopIRControls() {
  bool playPausePressed = IRcontrols.isPlayPausePressed();
  bool minusPressed = IRcontrols.isMinusPressed();
  bool plusPressed = IRcontrols.isPlusPressed();
  bool nextPressed = IRcontrols.isNextPressed();
  bool previousPressed = IRcontrols.isPreviousPressed();

  if (isSplashPage && (playPausePressed || minusPressed || plusPressed || nextPressed || previousPressed)) {
    isSplashPage = !isSplashPage;
    motor.start();
    drawPage();
  } else {
    if (playPausePressed) {
      if (motor.isMotorRunning()) {
        motor.stop();
      } else {
        motor.start();
      }

      if (currentPage == 3) {
        drawPage();
      }
    }

    if (minusPressed || plusPressed) {
      if (minusPressed) {
        motorSpeedAdjust -= motorSpeedAdjustStep;
      } else if (plusPressed) {
        motorSpeedAdjust += motorSpeedAdjustStep;
      }

      motor.setSpeed(motorSpeedAdjust);

      if (currentPage == 1) {
        drawPage();
      }
    }

    if (nextPressed || previousPressed) {
      if (nextPressed) {
        currentPage = currentPage == totalPages - 1 ? 0 : currentPage + 1;
      } else if (previousPressed) {
        currentPage = currentPage == 0 ? totalPages - 1 : currentPage - 1;
      }

      drawPage();
    }
  }
}

void GUI::drawBatterySummary() {
  oled.setCursor(oled.displayWidth() - oled.strWidth("000%"), 0);
  oled.print(batteryReader.getPercentage());
  oled.print("%");
}

void GUI::drawPagination() {
  //oled.setCursor(oled.displayWidth() - oled.strWidth("9/9"), 1);
  oled.setCursor(0, 1);
  oled.print(currentPage + 1);
  oled.print("/");
  oled.print(totalPages);
}

void GUI::drawPage() {
  oled.clear();
  oled.setCursor(0, 0);

  if (currentPage == 0) {
    drawPageSummary();
  }
  
  if (currentPage == 1) {
    drawPageMotorSpeed();
  }

  if (currentPage == 2) {
    drawPageMotorDirection();
  }

  if (currentPage == 3) {
    drawPageMotorControl();
  }

  if (currentPage == 4) {
    drawPageBattery();
  }

  drawBatterySummary();
  drawPagination();
}

void GUI::drawPageSplash() {
  oled.println("StarTracker v0.1");
  oled.println();
  oled.println();
  oled.println();
  oled.println("Press any button");
  oled.println("to start tracking");
}

void GUI::drawPageSummary() {
  oled.println("SUMMARY");
  oled.println();
  // oled.println("                      ");
  oled.println("Motor speed:");
  if (motor.isMotorRunning()) {
    oled.print(motor.getSpeed());
  } else {
    oled.print("Stopped");
  }
  oled.println(" steps/s");
  oled.println("");
  oled.println("Battery: ");
  oled.print(batteryReader.getPercentage());
  oled.println("%");
}

void GUI::drawPageMotorSpeed() {
  oled.println("MOTOR SPEED");
  oled.println();
  oled.print("Original: ");
  oled.println(motor.getOriginalSpeed());
  oled.print("Current: ");
  oled.println(motor.getSpeed());
  oled.print("Max: ");
  oled.println(motor.getMaxSpeed());
  oled.print("Adjust: ");
  oled.print(motorSpeedAdjust);
  oled.println(isAdjustingSpeed ? "_" : "<");
}

void GUI::drawPageMotorDirection() {
  oled.println("MOTOR DIRECTION");
  oled.println();
  oled.print("Direction: ");
  oled.print(motorDirection == motor.getOriginalDirection() ? "Normal" : "Reversed");
  oled.println(isAdjustingMotorDirection ? "_" : "<");
}

void GUI::drawPageMotorControl() {
  oled.println("MOTOR CONTROL");
  oled.println();
  oled.print("Status: ");
  oled.println(motor.isMotorRunning() ? "Running" : "Stopped");
  oled.println();
  oled.print(motor.isMotorRunning() ? "Stop" : "Start");
  oled.println("<");
}

void GUI::drawPageBattery() {
  oled.println("BATTERY");
  oled.println();
  oled.print("Min voltage: ");
  oled.print((float)batteryReader.getMinVoltage() / 1000.0);
  oled.println("V");
  oled.print("Max voltage: ");
  oled.print((float)batteryReader.getMaxVoltage() / 1000.0);
  oled.println("V");
  oled.print("Current: ");
  oled.print((float)batteryReader.getVoltage() / 1000.0);
  oled.println("V");
  oled.print("Percentage: ");
  oled.print(batteryReader.getPercentage());
  oled.println("%");
}
