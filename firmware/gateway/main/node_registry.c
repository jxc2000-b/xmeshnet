#include "node_registry.h"

#include <string.h>

#include "esp_timer.h"

static x_registered_node_t s_nodes[X_NODE_REGISTRY_MAX_NODES];

esp_err_t x_node_registry_init(void)
{
    memset(s_nodes, 0, sizeof(s_nodes));
    return ESP_OK;
}

esp_err_t x_node_registry_upsert_status(const x_msg_header_t *header, const x_node_status_payload_t *status)
{
    x_registered_node_t *slot = NULL;

    if (header == NULL || status == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    for (size_t i = 0; i < X_NODE_REGISTRY_MAX_NODES; i++) {
        if (s_nodes[i].in_use && memcmp(s_nodes[i].node_id, header->node_id, X_NODE_ID_LEN) == 0) {
            slot = &s_nodes[i];
            break;
        }
        if (!s_nodes[i].in_use && slot == NULL) {
            slot = &s_nodes[i];
        }
    }

    if (slot == NULL) {
        return ESP_ERR_NO_MEM;
    }

    slot->in_use = true;
    memcpy(slot->node_id, header->node_id, X_NODE_ID_LEN);
    slot->last_seq = header->seq;
    slot->last_seen_s = (uint32_t)(esp_timer_get_time() / 1000000ULL);
    slot->status = *status;
    return ESP_OK;
}

size_t x_node_registry_snapshot(x_registered_node_t *out, size_t capacity)
{
    size_t count = 0;

    if (out == NULL || capacity == 0) {
        return 0;
    }

    for (size_t i = 0; i < X_NODE_REGISTRY_MAX_NODES && count < capacity; i++) {
        if (s_nodes[i].in_use) {
            out[count++] = s_nodes[i];
        }
    }

    return count;
}
