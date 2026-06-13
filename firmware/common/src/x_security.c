#include "x_security.h"

#include <string.h>

#include "mbedtls/md.h"

esp_err_t x_security_hmac_sha256_truncated(const uint8_t *key,
                                           size_t key_len,
                                           const uint8_t *data,
                                           size_t data_len,
                                           uint8_t *out,
                                           size_t out_len)
{
    uint8_t full[32];
    const mbedtls_md_info_t *info;

    if (key == NULL || key_len == 0 || data == NULL || out == NULL ||
        out_len == 0 || out_len > sizeof(full)) {
        return ESP_ERR_INVALID_ARG;
    }

    info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
    if (info == NULL) {
        return ESP_FAIL;
    }

    if (mbedtls_md_hmac(info, key, key_len, data, data_len, full) != 0) {
        memset(full, 0, sizeof(full));
        return ESP_FAIL;
    }

    memcpy(out, full, out_len);
    memset(full, 0, sizeof(full));
    return ESP_OK;
}

bool x_security_constant_time_equal(const uint8_t *a, const uint8_t *b, size_t len)
{
    uint8_t diff = 0;

    if (a == NULL || b == NULL) {
        return false;
    }

    for (size_t i = 0; i < len; i++) {
        diff |= (uint8_t)(a[i] ^ b[i]);
    }

    return diff == 0;
}
