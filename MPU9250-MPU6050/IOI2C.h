#ifndef __IOI2C_H
#define __IOI2C_H
#include "stm32l0xx_hal.h"

//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))

#define SCL_H         GPIOB->BSRR = GPIO_PIN_8
#define SCL_L         GPIOB->BRR  = GPIO_PIN_8

#define SDA_H         GPIOB->BSRR = GPIO_PIN_9
#define SDA_L         GPIOB->BRR  = GPIO_PIN_9

#define SCL_read      GPIOB->IDR  & GPIO_PIN_8
#define SDA_read      GPIOB->IDR  & GPIO_PIN_9

extern void IIC_Init(void);                //初始化IIC的IO口


extern unsigned char IIC_ReadOneByte(unsigned char I2C_Addr,unsigned char addr);
extern unsigned char IICwriteByte(unsigned char dev, unsigned char reg, unsigned char data);
extern uint8_t IICwriteBytes(uint8_t dev, uint8_t reg, uint8_t length, uint8_t* data);
extern uint8_t IICwriteBit(uint8_t dev,uint8_t reg,uint8_t bitNum,uint8_t data);
extern uint8_t IICreadBytes(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t len,uint8_t *data);

extern void IIC_Analog(void);


void Delay_ms(uint32_t xms);

#endif

//------------------End of File----------------------------
