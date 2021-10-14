#ifndef MOTOR_h
#define MOTOR_h

#include <math.h>

/*
 * Definitions for StepperMotor
 */
#define motorPin1  8 // IN1 pin on the ULN2003A driver
#define motorPin2  9 // IN2 pin on the ULN2003A driver
#define motorPin3  10 // IN3 pin on the ULN2003A driver
#define motorPin4  11 // IN4 pin on the ULN2003A driver

/*
 * Definitions of hardware
 */
const float motorMaxSpeed = 400.0;
const int stepsPerRevolution = 2038; // In full step mode, for half step mode multiply by 2 and reduce max speed by half
const int gear1Teeth = 16;
const int gear2Teeth = 40; // Not needed
const int gear3Teeth = 83;
const int hingeRadius = 379; // mm
const short outDirection = -1; // We need to move the motor in different direction

/*
 * We need to calculate the rpm of the outer gear to rotate with the earth
 * https://blarg.co.uk/astronomy/barn-door-tracker-calculator
 * https://www.mathpapa.com/algebra-calculator.html
 */
const float gearRatio = (float)gear1Teeth / (float)gear3Teeth;
const float stepsPerRevolutionGear3 = (float)stepsPerRevolution / gearRatio;
const float gear3RPM = (float)hingeRadius * ((2 * M_PI / 1436) * 0.67);
const float gear3RPS = gear3RPM / 60;
const float stepsPerSecond = stepsPerRevolutionGear3 * gear3RPS;

class Motor
{
  public:
    Motor();
    void loop();
    float getSpeed();
    float getOriginalSpeed();
    float getMaxSpeed();
    short getDirection();
    short getOriginalDirection();
    void setDirection(short newOutDirection);
    void setSpeed(float newExtraSteps);
    void start();
    void stop();
    bool isMotorRunning();
};

#endif
