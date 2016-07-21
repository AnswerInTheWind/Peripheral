#define _MCP4822_C_

#include "stm32f10x.h"

#include "MCP4822.h"


#define EN_LDAC  0

#if EN_LDAC

#define  GPIO_MCP4822_LDAC   GPIOC
#define  GPIO_Pin_MCP4822_LDAC  GPIO_Pin_1

#endif

#define  GPIO_MCP4822_CE   GPIOA
#define  GPIO_Pin_MCP4822_CE  GPIO_Pin_9

#define  GPIO_MCP4822_SCK   GPIOA
#define  GPIO_Pin_MCP4822_SCK  GPIO_Pin_8

#define  GPIO_MCP4822_SDI   GPIOC
#define  GPIO_Pin_MCP4822_SDI  GPIO_Pin_9


void MCP4822_Delay(void)
{
    uint32_t i = 1000;

    while(i--)
    {
    }
}



void MCP4822_Proc(uint8_t Channel, uint8_t Gain, uint8_t OutEnable, uint16_t Value)
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

    GPIO_WriteBit(GPIO_MCP4822_CE, GPIO_Pin_MCP4822_CE, Bit_RESET);
    MCP4822_Delay();
    GPIO_WriteBit(GPIO_MCP4822_SCK, GPIO_Pin_MCP4822_SCK, Bit_RESET);
    MCP4822_Delay();

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
        MCP4822_Delay();
        GPIO_WriteBit(GPIO_MCP4822_SCK, GPIO_Pin_MCP4822_SCK, Bit_SET);
        MCP4822_Delay();
        GPIO_WriteBit(GPIO_MCP4822_SCK, GPIO_Pin_MCP4822_SCK, Bit_RESET);
    }

    MCP4822_Delay();
    GPIO_WriteBit(GPIO_MCP4822_CE, GPIO_Pin_MCP4822_CE, Bit_SET);
    MCP4822_Delay();

#if EN_LDAC
    GPIO_WriteBit(GPIO_MCP4822_LDAC, GPIO_Pin_MCP4822_LDAC, Bit_RESET);
    MCP4822_Delay();
    GPIO_WriteBit(GPIO_MCP4822_LDAC, GPIO_Pin_MCP4822_LDAC, Bit_SET);
    MCP4822_Delay();
#endif
}





