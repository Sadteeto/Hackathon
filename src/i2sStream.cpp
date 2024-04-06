#include "driver/i2s.h"
#define CAMERA_MODEL_ESP32S3_EYE
#include "camera_pins.h"
#include "Arduino.h"

#define I2S_PORT I2S_NUM_0
void init_i2s(void)
{
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX), // the mode must be set according to DSP configuration
        .sample_rate = 44100,                                // must be the same as DSP configuration
        .bits_per_sample = (i2s_bits_per_sample_t)16,        // must be the same as DSP configuration
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,         // must be the same as DSP configuration
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL2,
        .dma_buf_count = 3,
        .dma_buf_len = 300,
    };
    i2s_pin_config_t pin_config = {
        .mck_io_num = I2S_PIN_NO_CHANGE,
        .bck_io_num = 41,                  // IIS_SCLK
        .ws_io_num = 42,                   // IIS_LCLK
        .data_out_num = I2S_PIN_NO_CHANGE, // IIS_DSIN
        .data_in_num = 2                   // IIS_DOUT
    };
    i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM_0, &pin_config);
    i2s_zero_dma_buffer(I2S_NUM_0);

}
