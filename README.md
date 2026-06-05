# 🦅 FlockKiller

**AI vision inference on ESP32 chips** — real-time bird detection and automated deterrence at the edge.

FlockKiller runs computer vision models directly on low-cost ESP32 microcontrollers with camera modules to detect, identify, and deter pest bird flocks in agricultural, industrial, and urban settings. No cloud. No latency. No recurring costs.

## The Problem

Birds cause **billions** in crop damage annually. Existing solutions are expensive (laser systems, netting), labor-intensive (scarecrows, gas cannons), or harmful (poisons). We need a **cheap, smart, autonomous** alternative.

## The Solution

A distributed network of ESP32 camera nodes running lightweight AI vision models. Each node:

- 📷 **Captures** images via OV2640/OV5640 camera
- 🧠 **Detects** birds in real-time using on-device ML inference
- 🔊 **Deters** via directional audio, strobe lights, or actuator triggers
- 📡 **Reports** to a central hub via Wi-Fi/BLE for fleet monitoring

## Hardware Targets

| Chip | Camera | ML Capability |
|------|--------|---------------|
| ESP32-S3 | OV2640 / OV5640 | TensorFlow Lite Micro, ~1-3 FPS inference |
| ESP32-CAM | OV2640 | ESP-WHO face detect adapted for birds |
| ESP32-P4 | OV5640 | Higher throughput, multi-model pipeline |

## Tech Stack

- **Framework:** ESP-IDF v5.x / Arduino-ESP32
- **ML Runtime:** TensorFlow Lite Micro / ESP-DL / ESP-WHO
- **Models:** MobileNetV2-SSD, custom bird detection YOLO-nano
- **Deterrence:** I2S audio output, GPIO relays, PWM motor control
- **Comms:** Wi-Fi (MQTT/HTTP), ESP-NOW mesh, BLE
- **Power:** Solar + LiPo battery management

## Project Structure

```
flockkiller/
├── firmware/           # ESP32 firmware (ESP-IDF / Arduino)
│   ├── main/           # Application entry point
│   ├── components/     # Reusable modules (camera, ml, audio, network)
│   ├── models/         # TFLite model files (.tflite)
│   └── partitions.csv  # Flash partition table
├── models/             # Model training & conversion scripts
│   ├── training/       # PyTorch/TF training notebooks
│   ├── datasets/       # Bird detection dataset manifests
│   └── convert/        # Model quantization & TFLite conversion
├── hub/                # Central monitoring hub (optional)
│   ├── backend/        # API server (Python/FastAPI)
│   └── frontend/       # Dashboard (React/Next.js)
├── hardware/           # PCB designs, BOM, enclosure files
├── docs/               # Documentation & research
└── README.md
```

## Quick Start

```bash
# Clone the repo
git clone https://github.com/jxc2000-b/flockkiller.git
cd flockkiller

# Install ESP-IDF (if not already)
# https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/

# Build & flash (ESP32-S3 example)
cd firmware
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```

## Status

🚧 **Early development** — architecture design and prototyping phase.

### Roadmap

- [ ] Camera capture pipeline on ESP32-S3
- [ ] TFLite bird detection model ported & quantized
- [ ] Real-time inference loop at ≥1 FPS
- [ ] Audio deterrence output (directional speaker trigger)
- [ ] ESP-NOW mesh networking for multi-node deployment
- [ ] Solar power management (sleep/wake cycle)
- [ ] Central hub dashboard for fleet monitoring
- [ ] Field testing on actual birds

## License

MIT — see [LICENSE](LICENSE) file.

---

*Built for farmers. Powered by edge AI. No birds allowed.*
