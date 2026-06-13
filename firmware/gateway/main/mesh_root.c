#include "mesh_root.h"

#include <string.h>

#include "esp_log.h"
#include "node_registry.h"

static const char *TAG = "x_mesh_root";
static x_config_t s_config;
static x_node_identity_t s_identity;

esp_err_t x_mesh_root_start(const x_config_t *config, const x_node_identity_t *identity)
{
    if (config == NULL || identity == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    s_config = *config;
    s_identity = *identity;
    ESP_LOGI(TAG, "mesh root transport placeholder initialized for %s", s_identity.node_id_str);
    return ESP_OK;
}

esp_err_t x_mesh_root_send_command(const uint8_t node_id[X_NODE_ID_LEN], const x_command_payload_t *command)
{
    x_mesh_message_t msg;

    if (node_id == NULL || command == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    ESP_ERROR_CHECK(x_protocol_init_message(&msg,
                                            X_MSG_COMMAND,
                                            s_config.mesh_id,
                                            s_identity.node_id,
                                            0,
                                            0,
                                            command,
                                            sizeof(*command)));
    ESP_ERROR_CHECK(x_protocol_sign_message(&msg, s_config.mesh_auth_key, sizeof(s_config.mesh_auth_key)));

    ESP_LOGI(TAG, "prepared authenticated command for %02X:%02X:%02X:%02X:%02X:%02X (%u bytes)",
             node_id[0], node_id[1], node_id[2], node_id[3], node_id[4], node_id[5],
             (unsigned)x_protocol_wire_size(&msg));
    return ESP_OK;
}
