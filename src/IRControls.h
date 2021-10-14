#ifndef IRCONTROLS_h
#define IRCONTROLS_h

#define IR_RECEIVE_PIN 5

const int receiveInterval = 100;

class IRControls
{
  public:
    IRControls();
    void loop();
    bool isPlayPausePressed();
    bool isMinusPressed();
    bool isPlusPressed();
    bool isNextPressed();
    bool isPreviousPressed();
};

#endif
