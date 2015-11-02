#ifndef __MIIM_H__ 
#define __MIIM_H__
#include "W7500x_gpio.h"

#define MDIO    GPIO_Pin_15
#define MDC     GPIO_Pin_14

//#define PHY_ADDR_RLT8201 0x1F //AD[4:0] <= 0x1F (0x1F)
//#define PHY_ADDR_IP101G (phy_id())
//#define PHY_ADDR PHY_ADDR_IP101G


#define SVAL 0x2 //right shift val = 2 
#define PHYREG_CONTROL  0x0//Control Register address (Contorl basic register)
#define PHYREG_STATUS   0x1//Status Register address (Status basic register)
#define CNTL_DUPLEX     (0x01ul<< 7)
#define CNTL_AUTONEGO   (0x01ul<<11)
#define CNTL_SPEED      (0x01ul<<12)
typedef enum
{
    HalfDuplex10 = 0x0000,
    FullDuplex10 = CNTL_DUPLEX,
    AUTONEGO = CNTL_AUTONEGO,
    HalfDuplex100 = CNTL_SPEED,
    FullDuplex100 = (CNTL_SPEED|CNTL_DUPLEX)
}SetLink_Type;

#define IS_SETLINK_TYPE(Mode) (((Mode)==HalfDuplex10) || ((Mode)==FullDuplex10) || ((Mode)==AUTONEGO) || \
                               ((Mode)==HalfDuplex100) || ((Mode)==FullDuplex100))

int32_t phy_id(void);
void mdio_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_MDC, uint16_t GPIO_Pin_MDIO);
void mdio_write(GPIO_TypeDef* GPIOx, uint32_t PhyRegAddr, uint32_t val);
uint32_t mdio_read(GPIO_TypeDef* GPIOx, uint32_t PhyRegAddr);
uint32_t link(void);
void set_link(SetLink_Type mode);


#endif
