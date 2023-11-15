add_library(W7500X_MIIM_FILES STATIC)

target_sources(W7500X_MIIM_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/ioLibrary/MDIO/W7500x_miim.c
        )

target_include_directories(W7500X_MIIM_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/ioLibrary/MDIO
        )

target_link_libraries(W7500X_MIIM_FILES PUBLIC
        GPIO_FILES
        )