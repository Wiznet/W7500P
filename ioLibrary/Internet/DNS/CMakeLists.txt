add_library(DNS_FILES STATIC)

target_sources(DNS_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/ioLibrary/Internet/DNS/dns.c
        )

target_include_directories(DNS_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/ioLibrary/Internet/DNS
        )

target_link_libraries(DNS_FILES PUBLIC
        SOCKET_FILES
        WZTOE_FILES
        )