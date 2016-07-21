#ifndef _EEPROM_H_
#define _EEPROM_H_

#ifdef _EEPROM_C_
    #define _EEPROM_EXT_
#else
    #define _EEPROM_EXT_ extern
#endif

_EEPROM_EXT_ uint8_t EEPROM_Data[32];
_EEPROM_EXT_ void EEPROM_Read_Config(void);
_EEPROM_EXT_ void EEPROM_Write_Config(void);

#endif

