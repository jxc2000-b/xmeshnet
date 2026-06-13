#ifndef XMESHNET_PROTOCOL_H_
#define XMESHNET_PROTOCOL_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "esp_err.h"

#define X_MESH_ID_LEN 6u
#define X_NODE_ID_LEN 6u
#define X_AUTH_TAG_LEN 16u
#define X_PROTOCOL_VERSION 1u
#define X_MAX_PAYLOAD_LEN 1024u

typedef enum {
    X_MSG_NODE_STATUS = 1,
    X_MSG_SENSOR_EVENT = 2,
    X_MSG_COMMAND = 3,
    X_MSG_COMMAND_ACK = 4,
    X_MSG_OTA_CHUNK = 5,
    X_MSG_OTA_STATUS = 6
} x_msg_type_t;

typedef struct {
    uint8_t version;
    uint8_t msg_type;
    uint8_t mesh_id[X_MESH_ID_LEN];
    uint8_t node_id[X_NODE_ID_LEN];
    uint32_t seq;
    uint32_t timestamp;
    uint16_t payload_len;
    uint8_t auth[X_AUTH_TAG_LEN];
} __attribute__((packed)) x_msg_header_t;

typedef struct {
    x_msg_header_t header;
    uint8_t payload[X_MAX_PAYLOAD_LEN];
} x_mesh_message_t;

typedef struct {
    uint8_t battery_percent;
    int8_t rssi;
    uint32_t uptime_s;
    uint32_t free_heap;
} __attribute__((packed)) x_node_status_payload_t;

typedef struct {
    uint16_t event_type;
    uint16_t value_len;
    uint8_t value[128];
} __attribute__((packed)) x_sensor_event_payload_t;

typedef struct {
    uint16_t command_type;
    uint16_t value_len;
    uint8_t value[256];
} __attribute__((packed)) x_command_payload_t;

typedef struct {
    uint32_t command_seq;
    int32_t status;
} __attribute__((packed)) x_command_ack_payload_t;

typedef struct {
    char version[32];
    uint32_t offset;
    uint32_t data_size;
    uint32_t total_size;
    uint8_t data[1024];
} __attribute__((packed)) x_ota_chunk_payload_t;

esp_err_t x_protocol_init_message(x_mesh_message_t *msg,
                                  x_msg_type_t type,
                                  const uint8_t mesh_id[X_MESH_ID_LEN],
                                  const uint8_t node_id[X_NODE_ID_LEN],
                                  uint32_t seq,
                                  uint32_t timestamp,
                                  const void *payload,
                                  size_t payload_len);

esp_err_t x_protocol_sign_message(x_mesh_message_t *msg,
                                  const uint8_t *key,
                                  size_t key_len);

bool x_protocol_verify_message(const x_mesh_message_t *msg,
                               const uint8_t *key,
                               size_t key_len);

size_t x_protocol_wire_size(const x_mesh_message_t *msg);
bool x_protocol_is_valid_type(uint8_t msg_type);

#endif
