# Build the executable based on the source files
set(TARGET_NAME TimerRun)
add_executable(${TARGET_NAME}
  ${CMAKE_SOURCE_DIR}/Projects/Peripheral_Examples/DualTimer/TimerRun/main.c 
  ${CMAKE_SOURCE_DIR}/Projects/Peripheral_Examples/DualTimer/TimerRun/W7500x_it.c
  ${CMAKE_SOURCE_DIR}/Libraries/Startup/startup_W7500.s
  )
target_include_directories(${TARGET_NAME} PUBLIC
  ${CMAKE_SOURCE_DIR}/Projects/Peripheral_Examples/DualTimer/TimerRun
  )

target_link_libraries(${TARGET_NAME} PRIVATE
    DUALTIMER_FILES
    GPIO_FILES
    SYSTEM_W7500X_FILES
    )

complie_link_option(${TARGET_NAME})
create_binary_file(${TARGET_NAME})

