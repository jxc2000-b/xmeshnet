idf_component_register(
    SRCS
        "../common/src/x_config.c"
        "../common/src/x_node_identity.c"
        "../common/src/x_protocol.c"
        "../common/src/x_security.c"
        "main/gateway_app.c"
        "main/main.c"
        "main/mesh_root.c"
        "main/mqtt_client.c"
        "main/node_registry.c"
        "main/ota_manager.c"
        "main/web_admin.c"
    INCLUDE_DIRS
        "../common/include"
        "main"
    REQUIRES esp_wifi esp_event esp_http_server esp_https_ota mqtt nvs_flash mbedtls json app_update
)
