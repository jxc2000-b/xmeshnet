# FlockKiller Firmware

ESP32 on-device AI vision pipeline for bird detection and deterrence.

## Building

### Prerequisites

- ESP-IDF v5.2+ ([installation guide](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/))
- ESP32-S3 or ESP32-CAM dev board
- OV2640 or OV5640 camera module

### Build & Flash

```bash
cd firmware
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```

### Hardware Wiring

| ESP32-S3 Pin | Camera Pin |
|-------------|------------|
| GPIO 10     | XCLK       |
| GPIO 11     | PCLK       |
| GPIO 12     | VSYNC      |
| GPIO 13     | HREF       |
| GPIO 14     | D0         |
| GPIO 15     | D1         |
| GPIO 16     | D2         |
| GPIO 17     | D3         |
| GPIO 18     | D4         |
| GPIO 21     | D5         |
| GPIO 47     | D6         |
| GPIO 48     | D7         |
| 3.3V        | VCC        |
| GND         | GND        |
| GPIO 38     | SDA (SCCB) |
| GPIO 39     | SCL (SCCB) |

## Architecture

```
Camera (OV2640) → Frame Buffer (PSRAM) → Preprocessing → TFLite Inference → Decision → Deterrence Output
                                                                                  ↓
                                                                              MQTT Report → Hub
```

## Component Modules

- `camera/` — OV2640/OV5640 driver, frame capture, JPEG decoding
- `ml/` — TensorFlow Lite Micro runtime, model loading, inference loop
- `audio/` — I2S audio output for directional speaker deterrence
- `network/` — Wi-Fi connection, MQTT client, ESP-NOW mesh
- `power/` — Deep sleep management, battery voltage monitoring
