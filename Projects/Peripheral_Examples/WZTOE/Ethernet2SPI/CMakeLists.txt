# Build the executable based on the source files
set(TARGET_NAME Ethernet2SPI)

add_executable(${TARGET_NAME}
    ${CMAKE_SOURCE_DIR}/Projects/Peripheral_Examples/WZTOE/Ethernet2SPI/main.c 
    ${CMAKE_SOURCE_DIR}/Projects/Peripheral_Examples/WZTOE/Ethernet2SPI/W7500x_it.c
    ${CMAKE_SOURCE_DIR}/Projects/Peripheral_Examples/WZTOE/Ethernet2SPI/retarget.c
    ${CMAKE_SOURCE_DIR}/Libraries/Startup/startup_W7500.s
    )

target_include_directories(${TARGET_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/Projects/Peripheral_Examples/WZTOE/Ethernet2SPI
    )

target_link_libraries(${TARGET_NAME} PRIVATE
    WZTOE_FILES
    CRG_FILES
    UART_FILES
    GPIO_FILES
    W7500X_MIIM_FILES
    SYSTEM_W7500X_FILES
    SSP_FILES
    SOCKET_FILES
    )

complie_link_option(${TARGET_NAME})
create_binary_file(${TARGET_NAME})



