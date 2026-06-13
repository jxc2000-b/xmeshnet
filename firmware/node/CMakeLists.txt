idf_component_register(
    SRCS
        "../common/src/x_config.c"
        "../common/src/x_node_identity.c"
        "../common/src/x_protocol.c"
        "../common/src/x_security.c"
        "main/main.c"
        "main/mesh_client.c"
        "main/node_app.c"
        "main/power.c"
        "main/sensors.c"
    INCLUDE_DIRS
        "../common/include"
        "main"
    REQUIRES esp_wifi nvs_flash mbedtls
)
