#include "MPU9250_api.h"

void MPU9250_init()
{
    I2C_INIT...
    MPU2950_REG_INIT...
    DMP_INIT....

    MPU9250_INT_INIT.....
}

void getyawpitchroll(void);


void getquaternion(void);



void getAcc_gyro(void);
