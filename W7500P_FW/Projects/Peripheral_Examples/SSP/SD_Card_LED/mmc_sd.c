
#include <stdio.h>
#include "W7500x_gpio.h"
#include "W7500x_ssp.h"
#include "mmc_sd.h"

uint8_t SD_Type = 0; // SD card type

#define SD_MEMORY_RETRY_COUNT 255//400

// 2010/5/13
// Add some delay, measured to support TF card (1G/2G), Kingston 2G, 4G 16G SD Card
// 2010/6/24
// Added uint8_t SD_GetResponse (uint8_t Response) function
// Modified uint8_t SD_WaitDataReady (void) function
// Added USB card reader support uint8_t MSD_ReadBuffer (uint8_t * pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);
// And uint8_t MSD_WriteBuffer (uint8_t * pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite); two functions

void bsp_sd_gpio_init(void)
{
  GPIO_InitTypeDef GPIO_InitDef;

  /* Configure PB_00 pin: CS pin */
  GPIO_InitDef.GPIO_Pin = MMC_SD_CS_PIN;
  GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_Init(MMC_SD_CS_PORT, &GPIO_InitDef);
  PAD_AFConfig(PAD_PB,MMC_SD_CS_PIN , PAD_AF1);
    
  /* Configure PC_08 pin: Red LED pin */
  GPIO_InitDef.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_Init(GPIOC, &GPIO_InitDef);
  PAD_AFConfig(PAD_PC,GPIO_Pin_8 , PAD_AF1);
  GPIO_SetBits(GPIOC, GPIO_Pin_8);

    /* Configure PC_09 pin: Green LED pin */
  GPIO_InitDef.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_Init(GPIOC, &GPIO_InitDef);
  PAD_AFConfig(PAD_PC,GPIO_Pin_9 , PAD_AF1);
  GPIO_SetBits(GPIOC, GPIO_Pin_9);
    
  /* Configure PC_05 pin: Blue LED pin */
  GPIO_InitDef.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_Init(GPIOC, &GPIO_InitDef);
  PAD_AFConfig(PAD_PC,GPIO_Pin_5 , PAD_AF1);
  GPIO_SetBits(GPIOC, GPIO_Pin_5);
}


