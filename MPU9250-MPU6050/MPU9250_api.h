#ifndef __MPU9250_API_H__
#define __MPU9250_API_H__

#include "dmp.h"
#include "IOI2C.h"
#include "MPU9250.h"

void Init_dmp(void);

void getyawpitchroll(void);


void getquaternion(void);


void getmag(void);


void readdmp(void);


void getAcc_gyro(void);



#endif

//------------------End of File----------------------------
