# Build the executable based on the source files
set(TARGET_NAME httpClient)

add_executable(${TARGET_NAME}
    ${CMAKE_SOURCE_DIR}/Projects/Peripheral_Examples/WZTOE/httpClient/main.c 
    ${CMAKE_SOURCE_DIR}/Projects/Peripheral_Examples/WZTOE/httpClient/W7500x_it.c
    ${CMAKE_SOURCE_DIR}/Projects/Peripheral_Examples/WZTOE/httpClient/retarget.c
    ${CMAKE_SOURCE_DIR}/Libraries/Startup/startup_W7500.s
    )

target_include_directories(${TARGET_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/Projects/Peripheral_Examples/WZTOE/httpClient
    )

target_link_libraries(${TARGET_NAME} PRIVATE
    WZTOE_FILES
    CRG_FILES
    UART_FILES
    GPIO_FILES
    DNS_FILES
    W7500X_MIIM_FILES
    SYSTEM_W7500X_FILES
    WIZCHIP_CONF_FILES
    DHCP_FILES
    )

complie_link_option(${TARGET_NAME})
create_binary_file(${TARGET_NAME})



