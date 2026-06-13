#ifndef XMESHNET_CONFIG_H_
#define XMESHNET_CONFIG_H_

#include <stdbool.h>
#include <stdint.h>

#include "esp_err.h"
#include "x_protocol.h"

#define X_MAX_SSID_LEN 32u
#define X_MAX_WIFI_PASSWORD_LEN 64u
#define X_MAX_MESH_PASSWORD_LEN 64u
#define X_MAX_MQTT_URI_LEN 128u
#define X_AUTH_KEY_LEN 32u

typedef struct {
    char wifi_ssid[X_MAX_SSID_LEN + 1];
    char wifi_password[X_MAX_WIFI_PASSWORD_LEN + 1];
    uint8_t mesh_id[X_MESH_ID_LEN];
    char mesh_password[X_MAX_MESH_PASSWORD_LEN + 1];
    uint8_t mesh_auth_key[X_AUTH_KEY_LEN];
    char mqtt_uri[X_MAX_MQTT_URI_LEN + 1];
} x_config_t;

esp_err_t x_config_init_storage(void);
esp_err_t x_config_load(x_config_t *config);
esp_err_t x_config_save(const x_config_t *config);
void x_config_defaults(x_config_t *config);
bool x_config_validate(const x_config_t *config);

#endif
