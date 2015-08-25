/**
  ******************************************************************************
  * @file    W7500x_stdPeriph_Driver/inc/W7500x_i2c.h
  * @author  IOP Team
  * @version V1.0.0
  * @date    26-AUG-2015
  * @brief   This file contains all the functions prototypes for the I2C 
  *          firmware library.
  ******************************************************************************
  *
  ******************************************************************************
  */

/*include -------------------------------------*/
#include "W7500x.h"

#ifndef __W7500X_I2C_H
#define __W7500X_I2C_H


typedef enum {
    I2C_PA_5    = 0x05,
    I2C_PA_6    = 0x06,
    I2C_PA_9    = 0x09,
    I2C_PA_10   = 0x0A,
    I2C_PC_4    = 0x24,
    I2C_PC_5    = 0x25,
    I2C_PC_8    = 0x28,
    // Not connected
    I2C_NC = (int)0xFFFFFFFF
} I2C_PinName;

typedef struct
{
    I2C_PinName scl;
    I2C_PinName sda;
}I2C_ConfigStruct;


#define I2C_PORT(X) (((uint32_t)(X) >> 4) & 0xF)    // port number (0=A, 1=B, 2=C, 3=D)
#define I2C_PIN_INDEX(X)  (1 << ((uint32_t)(X) & 0xF))    // pin index : flag bit 
 
uint32_t I2C_Init(I2C_ConfigStruct* conf);

void I2C_WriteBitSDA(I2C_ConfigStruct* conf, uint8_t data);
void I2C_WriteBitSCL(I2C_ConfigStruct* conf, uint8_t data);
uint8_t I2C_ReadBitSDA(I2C_ConfigStruct* conf);

void I2C_SendACK(I2C_ConfigStruct* conf);
void I2C_SendNACK(I2C_ConfigStruct* conf);

uint8_t I2C_WriteByte(I2C_ConfigStruct* conf, uint8_t data);
uint8_t I2C_ReadByte(I2C_ConfigStruct* conf);

void I2C_Start(I2C_ConfigStruct* conf);
void I2C_Stop(I2C_ConfigStruct* conf);

int I2C_Write(I2C_ConfigStruct* conf, uint8_t addr, uint8_t* data, uint32_t len);
int I2C_WriteRepeated(I2C_ConfigStruct* conf, uint8_t addr, uint8_t* data, uint32_t len);
int I2C_Read(I2C_ConfigStruct* conf, uint8_t addr, uint8_t* data, uint32_t len);
int I2C_ReadRepeated(I2C_ConfigStruct* conf, uint8_t addr, uint8_t* data, uint32_t len);


 #endif //__W7500X_I2C_H

