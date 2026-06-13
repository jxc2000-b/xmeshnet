#include "node_app.h"

#include "esp_log.h"

#include "x_config.h"
#include "x_node_identity.h"

static const char *TAG = "x_node";

esp_err_t x_node_app_start(void)
{
    x_config_t config;
    x_node_identity_t identity;

    ESP_ERROR_CHECK(x_config_init_storage());
    ESP_ERROR_CHECK(x_config_load(&config));
    ESP_ERROR_CHECK(x_node_identity_load(&identity));

    ESP_LOGI(TAG, "starting sensor node node_id=%s", identity.node_id_str);
    return ESP_OK;
}
