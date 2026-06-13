#ifndef XMESHNET_NODE_IDENTITY_H_
#define XMESHNET_NODE_IDENTITY_H_

#include <stdint.h>

#include "esp_err.h"
#include "x_protocol.h"

typedef struct {
    uint8_t node_id[X_NODE_ID_LEN];
    char node_id_str[18];
} x_node_identity_t;

esp_err_t x_node_identity_load(x_node_identity_t *identity);
void x_node_identity_format(const uint8_t node_id[X_NODE_ID_LEN], char out[18]);

#endif
