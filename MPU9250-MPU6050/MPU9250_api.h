#ifndef __MPU9250_API_H__
#define __MPU9250_API_H__

#include "dmp.h"
#include "IOI2C.h"

extern float q[4]; /* ???*/
extern float gyrof[3];  /* X/Y/Z ???*/
extern float accelf[3]; /* X/Y/Z ??? */
extern float yprf[3];   /* yaw/pitch/roll*/
extern float mag[3];


//初始化MPU9250，并且开启DMP，设置中断模式为加速度中断
extern void Init_MPU9250_With_DMP(void);

//复位FIFO
extern void MPU9250_resetFIFO(void);

//获取FIFO的计数
extern uint16_t MPU9250_getFIFOCount(void);

//获取yaw/pitch/roll
extern void getyawpitchroll(void);

//获取四元数
extern void getquaternion(void);

//获取 X/Y/Z 磁力计值
extern void getmag(void);

//读取DMP FIFO
extern void readdmp(void);

//获取加速度、角速度
extern void getAcc_gyro(void);

//判断MPU9250是否已经发生过中断 1：发生过 0：未发生
extern uint8_t MPU9250_Interrupted(void);

//休眠MPU9250
extern void MPU9250_Sleep(void);

//唤醒MPU9250
extern void MPU9250_WakeUp(void);

#endif

//------------------End of File----------------------------
