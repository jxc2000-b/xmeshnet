#ifndef XMESHNET_NODE_REGISTRY_H_
#define XMESHNET_NODE_REGISTRY_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "esp_err.h"
#include "x_protocol.h"

#define X_NODE_REGISTRY_MAX_NODES 64u

typedef struct {
    uint8_t node_id[X_NODE_ID_LEN];
    uint32_t last_seq;
    uint32_t last_seen_s;
    x_node_status_payload_t status;
    bool in_use;
} x_registered_node_t;

esp_err_t x_node_registry_init(void);
esp_err_t x_node_registry_upsert_status(const x_msg_header_t *header, const x_node_status_payload_t *status);
size_t x_node_registry_snapshot(x_registered_node_t *out, size_t capacity);

#endif
