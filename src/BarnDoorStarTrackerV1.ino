#include "Globals.h"
#include "Motor.h"
#include "Controls.h"
#include "IRControls.h"
#include "GUI.h"
#include "BatteryReader.h"

void setup() {
  motor = Motor();
  batteryReader = BatteryReader();
  controls = Controls();
  IRcontrols = IRControls();
  gui = GUI();

  gui.drawPageSplash();
}

void loop() {
  controls.loop();
  IRcontrols.loop();
  batteryReader.loop();
  gui.loop();
  motor.loop();
}