// Initialize SD card
// Return if successful, it will automatically set the speed to 18Mhz SPI
// Return value: 0: NO_ERR
// 1: TIME_OUT
// 99: NO_CARD
uint8_t SD_Init (void)
{
	SSP_InitTypeDef SSP1_InitStructure;
	uint8_t r1; // return value of SD card storage
	uint16_t retry; // used to count out
	uint8_t buff[6] = {0,0,0,0,0};

	MSD_CS_DISABLE();

	/* SPI1 Config */
  SSP_StructInit(&SSP1_InitStructure);
  SSP1_InitStructure.SSP_SerialClockRate   	= 0x00;
  SSP1_InitStructure.SSP_FrameFormat       	= SSP_FrameFormat_MO; 
  SSP1_InitStructure.SSP_CPHA              				= SSP_CPHA_2Edge;//SSP_CPHA_1Edge;   
  SSP1_InitStructure.SSP_CPOL              				= SSP_CPOL_High;//SSP_CPOL_Low;
  SSP1_InitStructure.SSP_DataSize          			= SSP_DataSize_8b;
  SSP1_InitStructure.SSP_SOD               				= SSP_SOD_RESET;
  SSP1_InitStructure.SSP_Mode              				= SSP_Mode_Master;
  SSP1_InitStructure.SSP_NSS               				= SSP_NSS_Hard;
  SSP1_InitStructure.SSP_LBM               				= SSP_LBM_RESET;
  SSP1_InitStructure.SSP_SSE               				= SSP_SSE_SET;
  SSP1_InitStructure.SSP_BaudRatePrescaler = SSP_BaudRatePrescaler_254;
  SSP_Init(SSP1,&SSP1_InitStructure);

	/* SPI1 enable */
	//SPI_Cmd(SPI1, ENABLE);
	
	bsp_set_spi1_speed(SPI_SPEED_256);

	if (SD_Idle_Sta())
		return 1; 	// 1 set out to return to the idle mode failed

	//----------------- SD card is reset to the idle end of the -----------------
	// Get the SD card version
	MSD_CS_ENABLE();

	r1 = SD_SendCommand_NoDeassert (8, 0x1aa, 0x87);

	// If the version information is the v1.0 version of the card, ie r1 = 0x05, then the following initialization
	if (r1 == 0x05)
	{
		// Set the card type to SDV1.0, if the latter is detected as the MMC card, and then modified to MMC
		SD_Type = SD_TYPE_V1;
		// If the V1.0 card, CMD8 instruction did not follow-up data
		// Set chip select high end of the second order
		MSD_CS_ENABLE();

		// Multiple 8 CLK, so that the end of follow-up operation SD
		bsp_readwritebyte_spi1 (0xFF);

		//----------------- SD card, MMC card initialization -----------------
		// Initialize command CMD55 + ACMD41 Card
		// If there is response, that is the SD card, and the initialization is complete
		// No response, that is the MMC card, the corresponding additional initialization
		retry = 0;
		do
		{
			// Starting CMD55, should return 0x01; or wrong
			r1 = SD_SendCommand (CMD55, 0, 0);
			if (r1 == 0XFF) return r1; // if not 0xff, then sent to

			// Get the correct response, sent ACMD41, the return value should be 0x00, otherwise retry 200
			r1 = SD_SendCommand (ACMD41, 0, 0);

			retry++;
	    } while ((r1 != 0x00) && (retry <SD_MEMORY_RETRY_COUNT));
		
	    // Determine the correct response is the time-out or
	    // If response: is the SD card; did not respond: is the MMC card
	    //---------- MMC card for additional initialization started ------------
	    if (retry == SD_MEMORY_RETRY_COUNT)
	    {
			retry = 0;
			// Initialize command to send MMC card (not tested)
			do
			{
			    r1 = SD_SendCommand (1,0,0);
			    retry++;
			} while ((r1 != 0x00) && (retry <SD_MEMORY_RETRY_COUNT));

			if (retry == SD_MEMORY_RETRY_COUNT) return 1; // MMC card initialization timed out

			// Write card type
			SD_Type = SD_TYPE_MMC;
	    }
		
	    //---------- MMC card for additional initialization end ------------
	    // Set SPI high-speed mode
	    bsp_set_spi1_speed(SPI_SPEED_4);
	    bsp_readwritebyte_spi1 (0xFF);
		
	    // Disable CRC check
	    r1 = SD_SendCommand (CMD59, 0, 0x95);
	    if (r1 != 0x00) 
			return r1; // command error, returns r1
	    
	    // Set Sector Size
	    r1 = SD_SendCommand (CMD16, 512, 0x95);
	    if (r1 != 0x00) 
			return r1; // command error, returns r1
	    //----------------- SD card, MMC card initialization ended -----------------

	} 
	// SD Card for the V1.0 version of the initialization is complete
	
	// Here is the card initialization V2.0
	// Which need to read the OCR data, with a diagnosis or SD2.0HC Card SD2.0
	else if (r1 == 0x01)
	{
	    // V2.0 card, CMD8 command returns 4 bytes of data, and then to skip the end of the command
	    buff[0] = bsp_readwritebyte_spi1 (0xFF); // should be 0x00
	    buff[1] = bsp_readwritebyte_spi1 (0xFF); // should be 0x00
	    buff[2] = bsp_readwritebyte_spi1 (0xFF); // should be 0x01
	    buff[3] = bsp_readwritebyte_spi1 (0xFF); // should be 0xAA
	    
	    MSD_CS_DISABLE();
	    bsp_readwritebyte_spi1 (0xFF); // the next 8 clocks
	    // Determine whether the card supports a voltage range of 2.7V-3.6V
	    // If (buff [2] == 0x01 && buff [3] == 0xAA) // do not judge, let the cards to support more
	    {
			retry = 0;
			// Initialize command CMD55 + ACMD41 Card
			do
			{
				r1 = SD_SendCommand (CMD55, 0, 0);
				if (r1 != 0x01) return r1;

				r1 = SD_SendCommand (ACMD41, 0x40000000, 0);
				if (retry> SD_MEMORY_RETRY_COUNT) return r1; // timeout return status r1
			} while (r1 != 0);
			
			// Initialize command to send to complete, the next access to OCR information
			// SD2.0 card identification since version 
			//----------- -----------
			r1 = SD_SendCommand_NoDeassert (CMD58, 0, 0);
			if (r1 != 0x00)
			{
				MSD_CS_DISABLE(); // release chip select signal SD
				return r1; // If the command does not return the correct response, direct withdrawal, return response
			} // Read OCR command is issued, followed by 4 bytes of OCR information

			buff [0] = bsp_readwritebyte_spi1 (0xFF);
			buff [1] = bsp_readwritebyte_spi1 (0xFF);
			buff [2] = bsp_readwritebyte_spi1 (0xFF);
			buff [3] = bsp_readwritebyte_spi1 (0xFF);

			// OCR to receive complete set of high chip select
			MSD_CS_DISABLE();
			bsp_readwritebyte_spi1 (0xFF);

			// Check the received OCR in bit30-bit (CCS), was identified as SD2.0 SDHC
			// If the CCS = 1: SDHC CCS = 0: SD2.0
			if (buff [0] & 0x40) 
				SD_Type = SD_TYPE_V2HC; // Check the CCS
			else 
				SD_Type = SD_TYPE_V2;
			//----------- Identification card version of SD2.0 end -----------
			// Set SPI high-speed mode
			bsp_set_spi1_speed(SPI_SPEED_4);
	    }
	}
	return r1;
	
}

