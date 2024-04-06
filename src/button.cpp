#include <button.h>


/*! @brief Initialises the button GPIO pins. */
void audio_button::init() {
    pinMode(BUTTON_GPIO_PIN, INPUT);
}


/*! @brief Checks if the audio needs to be activated. */
void audio_button::audio_activation(bool activated) {
    check_buttons();
    if(!activated) {
        if(buttons[AUDIO_BUTTON_NUMBER]) {
            // Start Sending Audio
        }
    }
}


/*! @brief Checks the button GPIO to determine which button is being pressed. */
void audio_button::check_buttons() {
    int voltage_out = analogRead(BUTTON_GPIO_PIN);
    Serial.println(voltage_out);
    for(int i = 0; i < 4; i++) {
        buttons[i] = abs(voltage_out - voltages[i]) < 15;
    }
}