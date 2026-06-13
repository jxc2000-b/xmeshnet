#include "mqtt_client.h"

#include "esp_log.h"
#include "mqtt_client.h"

static const char *TAG = "x_mqtt";

esp_err_t x_mqtt_client_start(const x_config_t *config, const x_node_identity_t *identity)
{
    if (config == NULL || identity == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    ESP_LOGI(TAG, "mqtt client placeholder uri=%s gateway=%s", config->mqtt_uri, identity->node_id_str);
    return ESP_OK;
}

esp_err_t x_mqtt_publish_node_status(const x_msg_header_t *header, const x_node_status_payload_t *status)
{
    if (header == NULL || status == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    ESP_LOGI(TAG, "publish node status node=%02X:%02X:%02X:%02X:%02X:%02X battery=%u heap=%lu",
             header->node_id[0], header->node_id[1], header->node_id[2],
             header->node_id[3], header->node_id[4], header->node_id[5],
             status->battery_percent, (unsigned long)status->free_heap);
    return ESP_OK;
}
