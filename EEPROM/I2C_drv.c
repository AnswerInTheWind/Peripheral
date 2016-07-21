#define _I2C_DRV_C_

#include "stm32f10x.h"

#include "I2c_drv.h"


extern void Delay(__IO uint32_t nTime);

#define SCL_H()           GPIOA->BSRR = GPIO_Pin_11
#define SCL_L()           GPIOA->BRR  = GPIO_Pin_11
#define SDA_H()           GPIOA->BSRR = GPIO_Pin_10
#define SDA_L()           GPIOA->BRR  = GPIO_Pin_10
#define SCL_read         (GPIOA->IDR  & GPIO_Pin_11)
#define SDA_read         (GPIOA->IDR  & GPIO_Pin_10)


/************************************************************
				Function Definition Setction
*************************************************************/
void I2C_Delay(void)
{
//    uint32_t i = 40; //减慢EEPROM 速度 FisherYu 以前是10
//
//    while(i)
//    {
//        i--;
//    }
  TIM_SetCounter(TIM1, 0);
  while(4 > TIM_GetCounter(TIM1))
  {
  };
}

void I2C_DrvInit(void)
{    
    SCL_H();
    SDA_H();
    I2C_Delay();
}


void I2Cm_Start(void)
{
    SDA_H();
    SCL_H();
    I2C_Delay();
    SDA_L();
    I2C_Delay();
}

void I2Cm_Stop(void)
{
    SCL_L();
    I2C_Delay();
    SDA_L();
    I2C_Delay();
    SCL_H();
    I2C_Delay();
    SDA_H();
    I2C_Delay();
}

void I2Cm_Ack(void)
{
    SCL_L();
    I2C_Delay();
    SDA_L();
    I2C_Delay();
    SCL_H();
    I2C_Delay();
    SCL_L();
    I2C_Delay();
}

void I2Cm_nAck(void)
{
    SCL_L();
    I2C_Delay();
    SDA_H();
    I2C_Delay();
    SCL_H();
    I2C_Delay();
    SCL_L();
    I2C_Delay();
}

void I2Cm_WaitAck(void)
{
    SCL_L();
    I2C_Delay();
    SDA_H();
    I2C_Delay();
    SCL_H();
    I2C_Delay();

    if(SDA_read != RESET)
    {
        SCL_L();
        I2C_Delay();
        return;
    }

    SCL_L();
    I2C_Delay();
}

void I2Cm_TxData(uint8_t i2c_data)
{
    uint8_t i = 8;

    while(i--)
    {
        SCL_L();
        I2C_Delay();

      if(i2c_data&0x80)
        SDA_H();
      else
        SDA_L();

        i2c_data<<=1;
        I2C_Delay();
        SCL_H();
        I2C_Delay();
    }

    SCL_L();
    I2C_Delay();
}

uint8_t I2Cm_RxData(void)
{
    uint8_t i = 8;
    uint8_t ReceiveByte = 0;

    SDA_H();

    while(i--)
    {
        ReceiveByte<<=1;
        SCL_L();
        I2C_Delay();
        SCL_H();
        I2C_Delay();

        if(SDA_read != RESET)
        {
            ReceiveByte|=0x01;
        }
    }

    SCL_L();
    I2C_Delay();

    return ReceiveByte;
}



void I2C_WriteReg(uint8_t* Data, uint8_t I2C_Addr, uint8_t I2C_Reg, uint8_t Num)
{
    uint8_t i;
    I2Cm_Start();
    I2Cm_TxData(I2C_Addr);
    I2Cm_WaitAck();
    I2Cm_TxData(I2C_Reg);
    I2Cm_WaitAck();

    for(i=0; i<Num; i++)
    {
        I2Cm_TxData(Data[i]);
        I2Cm_WaitAck();
    }

    I2Cm_Stop();
}

void I2C_ReadReg(uint8_t* Data, uint8_t I2C_Addr, uint8_t I2C_Reg, uint8_t Num)
{
    uint8_t i;
    I2Cm_Start();
    I2Cm_TxData(I2C_Addr);
    I2Cm_WaitAck();
    I2Cm_TxData(I2C_Reg);
    I2Cm_WaitAck();
    I2Cm_Start();
    I2Cm_TxData(I2C_Addr | 0x01);
    I2Cm_WaitAck();

    Data[0] = I2Cm_RxData();

    for(i=1; i<Num; i++)
    {
        I2Cm_Ack();
        Data[i] = I2Cm_RxData();
    }

    I2Cm_nAck();

    I2Cm_Stop();
}


 
