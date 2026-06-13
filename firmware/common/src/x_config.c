#include "x_config.h"

#include <string.h>

#include "esp_log.h"
#include "nvs.h"
#include "nvs_flash.h"

#define X_CONFIG_NAMESPACE "xmeshnet"
#define X_KEY_WIFI_SSID "wifi_ssid"
#define X_KEY_WIFI_PASS "wifi_pass"
#define X_KEY_MESH_ID "mesh_id"
#define X_KEY_MESH_PASS "mesh_pass"
#define X_KEY_AUTH_KEY "auth_key"
#define X_KEY_MQTT_URI "mqtt_uri"

static const char *TAG = "x_config";

static esp_err_t get_str(nvs_handle_t handle, const char *key, char *dst, size_t dst_len)
{
    size_t len = dst_len;
    esp_err_t err = nvs_get_str(handle, key, dst, &len);

    if (err == ESP_ERR_NVS_NOT_FOUND) {
        dst[0] = '\0';
        return ESP_OK;
    }

    return err;
}

esp_err_t x_config_init_storage(void)
{
    esp_err_t err = nvs_flash_init();

    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }

    return err;
}

void x_config_defaults(x_config_t *config)
{
    static const uint8_t default_mesh_id[X_MESH_ID_LEN] = {0x78, 0x6d, 0x65, 0x73, 0x68, 0x01};

    if (config == NULL) {
        return;
    }

    memset(config, 0, sizeof(*config));
    memcpy(config->mesh_id, default_mesh_id, sizeof(default_mesh_id));
    strncpy(config->mesh_password, "xmeshnet-local", sizeof(config->mesh_password) - 1);
    strncpy(config->mqtt_uri, "mqtt://broker.local:1883", sizeof(config->mqtt_uri) - 1);

    for (size_t i = 0; i < sizeof(config->mesh_auth_key); i++) {
        config->mesh_auth_key[i] = (uint8_t)(0xa5u ^ (uint8_t)i);
    }
}

esp_err_t x_config_load(x_config_t *config)
{
    nvs_handle_t handle;
    esp_err_t err;
    size_t len;

    if (config == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    x_config_defaults(config);
    err = nvs_open(X_CONFIG_NAMESPACE, NVS_READONLY, &handle);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        return ESP_OK;
    }
    if (err != ESP_OK) {
        return err;
    }

    err = get_str(handle, X_KEY_WIFI_SSID, config->wifi_ssid, sizeof(config->wifi_ssid));
    if (err == ESP_OK) {
        err = get_str(handle, X_KEY_WIFI_PASS, config->wifi_password, sizeof(config->wifi_password));
    }
    if (err == ESP_OK) {
        err = get_str(handle, X_KEY_MESH_PASS, config->mesh_password, sizeof(config->mesh_password));
    }
    if (err == ESP_OK) {
        err = get_str(handle, X_KEY_MQTT_URI, config->mqtt_uri, sizeof(config->mqtt_uri));
    }
    if (err == ESP_OK) {
        len = sizeof(config->mesh_id);
        err = nvs_get_blob(handle, X_KEY_MESH_ID, config->mesh_id, &len);
        if (err == ESP_ERR_NVS_NOT_FOUND) {
            err = ESP_OK;
        }
    }
    if (err == ESP_OK) {
        len = sizeof(config->mesh_auth_key);
        err = nvs_get_blob(handle, X_KEY_AUTH_KEY, config->mesh_auth_key, &len);
        if (err == ESP_ERR_NVS_NOT_FOUND) {
            err = ESP_OK;
        }
    }

    nvs_close(handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "failed to load config: %s", esp_err_to_name(err));
    }

    return err;
}

esp_err_t x_config_save(const x_config_t *config)
{
    nvs_handle_t handle;
    esp_err_t err;

    if (!x_config_validate(config)) {
        return ESP_ERR_INVALID_ARG;
    }

    err = nvs_open(X_CONFIG_NAMESPACE, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        return err;
    }

    err = nvs_set_str(handle, X_KEY_WIFI_SSID, config->wifi_ssid);
    if (err == ESP_OK) {
        err = nvs_set_str(handle, X_KEY_WIFI_PASS, config->wifi_password);
    }
    if (err == ESP_OK) {
        err = nvs_set_blob(handle, X_KEY_MESH_ID, config->mesh_id, sizeof(config->mesh_id));
    }
    if (err == ESP_OK) {
        err = nvs_set_str(handle, X_KEY_MESH_PASS, config->mesh_password);
    }
    if (err == ESP_OK) {
        err = nvs_set_blob(handle, X_KEY_AUTH_KEY, config->mesh_auth_key, sizeof(config->mesh_auth_key));
    }
    if (err == ESP_OK) {
        err = nvs_set_str(handle, X_KEY_MQTT_URI, config->mqtt_uri);
    }
    if (err == ESP_OK) {
        err = nvs_commit(handle);
    }

    nvs_close(handle);
    return err;
}

bool x_config_validate(const x_config_t *config)
{
    if (config == NULL) {
        return false;
    }
    if (strnlen(config->wifi_ssid, sizeof(config->wifi_ssid)) > X_MAX_SSID_LEN) {
        return false;
    }
    if (strnlen(config->wifi_password, sizeof(config->wifi_password)) > X_MAX_WIFI_PASSWORD_LEN) {
        return false;
    }
    if (strnlen(config->mesh_password, sizeof(config->mesh_password)) > X_MAX_MESH_PASSWORD_LEN) {
        return false;
    }
    if (strnlen(config->mqtt_uri, sizeof(config->mqtt_uri)) > X_MAX_MQTT_URI_LEN) {
        return false;
    }

    return true;
}
