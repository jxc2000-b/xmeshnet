#include "ota_manager.h"

#include "esp_log.h"

static const char *TAG = "x_ota";

esp_err_t x_ota_manager_init(const x_config_t *config)
{
    if (config == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    ESP_LOGI(TAG, "ota manager placeholder initialized; signed HTTPS OTA required before production");
    return ESP_OK;
}
