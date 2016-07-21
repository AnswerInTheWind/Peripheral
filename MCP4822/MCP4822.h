#ifndef _MCP4822_H_
#define _MCP4822_H_

#ifdef _MCP4822_C_
    #define _MCP4822_EXT_
#else
    #define _MCP4822_EXT_ extern
#endif

#define  MCP4822_CHANNEL_A     0
#define  MCP4822_CHANNEL_B     1

#define  MCP4822_GAIN_1X       0
#define  MCP4822_GAIN_2X       1

#define  MCP4822_OUTDISABLE    0
#define  MCP4822_OUTENABLE     1

_MCP4822_EXT_ void MCP4822_Proc(uint8_t Channel, uint8_t Gain, uint8_t OutEnable, uint16_t Value);



#endif

