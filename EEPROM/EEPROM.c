#define _EEPROM_C_


#include "stm32f10x.h"

#include "I2c_drv.h"

#include "main.h"

#include "EEPROM.h"

#define GPIO_I2C_WP      GPIOA
#define GPIO_PIN_I2C_WP  GPIO_Pin_12


void EEPROM_Read_Config(void)
{
    I2C_ReadReg(EEPROM_Data, 0xA0, 0x00, 32);
}

void EEPROM_Write_Config(void)
{
    uint8_t i;

    GPIO_WriteBit(GPIO_I2C_WP, GPIO_PIN_I2C_WP, Bit_RESET);

    for(i=0; i<4; i++)
    {
        I2C_WriteReg(EEPROM_Data+i*8, 0xA0, 0x00+i*8, 8);  // write page 8Byte
        SysDelay(40000); 
    }

    GPIO_WriteBit(GPIO_I2C_WP, GPIO_PIN_I2C_WP, Bit_SET);
}







