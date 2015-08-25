;/**************************************************************************/
;/**
; * @file    startup_W7500x.s 
; * @author  IOP Team
; * @version V1.0.0
; * @date    01-May-2015
; * @brief   CMSIS Cortex-M0 Core Device Startup File for Device W7500x
; ******************************************************************************
; *
; * @attention
; * @par Revision history
; *    <2015/05/01> 1st Release
; *
; * <h2><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h2>
; ******************************************************************************
; */


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000400

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler
                DCD     SSP0_Handler              ; 16+ 0: SSP 0 Handler                   
                DCD     SSP1_Handler              ; 16+ 1: SSP 1 Handler                   
                DCD     UART0_Handler             ; 16+ 2: UART 0 Handler                  
                DCD     UART1_Handler             ; 16+ 3: UART 1 Handler                  
                DCD     UART2_Handler             ; 16+ 4: UART 2 Handler                  
                DCD     I2C0_Handler              ; 16+ 5: I2C 0 Handler                   
                DCD     I2C1_Handler              ; 16+ 6: I2C 1 Handler                   
                DCD     PORT0_Handler             ; 16+ 7: GPIO Port 0 Combined Handler    
                DCD     PORT1_Handler             ; 16+ 8: GPIO Port 1 Combined Handler    
                DCD     PORT2_Handler             ; 16+ 9: GPIO Port 2 Combined Handler    
                DCD     PORT3_Handler             ; 16+10: GPIO Port 3 Combined Handler    
                DCD     DMA_Handler               ; 16+11: DMA Combined Handler            
	            DCD     DUALTIMER0_Handler        ; 16+12: Dual timer 0 handler             
	            DCD     DUALTIMER1_Handler        ; 16+13: Dual timer 1 handler            
                DCD     PWM0_Handler              ; 16+14: PWM0 Handler                    
                DCD     PWM1_Handler              ; 16+15: PWM1 Handler                    
                DCD     PWM2_Handler              ; 16+16: PWM2 Handler                    
                DCD     PWM3_Handler              ; 16+17: PWM3 Handler                    
                DCD     PWM4_Handler              ; 16+18: PWM4 Handler                    
                DCD     PWM5_Handler              ; 16+19: PWM5 Handler                    
                DCD     PWM6_Handler              ; 16+20: PWM6 Handler                    
                DCD     PWM7_Handler              ; 16+21: PWM7 Handler                    
                DCD     RTC_Handler               ; 16+22: RTC Handler                     
                DCD     ADC_Handler               ; 16+23: ADC Handler                     
                DCD     WZTOE_Handler             ; 16+24: WZTOE_Handler                   
                DCD     EXTI_Handler             ; 16+25: EXTI_Handler      					
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
               EXPORT  SysTick_Handler            [WEAK]
               B       .
               ENDP
Default_Handler PROC
                EXPORT SSP0_Handler               [WEAK]
                EXPORT SSP1_Handler               [WEAK]
                EXPORT UART0_Handler              [WEAK]
                EXPORT UART1_Handler              [WEAK]
                EXPORT UART2_Handler              [WEAK]
                EXPORT I2C0_Handler               [WEAK]
                EXPORT I2C1_Handler               [WEAK]
                EXPORT PORT0_Handler              [WEAK]
                EXPORT PORT1_Handler              [WEAK]
                EXPORT PORT2_Handler              [WEAK]
                EXPORT PORT3_Handler              [WEAK]
                EXPORT DMA_Handler                [WEAK]
                EXPORT DUALTIMER0_Handler         [WEAK]
                EXPORT DUALTIMER1_Handler         [WEAK]
                EXPORT PWM0_Handler               [WEAK]
                EXPORT PWM1_Handler               [WEAK]
                EXPORT PWM2_Handler               [WEAK]
                EXPORT PWM3_Handler               [WEAK]
                EXPORT PWM4_Handler               [WEAK]
                EXPORT PWM5_Handler               [WEAK]
                EXPORT PWM6_Handler               [WEAK]
                EXPORT PWM7_Handler               [WEAK]
                EXPORT RTC_Handler                [WEAK]
                EXPORT ADC_Handler                [WEAK]
                EXPORT WZTOE_Handler              [WEAK]
                EXPORT EXTI_Handler              [WEAK]					
SSP0_Handler                      
SSP1_Handler                      
UART0_Handler                     
UART1_Handler                     
UART2_Handler                     
I2C0_Handler                      
I2C1_Handler                      
PORT0_Handler                     
PORT1_Handler                     
PORT2_Handler                     
PORT3_Handler                     
DMA_Handler                       
DUALTIMER0_Handler                
DUALTIMER1_Handler                
PWM0_Handler                      
PWM1_Handler                      
PWM2_Handler                      
PWM3_Handler                      
PWM4_Handler                      
PWM5_Handler                      
PWM6_Handler                      
PWM7_Handler                      
RTC_Handler                       
ADC_Handler                       
WZTOE_Handler                
EXTI_Handler
                B       .
                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END
