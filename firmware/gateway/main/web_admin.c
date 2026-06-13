#include "web_admin.h"

#include "esp_log.h"

static const char *TAG = "x_web_admin";

esp_err_t x_web_admin_start(const x_config_t *config)
{
    if (config == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    ESP_LOGI(TAG, "web admin placeholder enabled; password values will not be logged");
    return ESP_OK;
}
