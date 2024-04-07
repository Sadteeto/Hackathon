#include "Arduino.h"
#include "esp_http_client.h"
// #include "esp_timer.h"
// #include "esp_camera.h"
// #include "img_converters.h"
// #include "fb_gfx.h"
// #include "esp32-hal-ledc.h"
// #include "sdkconfig.h"
// #include "camera_index.h"

#define SERVER "http://192.168.137.78:5000/post"


esp_err_t _http_event_handler(esp_http_client_event_t *evt) {
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGD("HTTP", "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGD("HTTP", "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGD("HTTP", "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGD("HTTP", "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGD("HTTP", "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGD("HTTP", "HTTP_EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGD("HTTP", "HTTP_EVENT_DISCONNECTED");
            break;
    }
    return ESP_OK;
}



void send_post_request_start() {
    esp_http_client_config_t config = {
        .url = SERVER,
        .event_handler = _http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);

    // Set the HTTP request type to POST
    esp_http_client_set_method(client, HTTP_METHOD_POST);

    // Set the POST data content type and body
    esp_http_client_set_header(client, "Content-Type", "application/json");
    const char *post_data = "{\"button\":\"rec_start\"}";
    esp_http_client_set_post_field(client, post_data, strlen(post_data));

    // Perform the HTTP POST request
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK) {
        ESP_LOGI("HTTP", "HTTP POST Status = %d, content_length = %d",
                 esp_http_client_get_status_code(client),
                 esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE("HTTP", "HTTP POST request failed: %s", esp_err_to_name(err));
    }

    // Cleanup
    esp_http_client_cleanup(client);
}

void send_post_request_stop() {
    esp_http_client_config_t config = {
        .url = SERVER,
        .event_handler = _http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);

    // Set the HTTP request type to POST
    esp_http_client_set_method(client, HTTP_METHOD_POST);

    // Set the POST data content type and body
    esp_http_client_set_header(client, "Content-Type", "application/json");
    const char *post_data = "{\"button\":\"rec_stop\"}";
    esp_http_client_set_post_field(client, post_data, strlen(post_data));

    // Perform the HTTP POST request
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK) {
        ESP_LOGI("HTTP", "HTTP POST Status = %d, content_length = %d",
                 esp_http_client_get_status_code(client),
                 esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE("HTTP", "HTTP POST request failed: %s", esp_err_to_name(err));
    }

    // Cleanup
    esp_http_client_cleanup(client);
}