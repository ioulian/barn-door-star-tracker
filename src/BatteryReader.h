#ifndef BATTERY_READER_h
#define BATTERY_READER_h

#define BATTERY_PIN A0;

const unsigned int R1 = 30000;
const unsigned int R2 = 7500;
const unsigned int VOLT_MIN = 7500;
const unsigned int VOLT_MAX = 10950;
// const float ratio = (R1 + R2) / R2;
const float ratio = 5.0;

class BatteryReader
{
  public:
    BatteryReader();
    void loop();
    uint16_t getVoltage();
    uint8_t getPercentage();
    unsigned int getMaxVoltage();
    unsigned int getMinVoltage();
};

#endif
