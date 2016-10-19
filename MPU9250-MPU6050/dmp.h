#ifndef __DMP_H
#define __DMP_H

#include <stdint.h>

extern float yprf[3];   /* Euler ??*/
extern float gyrof[3];  /* ?????*/
extern float accelf[3]; /* ????*/
extern float yprf[3];   /* Euler ??*/
extern float mag[3];

void Init_dmp(void);
void getyawpitchroll(void);
void getquaternion(void);
void getmag(void);
void readdmp(void);
void getAcc_gyro(void);

#endif