// Wait for response to SD card
// Response: to get the feedback value
// Return value: 0, success has been the value of the response
// Otherwise, get the value of failure to respond
uint8_t SD_GetResponse (uint8_t Response)
{
	uint16_t Count = 0xFFF; // wait times

	while ((bsp_readwritebyte_spi1 (0XFF) != Response) && Count) 
		Count--; // waiting to get an accurate response

	if (Count == 0) 
		return MSD_RESPONSE_FAILURE; // get a response failure
	else 
		return MSD_RESPONSE_NO_ERROR; // correct response
}

// Wait for write to complete the SD card
// Return value: 0 success;
// Other, error codes;
uint8_t SD_WaitDataReady (void)
{
	uint8_t r1 = MSD_DATA_OTHER_ERROR;
	uint32_t retry;
	retry = 0;
	do
	{
       	 r1 = bsp_readwritebyte_spi1 (0xFF) &0X1F; // read response
       	 
        	if (retry == 0xfffe) 
			return 1;
			
		retry++;
		
		switch (r1)
		{
		case MSD_DATA_OK: // correct the data reception
			r1 = MSD_DATA_OK;
			break;
		case MSD_DATA_CRC_ERROR: // CRC checksum error
			return MSD_DATA_CRC_ERROR;
		case MSD_DATA_WRITE_ERROR: // Data write error
			return MSD_DATA_WRITE_ERROR;
		default: // Unknown error
			r1 = MSD_DATA_OTHER_ERROR;
		break;
		}
	} while (r1 == MSD_DATA_OTHER_ERROR); // data errors have been waiting for
	
	retry = 0;
	while (bsp_readwritebyte_spi1 (0XFF) == 0) // read data to 0, the data has not yet completed writing
	{
		retry++;
		
		// Delay_us (10); // SD card write takes a long time to wait
		if (retry >= 0XFFFFFFFE) 
			return 0XFF; // Wait failed
	};
	return 0; // success
}


// Send a command to the SD card
// Input: uint8_t cmd command
// uint32_t arg command arguments
// uint8_t crc crc checksum
// Return value: SD card, the response returned
uint8_t SD_SendCommand (uint8_t cmd, uint32_t arg, uint8_t crc)
{
	uint8_t r1;
	uint16_t Retry = 0;

	// Close the chip select
	MSD_CS_DISABLE();
	
	bsp_readwritebyte_spi1 (0xff); // high-speed write command delay
	bsp_readwritebyte_spi1 (0xff);
	bsp_readwritebyte_spi1 (0xff);
	
	// Chip select low-end set, select the SD card
	MSD_CS_ENABLE();
	
	// Send
	bsp_readwritebyte_spi1 (cmd | 0x40); // write command, respectively,
	bsp_readwritebyte_spi1 (arg>> 24);
	bsp_readwritebyte_spi1 (arg>> 16);
	bsp_readwritebyte_spi1 (arg>> 8);
	bsp_readwritebyte_spi1 (arg);
	bsp_readwritebyte_spi1 (crc);
	
	// Wait for a response, or time-out exit
	while ((r1 = bsp_readwritebyte_spi1 (0xFF)) == 0xFF)
	{
		Retry++;
		if (Retry> SD_MEMORY_RETRY_COUNT) 
			break;
	}
	
	// Close the chip select
	MSD_CS_DISABLE();
	
	// Additional 8 on the bus clock, so that SD card to complete the remaining work
	bsp_readwritebyte_spi1 (0xFF);
	
	// Return status values
	return r1;
	
}

