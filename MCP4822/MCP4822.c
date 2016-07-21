#define _MCP4822_C_

#include "stm32f10x.h"

#include "MCP4822.h"
#include "main.h"
#include "stdlib.h"
#define EN_LDAC  0

#if EN_LDAC

#define  GPIO_MCP4822_LDAC   GPIOC
#define  GPIO_Pin_MCP4822_LDAC  GPIO_Pin_1

#endif

//16片MCP4822
/*********************************************************************************************
对16个MCP4822的CS脚进行宏定义
*********************************************************************************************/
#define  GPIO_MCP4822_CE1       GPIOA
#define  GPIO_Pin_MCP4822_CE1   GPIO_Pin_9

#define  GPIO_MCP4822_CE2       GPIOA
#define  GPIO_Pin_MCP4822_CE2   GPIO_Pin_15

#define  GPIO_MCP4822_CE3       GPIOC
#define  GPIO_Pin_MCP4822_CE3   GPIO_Pin_10

#define  GPIO_MCP4822_CE4       GPIOC
#define  GPIO_Pin_MCP4822_CE4   GPIO_Pin_11

#define  GPIO_MCP4822_CE5       GPIOC
#define  GPIO_Pin_MCP4822_CE5   GPIO_Pin_12

#define  GPIO_MCP4822_CE6       GPIOD
#define  GPIO_Pin_MCP4822_CE6   GPIO_Pin_2

#define  GPIO_MCP4822_CE7       GPIOB
#define  GPIO_Pin_MCP4822_CE7   GPIO_Pin_4

#define  GPIO_MCP4822_CE8       GPIOB
#define  GPIO_Pin_MCP4822_CE8   GPIO_Pin_5

#define  GPIO_MCP4822_CE9       GPIOB
#define  GPIO_Pin_MCP4822_CE9   GPIO_Pin_6

#define  GPIO_MCP4822_CE10      GPIOB
#define  GPIO_Pin_MCP4822_CE10  GPIO_Pin_7

#define  GPIO_MCP4822_CE11      GPIOB
#define  GPIO_Pin_MCP4822_CE11  GPIO_Pin_8

#define  GPIO_MCP4822_CE12      GPIOB
#define  GPIO_Pin_MCP4822_CE12  GPIO_Pin_9

#define  GPIO_MCP4822_CE13      GPIOC
#define  GPIO_Pin_MCP4822_CE13  GPIO_Pin_0

#define  GPIO_MCP4822_CE14      GPIOC
#define  GPIO_Pin_MCP4822_CE14  GPIO_Pin_1

#define  GPIO_MCP4822_CE15      GPIOC
#define  GPIO_Pin_MCP4822_CE15  GPIO_Pin_2

#define  GPIO_MCP4822_CE16      GPIOC
#define  GPIO_Pin_MCP4822_CE16  GPIO_Pin_3

GPIO_TypeDef* MCP4822_CS_PORT[16] = {GPIO_MCP4822_CE1, GPIO_MCP4822_CE2, GPIO_MCP4822_CE3, GPIO_MCP4822_CE4,
                                     GPIO_MCP4822_CE5, GPIO_MCP4822_CE6, GPIO_MCP4822_CE7, GPIO_MCP4822_CE8,
                                     GPIO_MCP4822_CE9, GPIO_MCP4822_CE10, GPIO_MCP4822_CE11, GPIO_MCP4822_CE12,
                                     GPIO_MCP4822_CE13, GPIO_MCP4822_CE14, GPIO_MCP4822_CE15, GPIO_MCP4822_CE16}; 

const uint16_t MCP4822_CS_PIN[16] = {GPIO_Pin_MCP4822_CE1, GPIO_Pin_MCP4822_CE2, GPIO_Pin_MCP4822_CE3, GPIO_Pin_MCP4822_CE4,
                                     GPIO_Pin_MCP4822_CE5, GPIO_Pin_MCP4822_CE6, GPIO_Pin_MCP4822_CE7, GPIO_Pin_MCP4822_CE8,
                                     GPIO_Pin_MCP4822_CE9, GPIO_Pin_MCP4822_CE10, GPIO_Pin_MCP4822_CE11, GPIO_Pin_MCP4822_CE12,
                                     GPIO_Pin_MCP4822_CE13, GPIO_Pin_MCP4822_CE14, GPIO_Pin_MCP4822_CE15, GPIO_Pin_MCP4822_CE16}; 

/***********************************片选脚宏定义结束************************************/

#define  GPIO_MCP4822_SCK   GPIOA
#define  GPIO_Pin_MCP4822_SCK  GPIO_Pin_8

