#ifndef XMESHNET_MQTT_CLIENT_H_
#define XMESHNET_MQTT_CLIENT_H_

#include "esp_err.h"
#include "x_config.h"
#include "x_node_identity.h"
#include "x_protocol.h"

esp_err_t x_mqtt_client_start(const x_config_t *config, const x_node_identity_t *identity);
esp_err_t x_mqtt_publish_node_status(const x_msg_header_t *header, const x_node_status_payload_t *status);

#endif
