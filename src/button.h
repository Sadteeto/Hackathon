#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

#define AUDIO_BUTTON_NUMBER 0
#define BUTTON_ENABLE 3
#define BUTTON_GPIO_PIN 39

class audio_button {
public:
    audio_button() {};
    void init();
    void audio_activation(bool activated);
private:
    void check_buttons();
    bool buttons[4] = {false, false, false, false};
    int voltages[4] = {29, 63, 153, 186};
};

#endif