#define  GPIO_MCP4822_SDI   GPIOC
#define  GPIO_Pin_MCP4822_SDI  GPIO_Pin_9

void MCP4822_Init()
{ 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC 
                           | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
    
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//由于使用到了PA15，PB4引脚，失能JTAG调试模式，是这些引脚作为普通I/O口
    
    GPIO_InitTypeDef GPIO_InitStructure;
    
    //MCP4822 GPIO
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_15; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOA,GPIO_Pin_9 | GPIO_Pin_15,Bit_SET);//disbble PCS 1,2
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; 
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOB,GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9,Bit_SET);//disable PCS 7,8,9,10,11,12

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOC,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12,Bit_SET);//disable PCS 3,4,5,13,14,15,16
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOD,GPIO_Pin_2 ,Bit_SET);//disable PCS 6
    
}

void MCP4822_Delay(void)
{
    uint32_t i = 10;

    while(i--)
    {
    }
}

void MCP4822_CSEnable(uint8_t select)
{
    GPIO_WriteBit(MCP4822_CS_PORT[select],MCP4822_CS_PIN[select],Bit_RESET);
}


void MCP4822_CSDisable(uint8_t select)
{
    GPIO_WriteBit(MCP4822_CS_PORT[select],MCP4822_CS_PIN[select],Bit_SET);
}
 

void MCP4822_Proc(uint8_t Channel, uint8_t Gain, uint8_t OutEnable, uint16_t Value,uint8_t select,uint8_t channel)
{
    uint16_t Data;
    uint8_t i;

    if(Channel == MCP4822_CHANNEL_A)
    {
        Data = 0;
    }
    else
    {
        Data = 0x8000;
    }

    if(Gain == MCP4822_GAIN_1X)
    {
        Data |= 0x2000;
    }

    if(OutEnable == MCP4822_OUTENABLE)
    {
        Data |= 0x1000;
    }

    Data |= (Value & 0x0FFF);

#if EN_LDAC
    GPIO_WriteBit(GPIO_MCP4822_LDAC, GPIO_Pin_MCP4822_LDAC, Bit_SET);
    MCP4822_Delay();
#endif
    
    MCP4822_CSEnable(select);
    triggered_Pro(channel);
//    MCP4822_Delay();
    GPIO_WriteBit(GPIO_MCP4822_SCK, GPIO_Pin_MCP4822_SCK, Bit_RESET);
//    MCP4822_Delay();
    triggered_Pro(channel);
    
    for(i=0; i<16; i++)
    {
        if(Data&(0x8000>>i))
        {
            GPIO_WriteBit(GPIO_MCP4822_SDI, GPIO_Pin_MCP4822_SDI, Bit_SET);
        }
        else
        {
            GPIO_WriteBit(GPIO_MCP4822_SDI, GPIO_Pin_MCP4822_SDI, Bit_RESET);
        }
        triggered_Pro(channel);
//        MCP4822_Delay();
        GPIO_WriteBit(GPIO_MCP4822_SCK, GPIO_Pin_MCP4822_SCK, Bit_SET);
//        MCP4822_Delay();
        triggered_Pro(channel);
        GPIO_WriteBit(GPIO_MCP4822_SCK, GPIO_Pin_MCP4822_SCK, Bit_RESET);
    }
    
//    MCP4822_Delay();
    triggered_Pro(channel);
    MCP4822_CSDisable(select);
//    MCP4822_Delay();
    triggered_Pro(channel);


#if EN_LDAC
    GPIO_WriteBit(GPIO_MCP4822_LDAC, GPIO_Pin_MCP4822_LDAC, Bit_RESET);
    //MCP4822_Delay();
    triggered_Pro(channel);
    GPIO_WriteBit(GPIO_MCP4822_LDAC, GPIO_Pin_MCP4822_LDAC, Bit_SET);
    MCP4822_Delay();
#endif
}

//from U1 VSE1 VSET2 ........,VSETx from 1 to 16
void MCP4822_OutputVset(uint8_t VSETx,uint16_t VoutValue)
{
    if(VSETx % 2)
      MCP4822_Proc(MCP4822_CHANNEL_A, MCP4822_GAIN_2X, MCP4822_OUTENABLE, VoutValue,(VSETx+1)/2-1,VSETx);
    else
      MCP4822_Proc(MCP4822_CHANNEL_B, MCP4822_GAIN_2X, MCP4822_OUTENABLE, VoutValue,(VSETx+1)/2-1,VSETx);
}       
