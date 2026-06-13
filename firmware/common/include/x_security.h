#ifndef XMESHNET_SECURITY_H_
#define XMESHNET_SECURITY_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "esp_err.h"

esp_err_t x_security_hmac_sha256_truncated(const uint8_t *key,
                                           size_t key_len,
                                           const uint8_t *data,
                                           size_t data_len,
                                           uint8_t *out,
                                           size_t out_len);

bool x_security_constant_time_equal(const uint8_t *a, const uint8_t *b, size_t len);

#endif
