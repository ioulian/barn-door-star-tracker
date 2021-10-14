#ifndef GUI_h
#define GUI_h

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

const float motorSpeedAdjustStep = 5.0;
const long batteryDisplayInterval = 30000;

class GUI
{
  public:
    GUI();
    void loop();
    void drawPage();
    void drawPageSplash();
  private:
    void loopControls();
    void loopControlRotation();
    void loopControlButton();
    void loopIRControls();
    void drawPageSummary();
    void drawPageMotorSpeed();
    void drawPageMotorDirection();
    void drawPageMotorControl();
    void drawPageBattery();
    void drawBatterySummary();
    void drawPagination();
};

#endif
