#ifndef __IOI2C_H
#define __IOI2C_H
#include "stm32l0xx_hal.h"

//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))  

////IO口地址映射
//#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
//#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
//#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
//#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
//#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
//#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
//#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

//#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
//#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
//#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
//#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
//#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
//#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
//#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 

//#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
//#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

//#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
//#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 
   	   		   
//////IO方向设置
//#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0x80000000;}
//#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0x30000000;}


//IO操作函数	 
//#define (IIC_SCL=1)    GPIOB->BSRR = GPIO_PIN_8;//PBout(6) //SCL
//#define IIC_SDA=1    GPIOB->BSRR = GPIO_PIN_9;//PBout(7) //SDA	 
//#define READ_SDA   GPIOB->IDR  & GPIO_PIN_9;//PBin(7)  //输入SDA 

#define SCL_H         GPIOB->BSRR = GPIO_PIN_8
#define SCL_L         GPIOB->BRR  = GPIO_PIN_8 
   
#define SDA_H         GPIOB->BSRR = GPIO_PIN_9
#define SDA_L         GPIOB->BRR  = GPIO_PIN_9

#define SCL_read      GPIOB->IDR  & GPIO_PIN_8
#define SDA_read      GPIOB->IDR  & GPIO_PIN_9

//IIC所有操作函数
extern void IIC_Init(void);                //初始化IIC的IO口				 
extern uint8_t IIC_Start(void);				//发送IIC开始信号 
extern void IIC_Stop(void);	  			//发送IIC停止信号
extern void IIC_Send_Byte(uin8_t txd);			//IIC发送一个字节
extern uint8_t IIC_Read_Byte(void);//IIC读取一个字节
extern uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信号
extern void IIC_Ack(void);					//IIC发送ACK信号
extern void IIC_NAck(void);				//IIC不发送ACK信号

extern void IIC_Write_One_Byte(uin8_t daddr,uin8_t addr,uin8_t data);
extern uin8_t IIC_Read_One_Byte(uin8_t daddr,uin8_t addr);	 
extern unsigned char I2C_Readkey(unsigned char I2C_Addr);

extern unsigned char I2C_ReadOneByte(unsigned char I2C_Addr,unsigned char addr);
extern unsigned char IICwriteByte(unsigned char dev, unsigned char reg, unsigned char data);
extern uin8_t IICwriteBytes(uin8_t dev, uin8_t reg, uin8_t length, uin8_t* data);
extern uin8_t IICwriteBits(uin8_t dev,uin8_t reg,uin8_t bitStart,uin8_t length,uin8_t data);
extern uin8_t IICwriteBit(uin8_t dev,uin8_t reg,uin8_t bitNum,uin8_t data);
extern uint8_t IICreadBytes(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t len,uint8_t *data);

extern void IIC_Analog(void);

#endif

//------------------End of File----------------------------
