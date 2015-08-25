#ifndef _MMC_SD_H_
#define _MMC_SD_H_
#include "W7500x.h"

#define MMC_SD_SPI1_PORT		GPIOB

#define MMC_SD_SCK_PORT		MMC_SD_SPI1_PORT
#define MMC_SD_SCK_PIN				GPIO_Pin_1

#define MMC_SD_MISO_PORT		MMC_SD_SPI1_PORT
#define MMC_SD_MISO_PIN			GPIO_Pin_2

#define MMC_SD_MOSI_PORT		MMC_SD_SPI1_PORT
#define MMC_SD_MOSI_PIN			GPIO_Pin_3


#define MMC_SD_CS_PORT			GPIOB
#define MMC_SD_CS_PIN					GPIO_Pin_0

// SD data transmission whether to release the bus after the end of the macro definition
#define NO_RELEASE 0
#define RELEASE 1

// SD Card Type Definition
#define SD_TYPE_MMC 1
#define SD_TYPE_V1 2
#define SD_TYPE_V2 3
#define SD_TYPE_V2HC 4

// SD Card instruction sheet
#define CMD0 0 // Card Reset
#define CMD1 1
#define CMD9 9 // command 9, CSD data read
#define CMD10 10 // Command 10, read CID data
#define CMD12 12 // command 12, to stop data transmission
#define CMD16 16 // Command 16, set SectorSize should return 0x00
#define CMD17 17 // Command 17, read sector
#define CMD18 18 // Command 18, read Multi sector
#define ACMD23 23 // Command 23, set the multi-sector erase writing in advance of a block N
#define CMD24 24 // Command 24, write sector
#define CMD25 25 // Command 25, write Multi sector
#define ACMD41 41 // command to 41, should return 0x00
#define CMD55 55 // command to 55, should return 0x01
#define CMD58 58 // Command 58, read OCR information
#define CMD59 59 // command to 59, enables / disables the CRC, should return 0x00

// Write data to respond to the word meaning
#define MSD_DATA_OK 0x05
#define MSD_DATA_CRC_ERROR 0x0B
#define MSD_DATA_WRITE_ERROR 0x0D
#define MSD_DATA_OTHER_ERROR 0xFF

// SD card labeled word response
#define MSD_RESPONSE_NO_ERROR 0x00
#define MSD_IN_IDLE_STATE 0x01
#define MSD_ERASE_RESET 0x02
#define MSD_ILLEGAL_COMMAND 0x04
#define MSD_COM_CRC_ERROR 0x08
#define MSD_ERASE_SEQUENCE_ERROR 0x10
#define MSD_ADDRESS_ERROR 0x20
#define MSD_PARAMETER_ERROR 0x40
#define MSD_RESPONSE_FAILURE 0xFF
 
// This part should be modified depending on the connection!
// Mini STM32 uses SD cards as CS PA3 feet.
// #define SD_CS PAout (3) // SD card selection pin
/* Select MSD Card: ChipSelect pin low  */ 
#define MSD_CS_ENABLE()     GPIO_ResetBits(MMC_SD_CS_PORT, MMC_SD_CS_PIN)  

/* Deselect MSD Card: ChipSelect pin high */  
#define MSD_CS_DISABLE()     GPIO_SetBits(MMC_SD_CS_PORT, MMC_SD_CS_PIN)  

#define SPI_SPEED_2   0
#define SPI_SPEED_4   1
#define SPI_SPEED_8   2
#define SPI_SPEED_16  3
#define SPI_SPEED_256 4


extern uint8_t SD_Type; // SD card type
	
// Function state area
void bsp_set_spi1_speed_mmcsd(uint16_t prescaler);
uint8_t SD_WaitReady (void); // SD card ready to wait
uint8_t SD_SendCommand (uint8_t cmd, uint32_t arg, uint8_t crc); // SD card to send a command
uint8_t SD_SendCommand_NoDeassert (uint8_t cmd, uint32_t arg, uint8_t crc);
uint8_t SD_Init (void); // SD Card initialization
uint8_t SD_Idle_Sta (void); // set the SD card into suspend mode

uint8_t SD_ReceiveData (uint8_t * data, uint16_t len, uint8_t release); // SD card reader data
uint8_t SD_GetCID (uint8_t * cid_data); // reading SD card CID
uint8_t SD_GetCSD (uint8_t * csd_data); // reading SD card CSD
uint32_t SD_GetCapacity (void); // check SD card capacity

// USB SD card reader operation function
uint8_t MSD_WriteBuffer (uint8_t * pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite);
uint8_t MSD_ReadBuffer (uint8_t * pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);

uint8_t SD_ReadSingleBlock (uint32_t sector, uint8_t * buffer); // read a sector
uint8_t SD_WriteSingleBlock (uint32_t sector, const uint8_t * buffer); // write a sector
uint8_t SD_ReadMultiBlock (uint32_t sector, uint8_t * buffer, uint8_t count); // read multiple sector
uint8_t SD_WriteMultiBlock (uint32_t sector, const uint8_t * data, uint8_t count); // write multiple sector
uint8_t SD_Read_Bytes (unsigned long address, unsigned char * buf, unsigned int offset, unsigned int bytes); // read a byte
uint8_t SD_WaitReady(void);

extern void bsp_sd_gpio_init(void);
extern int g_mkfs_done;
extern int g_sdcard_done;

void bsp_set_spi1_speed (uint8_t speed);
uint8_t bsp_readwritebyte_spi1 (uint8_t tx_data);

#endif
