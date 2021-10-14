#include <Battery.h>

#include "BatteryReader.h"

Battery battery(VOLT_MIN, VOLT_MAX, A0);

BatteryReader::BatteryReader() {
	battery.begin(5000, ratio);
}

void BatteryReader::loop() {
  
}

uint16_t BatteryReader::getVoltage() {
  return battery.voltage();
}

uint8_t BatteryReader::getPercentage() {
  return battery.level();
}

unsigned int BatteryReader::getMaxVoltage() {
  return VOLT_MAX;
}

unsigned int BatteryReader::getMinVoltage() {
  return VOLT_MIN;
}
