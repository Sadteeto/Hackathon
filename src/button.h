#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

#define AUDIO_BUTTON_NUMBER 0
#define BUTTON_GPIO_PIN GPIO_NUM_1

class audio_button {
public:
    audio_button() {};
    void init();
    void audio_activation();
private:
    void check_buttons();
    bool buttons[4] = {false, false, false, false};
    int voltages[4] = {440, 980, 2400, 2900};
    bool activated;
};

#endif