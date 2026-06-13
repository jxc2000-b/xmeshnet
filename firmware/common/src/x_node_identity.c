#include "x_node_identity.h"

#include <stdio.h>
#include <string.h>

#include "esp_mac.h"

esp_err_t x_node_identity_load(x_node_identity_t *identity)
{
    esp_err_t err;

    if (identity == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    memset(identity, 0, sizeof(*identity));
    err = esp_read_mac(identity->node_id, ESP_MAC_WIFI_STA);
    if (err != ESP_OK) {
        return err;
    }

    x_node_identity_format(identity->node_id, identity->node_id_str);
    return ESP_OK;
}

void x_node_identity_format(const uint8_t node_id[X_NODE_ID_LEN], char out[18])
{
    if (node_id == NULL || out == NULL) {
        return;
    }

    snprintf(out, 18, "%02X:%02X:%02X:%02X:%02X:%02X",
             node_id[0], node_id[1], node_id[2],
             node_id[3], node_id[4], node_id[5]);
}
