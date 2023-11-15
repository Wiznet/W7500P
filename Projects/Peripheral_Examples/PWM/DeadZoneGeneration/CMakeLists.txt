# Build the executable based on the source files
set(TARGET_NAME DeadZoneGeneration)
add_executable(${TARGET_NAME}
  ${CMAKE_SOURCE_DIR}/Projects/Peripheral_Examples/PWM/DeadZoneGeneration/main.c
  ${CMAKE_SOURCE_DIR}/Libraries/Startup/startup_W7500.s
  )
target_include_directories(${TARGET_NAME} PUBLIC
  ${CMAKE_SOURCE_DIR}/Projects/Peripheral_Examples/PWM/DeadZoneGeneration
)
target_link_libraries(${TARGET_NAME} PRIVATE
    GPIO_FILES
    PWM_FILES
    SYSTEM_W7500X_FILES  
    )

complie_link_option(${TARGET_NAME})
create_binary_file(${TARGET_NAME})

