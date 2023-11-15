add_library(SOCKET_FILES STATIC)

target_sources(SOCKET_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/ioLibrary/Ethernet/socket.c
        )

target_include_directories(SOCKET_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/ioLibrary/Ethernet
        )

target_link_libraries(SOCKET_FILES PUBLIC
        SYSTEM_W7500X_FILES
        WZTOE_FILES
        )

add_library(WIZCHIP_CONF_FILES STATIC)

target_sources(WIZCHIP_CONF_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/ioLibrary/Ethernet/wizchip_conf.c
        )

target_include_directories(WIZCHIP_CONF_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/ioLibrary/Ethernet
        )

target_link_libraries(WIZCHIP_CONF_FILES PUBLIC
        SYSTEM_W7500X_FILES
        WZTOE_FILES
        )