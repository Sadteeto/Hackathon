#include <button.h>
#include <Arduino.h>


/*! @brief Initialises the button GPIO pins. */
void audio_button::init() {
    pinMode(BUTTON_GPIO_PIN, INPUT);
}


/*! @brief Checks if the audio needs to be activated. */
int audio_button::audio_activation() {
    check_buttons();
    if(!activated) {
        if(buttons[AUDIO_BUTTON_NUMBER]) {
            // Start Sending Audio
            Serial.println("Send Audio");
            activated = true;
            return 1;
        }
    } else {
        if(!buttons[AUDIO_BUTTON_NUMBER]) {
            // Second INTERRUPT to Stop Sending Audio
            Serial.println("Stop Audio");
            activated = false;
            return 2;
        }
    }
    if(buttons[CAPTURE_BUTTON_NUMBER]) {
        Serial.println("Take Picture");
        return 3;
    }
    return 0;
}


/*! @brief Checks the button GPIO to determine which button is being pressed. */
void audio_button::check_buttons() {
    const char message[] = "Button Output: ";
    int voltage_out = analogRead(BUTTON_GPIO_PIN);
    Serial.print(message);
    Serial.print("\t");
    Serial.println(voltage_out);
    for(int i = 0; i < 4; i++) {
        buttons[i] = abs(voltage_out - voltages[i]) < 200;
    }
}