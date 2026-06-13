#include "x_protocol.h"

#include <string.h>

#include "x_security.h"

static esp_err_t compute_auth(const x_mesh_message_t *msg,
                              const uint8_t *key,
                              size_t key_len,
                              uint8_t out[X_AUTH_TAG_LEN])
{
    x_mesh_message_t tmp;

    if (msg == NULL || key == NULL || key_len == 0 || out == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    tmp = *msg;
    memset(tmp.header.auth, 0, sizeof(tmp.header.auth));

    return x_security_hmac_sha256_truncated(key,
                                            key_len,
                                            (const uint8_t *)&tmp,
                                            x_protocol_wire_size(&tmp),
                                            out,
                                            X_AUTH_TAG_LEN);
}

esp_err_t x_protocol_init_message(x_mesh_message_t *msg,
                                  x_msg_type_t type,
                                  const uint8_t mesh_id[X_MESH_ID_LEN],
                                  const uint8_t node_id[X_NODE_ID_LEN],
                                  uint32_t seq,
                                  uint32_t timestamp,
                                  const void *payload,
                                  size_t payload_len)
{
    if (msg == NULL || mesh_id == NULL || node_id == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    if (!x_protocol_is_valid_type((uint8_t)type) || payload_len > X_MAX_PAYLOAD_LEN) {
        return ESP_ERR_INVALID_SIZE;
    }
    if (payload_len > 0 && payload == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    memset(msg, 0, sizeof(*msg));
    msg->header.version = X_PROTOCOL_VERSION;
    msg->header.msg_type = (uint8_t)type;
    memcpy(msg->header.mesh_id, mesh_id, X_MESH_ID_LEN);
    memcpy(msg->header.node_id, node_id, X_NODE_ID_LEN);
    msg->header.seq = seq;
    msg->header.timestamp = timestamp;
    msg->header.payload_len = (uint16_t)payload_len;
    if (payload_len > 0) {
        memcpy(msg->payload, payload, payload_len);
    }

    return ESP_OK;
}

esp_err_t x_protocol_sign_message(x_mesh_message_t *msg,
                                  const uint8_t *key,
                                  size_t key_len)
{
    if (msg == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    memset(msg->header.auth, 0, sizeof(msg->header.auth));
    return compute_auth(msg, key, key_len, msg->header.auth);
}

bool x_protocol_verify_message(const x_mesh_message_t *msg,
                               const uint8_t *key,
                               size_t key_len)
{
    uint8_t expected[X_AUTH_TAG_LEN];

    if (msg == NULL || msg->header.version != X_PROTOCOL_VERSION ||
        !x_protocol_is_valid_type(msg->header.msg_type) ||
        msg->header.payload_len > X_MAX_PAYLOAD_LEN) {
        return false;
    }

    if (compute_auth(msg, key, key_len, expected) != ESP_OK) {
        return false;
    }

    return x_security_constant_time_equal(expected, msg->header.auth, X_AUTH_TAG_LEN);
}

size_t x_protocol_wire_size(const x_mesh_message_t *msg)
{
    if (msg == NULL || msg->header.payload_len > X_MAX_PAYLOAD_LEN) {
        return 0;
    }

    return sizeof(x_msg_header_t) + msg->header.payload_len;
}

bool x_protocol_is_valid_type(uint8_t msg_type)
{
    switch ((x_msg_type_t)msg_type) {
    case X_MSG_NODE_STATUS:
    case X_MSG_SENSOR_EVENT:
    case X_MSG_COMMAND:
    case X_MSG_COMMAND_ACK:
    case X_MSG_OTA_CHUNK:
    case X_MSG_OTA_STATUS:
        return true;
    default:
        return false;
    }
}
