#include "driver/i2s.h"
#define CAMERA_MODEL_ESP32S3_EYE
#include "camera_pins.h"
#include "Arduino.h"


    // Set the I2S configuration as PDM and 16bits per sample

//    i2s_config_t i2s_config = {
//        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX ),
//        .sample_rate = I2S_BITS_PER_SAMPLE_16BIT,
//        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
//        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
//        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
//        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL2,
//        .dma_buf_count = 8,
//        .dma_buf_len = 1024,
//        .use_apll = 0,
//    };
#define SAMPLE_SIZE         (16 * 1024)
#define BUFFER_LEN          64
int16_t i2s_readraw_buff[SAMPLE_SIZE];

  void init_i2s(void){    // Set the I2S configuration as PDM and 16bits per sample
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = 44100,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = 0,
        .dma_buf_count = 8,
        .dma_buf_len = BUFFER_LEN,
        .use_apll = false,
    };


    // The pin config as per the setup
    i2s_pin_config_t pin_config = {
        .mck_io_num = I2S_PIN_NO_CHANGE,
        .bck_io_num = 41,
        .ws_io_num = 42,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = 2,
    };


    int result1 = 0;
    int result2 = 0;
    int result3 = 0;
    // Assuming you use I2S_NUM_0 for this example
    result1 = i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    result2 = i2s_set_pin(I2S_NUM_0, &pin_config);
    // result3 = i2s_set_clk(I2S_NUM_0, 44100, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);

    delay(5000);
    printf("Result 1: %d\n", result1);
    printf("Result 2: %d\n", result2);
    printf("Result 3: %d\n", result3);


    // sample once and print through serial
    size_t bytes_read = 0;
  
    //i2s_read(I2S_NUM_0, data, 1024, &bytes_read, );
    i2s_read(I2S_NUM_0, &i2s_readraw_buff, BUFFER_LEN, &bytes_read, portMAX_DELAY);
    // for (int i = 0; i < 16*64; i++) {
    //     printf("%d ", i2s_readraw_buff[i]);
    // }
    int16_t samples_read = bytes_read / 8;
    if (samples_read > 0) {
      float mean = 0;
      for (int16_t i = 0; i < samples_read; ++i) {
        mean += (i2s_readraw_buff[i]);
      }
 
      // Average the data reading
      mean /= samples_read;
 
      // Print to serial plotter
      Serial.println(mean);
    }
    // Check if the I2S initialization was successful
    
}