// Send a command to the SD card (the end is yet to chip select, there came the follow-up data)
// Input: uint8_t cmd command
// uint32_t arg command arguments
// uint8_t crc crc checksum
// Return value: SD card, the response returned
uint8_t SD_SendCommand_NoDeassert (uint8_t cmd, uint32_t arg, uint8_t crc)
{
	uint16_t Retry = 0;
	uint8_t r1;
	
	bsp_readwritebyte_spi1 (0xff); // high-speed write command delay
	bsp_readwritebyte_spi1 (0xff);

	// chip select low-end set, select the SD card
	MSD_CS_ENABLE(); 
	
	// Send
	bsp_readwritebyte_spi1 (cmd | 0x40); // write command, respectively,
	bsp_readwritebyte_spi1 (arg>> 24);
	bsp_readwritebyte_spi1 (arg>> 16);
	bsp_readwritebyte_spi1 (arg>> 8);
	bsp_readwritebyte_spi1 (arg);
	bsp_readwritebyte_spi1 (crc);
	
	// Wait for a response, or time-out exit
	while ((r1 = bsp_readwritebyte_spi1 (0xFF)) == 0xFF)
	{
	    Retry++;
	    if (Retry> SD_MEMORY_RETRY_COUNT) 
			break;
	}
	
	// Return the response value
	return r1;
}

// Set the SD card into suspend mode
// Return value: 0, successfully set
// 1, setup failed
uint8_t SD_Idle_Sta (void)
{
	uint16_t i;
	uint8_t r1=0;
	uint16_t retry;

	for (i = 0; i <0xf00; i++);// pure delay, waiting for complete power-SD card

	// Should generate> 74 pulses, so that SD card to complete their initialization
	for (i = 0; i <10; i++) bsp_readwritebyte_spi1 (0xFF);

	//----------------- SD card is reset to the idle start -----------------
	// Loop continuously sending CMD0, until the SD card back 0x01, enter the IDLE state
	// Timeout then exit
	retry = 0;
	do
	{
		// Send CMD0, so that SD card into the IDLE state
		r1 = SD_SendCommand (CMD0, 0, 0x95);
		retry++;
	} while ((r1 != 0x01) && (retry <SD_MEMORY_RETRY_COUNT));

	// Exit the loop, check reason: Initialization successful? or try out?
	if (retry == SD_MEMORY_RETRY_COUNT) return 1; // fail

	return 0; // success
}


// Read back from the SD card in the specified length of data placed in a given position
// Input: uint8_t * data (read back the data storage memory> len)
// uint16_t len (data length)
// uint8_t release (whether to release the bus after transfer CS is set high 0: do not release 1: Release)
// Return value: 0: NO_ERR
// Other: Error Message
uint8_t SD_ReceiveData (uint8_t * data, uint16_t len, uint8_t release)
{
	// Start the first transfer
	MSD_CS_ENABLE();
	if (SD_GetResponse (0xFE)) // wait for data sent back to the starting SD card token 0xFE
	{
		MSD_CS_DISABLE();
		return 1;
	}
	
	while (len--) // Start receiving data
	{
		*data = bsp_readwritebyte_spi1 (0xFF);
		data++;
	}
	
	// Here are two pseudo-CRC (dummy CRC)
	bsp_readwritebyte_spi1 (0xFF);
	bsp_readwritebyte_spi1 (0xFF);
	if (release == RELEASE) // demand the release of the bus, the CS is set high
	{
		MSD_CS_DISABLE(); // end of transmission
		bsp_readwritebyte_spi1 (0xFF);
	}
	return 0;
}

// Get the SD card CID information, including manufacturer information
// Input: uint8_t * cid_data (CID stored in the memory, at least 16Byte)
// Return value: 0: NO_ERR
// 1: TIME_OUT
// Other: Error Message
uint8_t SD_GetCID (uint8_t * cid_data)
{
	uint8_t r1;
	
	// Send CMD10 command, read CID
	r1 = SD_SendCommand(CMD10,0,0xff);
	
	if (r1 != 0x00) 
		return r1; // do not return the correct answer, then exit, error
		
	SD_ReceiveData (cid_data, 16, RELEASE); // 16 bytes of data received
	return 0;
}

