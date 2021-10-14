#include <AccelStepper.h>

#include "Motor.h"

float currentExtraSteps = 0.0;
short currentOutDirection = outDirection;
bool isRunning = false;

/*
 * AccelStepper::FULL2WIRE (2) means: 2 wire stepper (2 pins needed). 
 * AccelStepper::FULL3WIRE (3) means: 3 wire stepper, like a harddisk motor (3 pins needed). 
 * AccelStepper::FULL4WIRE (4) means: 4 wire stepper (4 pins needed). 
 * AccelStepper::HALF3WIRE (6) means: 3 wire half stepper, like a harddisk motor (3 pins needed) 
 * AccelStepper::HALF4WIRE (8) means: 4 wire half stepper (4 pins needed) 
 *
 * AccelStepper uses AccelStepper::FULL4WIRE (4 pins needed) by default.
 */
AccelStepper stepper(AccelStepper::FULL4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);

Motor::Motor() {  
  stepper.setMaxSpeed(motorMaxSpeed);
  setSpeed(0);
}

void Motor::loop() {
  if (isRunning) {
    stepper.runSpeed();
  }
}

void Motor::setSpeed(float newExtraSteps) {
  currentExtraSteps = newExtraSteps;
  stepper.setSpeed((stepsPerSecond + currentExtraSteps) * (float)currentOutDirection);
}

float Motor::getSpeed() {
  return stepsPerSecond + currentExtraSteps;
}

float Motor::getOriginalSpeed() {
  return stepsPerSecond;
}

float Motor::getMaxSpeed() {
  return motorMaxSpeed;
}

short Motor::getDirection() {
  return currentOutDirection;
}

short Motor::getOriginalDirection() {
  return outDirection;
}

void Motor::setDirection(short newOutDirection) {
  currentOutDirection = newOutDirection;
  setSpeed(currentExtraSteps);
}

void Motor::start() {
  isRunning = true;
}

void Motor::stop() {
  isRunning = false;
}

bool Motor::isMotorRunning() {
  return isRunning;
}
