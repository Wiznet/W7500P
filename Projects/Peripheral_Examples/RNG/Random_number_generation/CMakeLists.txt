# Build the executable based on the source files
set(TARGET_NAME Random_number_generation)
add_executable(${TARGET_NAME}
  ${CMAKE_SOURCE_DIR}/Projects/Peripheral_Examples/RNG/Random_number_generation/main.c 
  ${CMAKE_SOURCE_DIR}/Projects/Peripheral_Examples/RNG/Random_number_generation/retarget.c
  ${CMAKE_SOURCE_DIR}/Projects/Peripheral_Examples/RNG/Random_number_generation/W7500x_it.c
  ${CMAKE_SOURCE_DIR}/Libraries/Startup/startup_W7500.s
  )

target_include_directories(${TARGET_NAME} PUBLIC
  ${CMAKE_SOURCE_DIR}/Projects/Peripheral_Examples/RNG/Random_number_generation
  )
target_link_libraries(${TARGET_NAME} PRIVATE
    RNG_FILES
    GPIO_FILES
    UART_FILES
    SYSTEM_W7500X_FILES
    )

complie_link_option(${TARGET_NAME})
create_binary_file(${TARGET_NAME})

