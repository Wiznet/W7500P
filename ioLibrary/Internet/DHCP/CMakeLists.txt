add_library(DHCP_FILES STATIC)

target_sources(DHCP_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/ioLibrary/Internet/DHCP/dhcp.c
        )

target_include_directories(DHCP_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/ioLibrary/Internet/DHCP
        )

target_link_libraries(DHCP_FILES PUBLIC
        SOCKET_FILES
        WZTOE_FILES
        )
