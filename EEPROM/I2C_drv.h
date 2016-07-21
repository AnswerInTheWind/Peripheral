#ifndef _I2C_DRV_H_
#define _I2C_DRV_H_

#ifdef _I2C_DRV_C_
#define _I2CDRVEXT_
#else
#define _I2CDRVEXT_ extern
#endif



/************************************************************
				Exern Function Setction
*************************************************************/
_I2CDRVEXT_ void I2C_DrvInit(void);
_I2CDRVEXT_ void I2Cm_Start(void);
_I2CDRVEXT_ void I2Cm_Stop(void);
_I2CDRVEXT_ void I2Cm_WaitAck(void);
_I2CDRVEXT_ void I2Cm_Ack(void);
_I2CDRVEXT_ void I2Cm_nAck(void);
_I2CDRVEXT_ void I2Cm_TxData(uint8_t i2c_data);
_I2CDRVEXT_ uint8_t I2Cm_RxData(void);
_I2CDRVEXT_ void I2C_WriteReg(uint8_t* Data, uint8_t I2C_Addr, uint8_t I2C_Reg, uint8_t Num);
_I2CDRVEXT_ void I2C_ReadReg(uint8_t* Data, uint8_t I2C_Addr, uint8_t I2C_Reg, uint8_t Num);

 
#endif
