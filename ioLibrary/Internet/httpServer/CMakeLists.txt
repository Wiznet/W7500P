add_library(HTTP_PARSER_FILES STATIC)

target_sources(HTTP_PARSER_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/ioLibrary/Internet/httpServer/httpParser.c
        )

target_include_directories(HTTP_PARSER_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/ioLibrary/Internet/httpServer
        )

target_link_libraries(HTTP_PARSER_FILES PUBLIC
        SOCKET_FILES
        WZTOE_FILES
        )

add_library(HTTP_UTIL_FILES STATIC)

target_sources(HTTP_UTIL_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/ioLibrary/Internet/httpServer/httpUtil.c
        )

target_include_directories(HTTP_UTIL_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/ioLibrary/Internet/httpServer
        )

target_link_libraries(HTTP_UTIL_FILES PUBLIC
        WIZCHIP_CONF_FILES
        WZTOE_FILES
        GPIO_FILES
        )


add_library(HTTP_SERVER_FILES STATIC)

target_sources(HTTP_SERVER_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/ioLibrary/Internet/httpServer/httpServer.c
        )

target_include_directories(HTTP_SERVER_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/ioLibrary/Internet/httpServer
        )

target_link_libraries(HTTP_SERVER_FILES PUBLIC
        WIZCHIP_CONF_FILES
        SOCKET_FILES
        WZTOE_FILES
        HTTP_PARSER_FILES
        HTTP_UTIL_FILES
        )
