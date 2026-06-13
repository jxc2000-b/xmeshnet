#include "x_protocol.h"

#include "esp_system.h"

void x_sensors_read_status(x_node_status_payload_t *status)
{
    if (status == NULL) {
        return;
    }

    status->battery_percent = 100;
    status->rssi = 0;
    status->uptime_s = 0;
    status->free_heap = esp_get_free_heap_size();
}