// Get the SD card, CSD, including the capacity and speed of information
// Input: uint8_t * cid_data (CID stored in the memory, at least 16Byte)
// Return value: 0: NO_ERR
// 1: TIME_OUT
// Other: Error Message
uint8_t SD_GetCSD (uint8_t *csd_data)
{
	uint8_t r1;
	
	r1 = SD_SendCommand(CMD9, 0, 0xff); // send CMD9 command, read CSD
	
	if (r1) 
		return r1; // do not return the correct answer, then exit, error
		
	SD_ReceiveData (csd_data, 16, RELEASE); // 16 bytes of data received
	
	return 0;
}

// Get the SD card capacity (bytes)
// Return value: 0: take capacity error
// Other: SD card capacity (bytes)
uint32_t SD_GetCapacity (void)
{
	uint8_t csd [16];
	uint32_t Capacity;
	uint8_t r1;
	uint16_t i;
	uint16_t temp;
	// Get CSD information, if during the error, return 0
	if (SD_GetCSD (csd) != 0) return 0;
	
	// If the SDHC card, calculated in accordance with the following
	if ((csd [0] & 0xC0) == 0x40)
	{
		Capacity = ((uint32_t) csd [8]) <<8;
		Capacity += (uint32_t) csd [9] +1;
		Capacity = (Capacity) * 1024; // get number of sectors
		Capacity *= 512; // get number of bytes
	}
	else
	{
		//int j;

		//for(j=0;j<16;j++)
		//	usart1_transmit_string_format("%x\r\n", csd[j]);
	
		i = csd [6] &0x03;
		//usart1_transmit_string_format("\r\ni=%x", i);
		i <<= 8;
		//usart1_transmit_string_format("\r\ni=%x", i);
		i += csd [7];
		//usart1_transmit_string_format("\r\ni=%x", i);
		i <<= 2;
		//usart1_transmit_string_format("\r\ni=%x", i);
		i += ((csd [8] & 0xc0)>> 6);
		//usart1_transmit_string_format("\r\ni=%x", i);
		
		// C_SIZE_MULT
		r1 = csd [9] &0x03;
		r1 <<= 1;
		r1 += ((csd [10] & 0x80)>> 7);
		r1 += 2; // BLOCKNR
		temp = 1;
		
		while (r1)
		{
			temp *= 2;
			r1--;
		}
		
		Capacity = ((uint32_t) (i +1 ))*(( uint32_t) temp);

		//usart1_transmit_string_format("\r\ntemp=%d,  Capacity=%d, i=%d\r\n", temp, Capacity, i);
		
		// READ_BL_LEN
		i = csd [5] &0x0f;
		
		// BLOCK_LEN
		temp = 1;
		
		while (i)
		{
			temp *= 2;
			i--;
		}

		//usart1_transmit_string_format("\r\\ntemp=%d,  Capacity=%d Bytes\r\n", temp, Capacity);
		
		// The final result
		Capacity *= (uint32_t) temp; // in bytes
	}
	return (uint32_t) Capacity;
}

// Read a block SD card
// Input: uint32_t sector to take the address (sector value, non-physical address)
// uint8_t * buffer data storage location (size at least 512byte)
// Return value: 0: Success
// Other: failure
uint8_t SD_ReadSingleBlock (uint32_t sector, uint8_t * buffer)
{
	uint8_t r1;
	
	// Set to high-speed mode
	// bsp_set_spi1_speed(SPI_SPEED_4);
	
	// If it is not SDHC, given that the sector address, convert it into a byte address
	if (SD_Type != SD_TYPE_V2HC)
	{
	    sector = sector <<9;
	}
	
	r1 = SD_SendCommand (CMD17, sector, 0); // read command
	
	if (r1 != 0x00) return r1;
	
	r1 = SD_ReceiveData (buffer, 512, RELEASE);
	if (r1 != 0) 
		return r1; // read data error!
	else 
		return 0;
}
//////////////////////////// Function of the following two required 
/////////// USB reader //////////////
// Define block size SD card
#define BLOCK_SIZE 512

