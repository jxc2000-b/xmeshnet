#include "x_protocol.h"

#include "esp_err.h"

esp_err_t x_mesh_client_send_status(const x_mesh_message_t *msg)
{
    return msg == NULL ? ESP_ERR_INVALID_ARG : ESP_OK;
}
