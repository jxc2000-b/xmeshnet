#ifndef XMESHNET_OTA_MANAGER_H_
#define XMESHNET_OTA_MANAGER_H_

#include "esp_err.h"
#include "x_config.h"

esp_err_t x_ota_manager_init(const x_config_t *config);

#endif
