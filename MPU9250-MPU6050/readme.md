#MPU9250 MPU6050驱动(带DMP姿态融合)

MPU9250芯片

驱动一共分为两个个部分

	1.模拟I2C驱动
	2.MPU9250 及 DMP的 驱动

分别都有对应的*.c和*.h文件。

I2C相关的文件为IOI2C.C和IOI2C.h
MPU9250相关的文件有三个dmp.c/dmp.h/MPU9250_api.h

## I2C ##

此例程的I2C使用的是模拟的I2C，因为移植方便。驱动使用情况详见.h文件以及例程中的调用

## MPU9250 及DMP获取yaw、pitch、roll ##

因为MPU9250内置DMP姿态融合器，无需算法，直接使用DMP融合即可得到姿态。

其中，接口都在MPU9250_api.h文件中，包括MPU9250/DMP的初始化，传感数值的获取。

## 驱动文件使用方法 ##
首先需要把这五个文件添加到工程里面去
然后
- 在初始化的文件中#include "IOI2C.H" #include "MPU9250_api.h"
- 在需要获取传感器数值的文件中#include "MPU9250_api.h"

1. 初始化
```	
IIC_Init();//模拟I2C驱动的初始化，一定要先初始化I2C接口才能操作MPU9250芯片

Init_MPU9250_With_DMP();//初始化MPU9250,配置并且开启DMP，设置中断方式为加速度方式
```
2. 	函数调用

``` c
uint16_t fifo_count = 0;
while(1)//使用循环是为了等待DMP转换完成
{		
	fifo_count = MPU9250_getFIFOCount();//读取FIFO计数
	
	if(fifo_count >= 0x0200)//如果FIFO值>0x0200，此时DMP的结果错误，直接复位FIFO
	{
		MPU9250_resetFIFO();
	}
	else
	{
		
		if(fifo_count >= 0x2a)//如果FIFO值 > 0x2a,此时DMP转换完成并且数值正常
		{				
			readdmp(); //首先要读取DMP FIFO，读取之后才能进行计算姿态的操作
			MPU9250_resetFIFO();					
			getyawpitchroll();//计算并且获取yaw、pitch、roll，结果保存在yprf[3]数组中
			break;//转换并且计算完成之后退出循环
		}	
	}		
}
```

NOTE:在判断DMP是否完成时，应当从FIFO的计数中去判断，当计数大于等于42，说明DMP转换完成，
也可以采用中断的方式来作为标志。
