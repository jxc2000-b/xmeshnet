# MQTT Topics

Telemetry:

```text
mesh/{mesh_id}/gateway/{gateway_id}/status
mesh/{mesh_id}/node/{node_id}/status
mesh/{mesh_id}/node/{node_id}/event
mesh/{mesh_id}/ota/status
```

Commands:

```text
mesh/{mesh_id}/gateway/{gateway_id}/command
mesh/{mesh_id}/node/{node_id}/command
```

Gateway command handlers should authenticate cloud commands before forwarding them into the mesh.