// Write MSD / SD data
// PBuffer: Data Storage
// ReadAddr: writing the first address
// NumByteToRead: number of bytes to write
// Return value: 0, write to complete
// Otherwise, write failure
uint8_t MSD_WriteBuffer (uint8_t * pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite)
{
	uint32_t i, NbrOfBlock = 0, Offset = 0;
	uint32_t sector;
	uint8_t r1;
	
	NbrOfBlock = NumByteToWrite / BLOCK_SIZE; // get the number of blocks to be written
	MSD_CS_ENABLE();
	
	while (NbrOfBlock--) // write a sector
	{
		sector = WriteAddr + Offset;
		if (SD_Type == SD_TYPE_V2HC) sector >>= 9; // perform the reverse operation and common action
		
		r1 = SD_SendCommand_NoDeassert (CMD24, sector, 0xff); // write command
		if (r1)
		{
			MSD_CS_DISABLE();
			return 1; // response is not correct, a direct return
		}
		
		bsp_readwritebyte_spi1 (0xFE); // put initial token 0xFE
		
		// Put data in a sector
		for (i = 0; i <512; i++) 
			bsp_readwritebyte_spi1 (*pBuffer++);
		
		// Send the dummy CRC Byte 2
		bsp_readwritebyte_spi1 (0xff);
		bsp_readwritebyte_spi1 (0xff);
		
		if (SD_WaitDataReady ())// SD card data is written to wait for the completion
		{
			MSD_CS_DISABLE();
			return 2;
		}
		
		Offset += 512;
	}
	
	// Write completed, set to 1 chip select	
	MSD_CS_DISABLE();
	bsp_readwritebyte_spi1 (0xff);
	
	return 0;
	
}
// Read the MSD / SD data
// PBuffer: Data Storage
// ReadAddr: Read the first address
// NumByteToRead: number of bytes to read
// Return value: 0, read out the complete
// Others, read failure
uint8_t MSD_ReadBuffer (uint8_t * pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
{
	uint32_t NbrOfBlock = 0, Offset = 0;
	uint32_t sector = 0;
	uint8_t r1 = 0;
	
	NbrOfBlock = NumByteToRead / BLOCK_SIZE;
	
	MSD_CS_ENABLE();
	
	while (NbrOfBlock--)
	{
		sector = ReadAddr + Offset;
		if (SD_Type == SD_TYPE_V2HC) 
			sector >>= 9; // perform the reverse operation and common action
			
		r1 = SD_SendCommand_NoDeassert (CMD17, sector, 0xff); // read command
		if (r1) // command to send an error
		{
			MSD_CS_DISABLE();
			return r1;
		}
		
		r1 = SD_ReceiveData (pBuffer, 512, RELEASE);
		if (r1) // reading error
		{
			MSD_CS_DISABLE();
			return r1;
		}
		
		pBuffer += 512;
		Offset += 512;
	}
	
	MSD_CS_DISABLE();
	bsp_readwritebyte_spi1 (0xff);
	
	return 0;
}
//////////////////////////////////////////////////////////////////////////
// Write SD card, a block (not actually tested)
// Input: uint32_t sector sector address (sector value, non-physical address)
// uint8_t * buffer data storage location (size at least 512byte)
// Return value: 0: Success
// Other: failure
uint8_t SD_WriteSingleBlock (uint32_t sector, const uint8_t * data)
{
	uint8_t r1;
	uint16_t i;
	uint16_t retry;

	// Set to high-speed mode
	// SPIx_SetSpeed(SPI_SPEED_HIGH);
	
	// If it is not SDHC, given that the sector address, convert it into a byte address
	if (SD_Type != SD_TYPE_V2HC)
	{
		sector = sector <<9;
	}
	
	r1 = SD_SendCommand (CMD24, sector, 0x00);
	if (r1 != 0x00)
	{
		return r1; // response is not correct, a direct return
	}

	// Start preparing data
	MSD_CS_ENABLE();
	// First put three empty data, SD card ready to wait
	bsp_readwritebyte_spi1 (0xff);
	bsp_readwritebyte_spi1 (0xff);
	bsp_readwritebyte_spi1 (0xff);
	// Put initial token 0xFE
	bsp_readwritebyte_spi1 (0xFE);

	// Put data in a sector
	for (i = 0; i <512; i++)
	{
		bsp_readwritebyte_spi1 (* data++);
	}
	
	// Send a dummy CRC Byte 2
	bsp_readwritebyte_spi1 (0xff);
	bsp_readwritebyte_spi1 (0xff);

	// Wait for answer SD Card
	r1 = bsp_readwritebyte_spi1 (0xff);
	if ((r1 & 0x1F) != 0x05)
	{
	    MSD_CS_DISABLE();
	    return r1;
	}

	// Wait operation is completed
	retry = 0;
	while ( !bsp_readwritebyte_spi1 (0xff))
	{
	    retry++;
	    if (retry> 0xfffe) // if not done for a long time to write, error exit
	    {
	        MSD_CS_DISABLE();
	        return 1; // write timeout return 1
	    }
	}
	// Write completed, set to 1 chip select
	MSD_CS_DISABLE();
	bsp_readwritebyte_spi1 (0xff);

	return 0;
}

// Read more than one SD card block (actually tested)
// Input: uint32_t sector sector address (sector value, non-physical address)
// uint8_t * buffer data storage location (size at least 512byte)
// uint8_t count one continuous block read count
// Return value: 0: Success
// Other: failure
uint8_t SD_ReadMultiBlock (uint32_t sector, uint8_t * buffer, uint8_t count)
{
    uint8_t r1;
	
	// SPIx_SetSpeed(SPI_SPEED_HIGH); // set to high-speed mode
	
	// If it is not SDHC, the sector addresses turn into a byte address
	if (SD_Type != SD_TYPE_V2HC) 
		sector = sector <<9;

	// SD_WaitDataReady ();
	// Read multi-block commands issued
	r1 = SD_SendCommand (CMD18, sector, 0); // read command
	if (r1 != 0x00) return r1;
	
	do // Start receiving data
	{
	    if (SD_ReceiveData (buffer, 512, NO_RELEASE) != 0x00) break;
	    buffer += 512;
	} while (--count);
	
	// All the transmission is completed, send the stop command
	SD_SendCommand (CMD12, 0, 0);
	
	// Release bus
	MSD_CS_DISABLE();
	bsp_readwritebyte_spi1 (0xFF);
	
	if (count != 0) 
		return count; // end if not passed, return the remaining number of
	else 
		return 0;
	
}
// Write SD card, N-block (not actually tested)
// Input: uint32_t sector sector address (sector value, non-physical address)
// uint8_t * buffer data storage location (size at least 512byte)
// uint8_t count the number of write block
// Return value: 0: Success
// Other: failure
uint8_t SD_WriteMultiBlock (uint32_t sector, const uint8_t * data, uint8_t count)
{
	uint8_t r1;
	uint16_t i;

	// SPIx_SetSpeed (SPI_SPEED_HIGH); // set to high-speed mode
	
	if (SD_Type != SD_TYPE_V2HC) 
		sector = sector <<9; // If it is not SDHC, given that the sector address, convert it to byte address
	if (SD_Type != SD_TYPE_MMC) 
		r1 = SD_SendCommand (ACMD23, count, 0x00); // If the target card is not the MMC card, enable the command to enable pre-erase ACMD23
		
	r1 = SD_SendCommand (CMD25, sector, 0x00); // send multi-block write command
	if (r1 != 0x00) 
		return r1; // response is not correct, a direct return
		
	MSD_CS_ENABLE(); // start preparing data
	
	bsp_readwritebyte_spi1 (0xff); // first put three empty data, SD card ready to wait
	bsp_readwritebyte_spi1 (0xff);
	//-------- The following is written by N-loop part of the sector
	
	do
	{
		// Put the start token that is a multi-block write 0xFC
		bsp_readwritebyte_spi1 (0xFC);
		// Put data in a sector
		for (i = 0; i <512; i++)
		{
			bsp_readwritebyte_spi1 (* data++);
		}
		// Send a dummy CRC Byte 2
		bsp_readwritebyte_spi1 (0xff);
		bsp_readwritebyte_spi1 (0xff);

		// Wait for answer SD Card
		r1 = bsp_readwritebyte_spi1 (0xff);
		if ((r1 & 0x1F) != 0x05)
		{
			MSD_CS_DISABLE(); // If the response is an error, then exit with error code
			return r1;
		}
		// Wait for write to complete the SD card
		if (SD_WaitDataReady () == 1)
		{
			MSD_CS_DISABLE(); // wait for write to complete the SD card out, exit error
			return 1;
		}
	} while (--count); // completion of the sector data transfer
	
	// Send end of the transmission token 0xFD
	r1 = bsp_readwritebyte_spi1 (0xFD);
	if (r1 == 0x00)
	{
		count = 0xfe;
	}
	
	if (SD_WaitDataReady ()) // wait for ready
	{
		MSD_CS_DISABLE();
		return 1;
	}
	// Write completed, set to 1 chip select
	MSD_CS_DISABLE();
	bsp_readwritebyte_spi1 (0xff);
	
	return count; // return count value, if finished then count = 0, otherwise, count = 1
	
}
// In the specified sector, began to read out bytes from the offset byte
// Input: uint32_t sector sector address (sector value, non-physical address)
// uint8_t * buf data storage addresses (size <= 512byte)
// uint16_t offset offset inside the sector
// uint16_t bytes number of bytes to read
// Return value: 0: Success
// Other: failure
uint8_t SD_Read_Bytes (unsigned long address, unsigned char * buf, unsigned int offset, unsigned int bytes)
{
	uint8_t r1; uint16_t i = 0;
	r1 = SD_SendCommand (CMD17, address <<9,0); // send the Read Sector command
	
	if (r1) 
		return r1; // response is not correct, a direct return
		
	MSD_CS_ENABLE(); // select the SD card
	
	if (SD_GetResponse (0xFE)) // wait for data sent back to the starting SD card token 0xFE
	{
		MSD_CS_DISABLE(); // close the SD card
		return 1; // read failure
	}
	
	for (i = 0; i <offset; i++) bsp_readwritebyte_spi1 (0xff); // skip the offset bits
	for (; i <offset + bytes; i++) * buf++= bsp_readwritebyte_spi1 (0xff); // read the useful data
	for (; i <512; i++) bsp_readwritebyte_spi1 (0xff); // read the remaining bytes
	
	bsp_readwritebyte_spi1 (0xff); // send the pseudo-code CRC
	bsp_readwritebyte_spi1 (0xff);
	
	MSD_CS_DISABLE(); // close the SD card
	
	return 0;
}

uint8_t SD_WaitReady(void)
{
    uint8_t r1;
    uint16_t retry;
    retry = 0;
    do
    {
        r1 = bsp_readwritebyte_spi1(0xFF);
        if(retry==0xfffe)
        {
            return 1;
        }
    }while(r1!=0xFF);

    return 0;
}

void bsp_set_spi1_speed (uint8_t speed)
{
	SSP1->CR1 &= 0XFFC7; // Fsck = Fcpu/256
	switch (speed)
	{
		case SPI_SPEED_2: // Second division
			SSP1->CR1 |= 0<<3; // Fsck = Fpclk / 2 = 36Mhz
			break;
		case SPI_SPEED_4: // four-band
			SSP1-> CR1 |= 1<<3; // Fsck = Fpclk / 4 = 18Mhz
			break;
		case SPI_SPEED_8: // eighth of the frequency
			SSP1-> CR1 |= 2<<3; // Fsck = Fpclk / 8 = 9Mhz
			break;
		case SPI_SPEED_16: // sixteen frequency
			SSP1-> CR1 |= 3<<3; // Fsck = Fpclk/16 = 4.5Mhz
			break;
		case SPI_SPEED_256: // 256 frequency division
			SSP1-> CR1 |= 7<<3; // Fsck = Fpclk/16 = 281.25Khz
			break;
	}
	
	SSP1->CR1 |= 1<<6; // SPI devices enable
	
}

uint8_t bsp_readwritebyte_spi1 (uint8_t tx_data)
{
	uint16_t retry=0;
	
	/* Loop while DR register in not emplty */
	while (SSP_GetFlagStatus (SSP1, SSP_FLAG_TNF) == RESET)
	{
		retry++;
		if(retry>400)
			return 0;
	}

	/* Send byte through the SPI1 peripheral */
	SSP_SendData (SSP1, tx_data);

	retry=0;

	/* Wait to receive a byte */
	while (SSP_GetFlagStatus (SSP1, SSP_FLAG_RNE) == RESET)
	{
		retry++;
		
		if(retry>400)
			return 0;
	}		

	/* Return the byte read from the SPI bus */
	return SSP_ReceiveData (SSP1);
}

