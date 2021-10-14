#ifndef CONTROLS_h
#define CONTROLS_h

/*
 * Definitions for Rotary Encoder
 */
#define CLK 2
#define DT 3
#define SW 4

class Controls
{
  public:
    Controls();
    void loop();
    short getRotation();
    bool getButtonPressed();
    
  private:
    void loopRotation();
    void loopButton();
};

#endif
