# Firmware Layout

```text
firmware/common   Shared protocol, security, config, identity
firmware/gateway  Root gateway behavior
firmware/node     Sensor/relay node behavior
```

The common code is intentionally independent of node or gateway roles. Gateway and node firmware both use the same authenticated `x_mesh_message_t` envelope.
