#ifndef XMESHNET_MESH_ROOT_H_
#define XMESHNET_MESH_ROOT_H_

#include "esp_err.h"
#include "x_config.h"
#include "x_node_identity.h"
#include "x_protocol.h"

esp_err_t x_mesh_root_start(const x_config_t *config, const x_node_identity_t *identity);
esp_err_t x_mesh_root_send_command(const uint8_t node_id[X_NODE_ID_LEN], const x_command_payload_t *command);

#endif
