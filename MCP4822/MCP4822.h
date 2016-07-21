#ifndef _MCP4822_H_
#define _MCP4822_H_

#ifdef _MCP4822_C_
    #define _MCP4822_EXT_
#else
    #define _MCP4822_EXT_ extern
#endif

/*********************************************************************************************
对16个MCP4822进行编号
*********************************************************************************************/
#define  MCP4822_PCS_1                  0
#define  MCP4822_PCS_2                  1
#define  MCP4822_PCS_3                  2
#define  MCP4822_PCS_4                  3
#define  MCP4822_PCS_5                  4
#define  MCP4822_PCS_6                  5
#define  MCP4822_PCS_7                  6
#define  MCP4822_PCS_8                  7
#define  MCP4822_PCS_9                  8
#define  MCP4822_PCS_10                 9
#define  MCP4822_PCS_11                 10
#define  MCP4822_PCS_12                 11
#define  MCP4822_PCS_13                 12
#define  MCP4822_PCS_14                 13
#define  MCP4822_PCS_15                 14
#define  MCP4822_PCS_16                 15

#define  MCP4822_CHANNEL_A     0
#define  MCP4822_CHANNEL_B     1

#define  MCP4822_GAIN_1X       0
#define  MCP4822_GAIN_2X       1

#define  MCP4822_OUTDISABLE    0
#define  MCP4822_OUTENABLE     1

_MCP4822_EXT_ void MCP4822_Proc(uint8_t Channel, uint8_t Gain, uint8_t OutEnable, uint16_t Value,uint8_t select,uint8_t channel);
void MCP4822_Init();
void MCP4822_OutputVset(uint8_t VSETx,uint16_t VoutValue);


#endif

