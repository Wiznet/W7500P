#SYSTEM W7500x
add_library(SYSTEM_W7500X_FILES STATIC)

target_sources(SYSTEM_W7500X_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c
        )

target_include_directories(SYSTEM_W7500X_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/CMSIS/Device/WIZnet/W7500/Include
        ${CMAKE_SOURCE_DIR}/Libraries/CMSIS/Include
        )

#GPIO
add_library(GPIO_FILES STATIC)

target_sources(GPIO_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c
        )

target_include_directories(GPIO_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/inc
        )
target_link_libraries(GPIO_FILES PUBLIC
        SYSTEM_W7500X_FILES
        )

#PWM
add_library(PWM_FILES STATIC)
target_sources(PWM_FILES PUBLIC
${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c
)

target_include_directories(PWM_FILES PUBLIC
${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/inc
)

target_link_libraries(PWM_FILES PUBLIC
        SYSTEM_W7500X_FILES
)

#ADC
add_library(ADC_FILES STATIC)
target_sources(ADC_FILES PUBLIC
${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/src/W7500x_adc.c
        )

target_include_directories(ADC_FILES PUBLIC
${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/inc
        )
target_link_libraries(ADC_FILES PUBLIC
        SYSTEM_W7500X_FILES
        )

#UART
add_library(UART_FILES STATIC)
target_sources(UART_FILES PUBLIC
${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/src/W7500x_uart.c
        )

target_include_directories(UART_FILES PUBLIC
${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/inc
        )

target_link_libraries(UART_FILES PUBLIC
        GPIO_FILES
        SYSTEM_W7500X_FILES
        )

#DUAL TIMER
add_library(DUALTIMER_FILES STATIC)

target_sources(DUALTIMER_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/src/W7500x_dualtimer.c
        )

target_include_directories(DUALTIMER_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/inc
        )

target_link_libraries(DUALTIMER_FILES PUBLIC
        SYSTEM_W7500X_FILES
        )

#EXTI
add_library(EXTI_FILES STATIC)

target_sources(EXTI_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/src/W7500x_exti.c
        )

target_include_directories(EXTI_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/inc        
        )

target_link_libraries(EXTI_FILES PUBLIC
        GPIO_FILES
        SYSTEM_W7500X_FILES
        )

#SSP
add_library(SSP_FILES STATIC)

target_sources(SSP_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/src/W7500x_ssp.c 
        )

target_include_directories(SSP_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/inc
        )

target_link_libraries(SSP_FILES PUBLIC
        SYSTEM_W7500X_FILES
        )

#CRG
add_library(CRG_FILES STATIC)

target_sources(CRG_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/src/W7500x_crg.c 
        )

target_include_directories(CRG_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/inc
        )

target_link_libraries(CRG_FILES PUBLIC
        SYSTEM_W7500X_FILES
        )

#WDT
add_library(WDT_FILES STATIC)

target_sources(WDT_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wdt.c 
        )

target_include_directories(WDT_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/inc
        )

target_link_libraries(WDT_FILES PUBLIC
        SYSTEM_W7500X_FILES
        )


#DMA
add_library(DMA_FILES STATIC)

target_sources(DMA_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/src/W7500x_dma.c 
        )

target_include_directories(DMA_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/inc
        ) 

target_link_libraries(DMA_FILES PUBLIC
        SYSTEM_W7500X_FILES
        )

#RNG
add_library(RNG_FILES STATIC)

target_sources(RNG_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/src/W7500x_rng.c      
        )

target_include_directories(RNG_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/inc
        )    

target_link_libraries(RNG_FILES PUBLIC
        SYSTEM_W7500X_FILES
        )
#RTC
add_library(RTC_FILES STATIC)

target_sources(RTC_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/src/W7500x_rtc.c      
        )

target_include_directories(RTC_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/inc
        )    

target_link_libraries(RTC_FILES PUBLIC
        CRG_FILES
        SYSTEM_W7500X_FILES
        )

#WZTOE
add_library(WZTOE_FILES STATIC)

target_sources(WZTOE_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c      
        )

target_include_directories(WZTOE_FILES PUBLIC
        ${CMAKE_SOURCE_DIR}/Libraries/W7500x_stdPeriph_Driver/inc
        )     

target_link_libraries(WZTOE_FILES PUBLIC
        SYSTEM_W7500X_FILES
        )