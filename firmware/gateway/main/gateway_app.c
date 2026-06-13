#include "gateway_app.h"

#include "esp_log.h"

#include "mesh_root.h"
#include "mqtt_client.h"
#include "node_registry.h"
#include "ota_manager.h"
#include "web_admin.h"
#include "x_config.h"
#include "x_node_identity.h"

static const char *TAG = "x_gateway";

esp_err_t x_gateway_app_start(void)
{
    x_config_t config;
    x_node_identity_t identity;

    ESP_ERROR_CHECK(x_config_init_storage());
    ESP_ERROR_CHECK(x_config_load(&config));
    ESP_ERROR_CHECK(x_node_identity_load(&identity));

    ESP_LOGI(TAG, "starting gateway node_id=%s", identity.node_id_str);
    ESP_LOGI(TAG, "mesh_id=%02X-%02X-%02X-%02X-%02X-%02X mqtt=%s",
             config.mesh_id[0], config.mesh_id[1], config.mesh_id[2],
             config.mesh_id[3], config.mesh_id[4], config.mesh_id[5], config.mqtt_uri);

    ESP_ERROR_CHECK(x_node_registry_init());
    ESP_ERROR_CHECK(x_mesh_root_start(&config, &identity));
    ESP_ERROR_CHECK(x_mqtt_client_start(&config, &identity));
    ESP_ERROR_CHECK(x_web_admin_start(&config));
    ESP_ERROR_CHECK(x_ota_manager_init(&config));

    return ESP_OK;
}
