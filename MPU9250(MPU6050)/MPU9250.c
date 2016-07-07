#include "MPU9250.h"
#include "IOI2C.h"

uint8_t buffer[14];

int16_t  MPU9250_FIFO[6][11];
int16_t Gx_offset=0,Gy_offset=0,Gz_offset=0;

uint8_t pgm_read_byte(uint16_t add){
	return 0;
}

void MPU9250_INT_init()
{
  GPIO_InitTypeDef   GPIO_InitStructure;
  /* Enable GPIOA clock */
  __GPIOA_CLK_ENABLE();
	
  /* Configure PA8 pin as input floating */
  GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStructure.Pull = GPIO_PULLDOWN;
  GPIO_InitStructure.Pin = MPU9250_INT_PIN;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  HAL_GPIO_Init(MPU9250_INT_PORT, &GPIO_InitStructure);
	
  /* Enable and set EXTI4_15 Interrupt priority */
//  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 1, 0);//
//  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
}

void MPU9250_Sleep()
{
	IICwriteByte(GYRO_ADDRESS,MPU9250_RA_PWR_MGMT_1, 0x40);//pw1	
}

void MPU9250_WakeUp()
{
	IICwriteByte(GYRO_ADDRESS,MPU9250_RA_PWR_MGMT_1, 0x00);//pw1	
}

/**************************实现函数********************************************
*函数原型:		unsigned char MPU9250_is_DRY(void)
*功　　能:	    检查 MPU9250的中断引脚，测试是否完成转换
返回 1  转换完成
0 数据寄存器还没有更新
*******************************************************************************/
unsigned char MPU9250_is_DRY(void)
{
	if(HAL_GPIO_ReadPin(MPU9250_INT_PORT,MPU9250_INT_PIN)==1)
		return 1;
	else
		return 0;
}

/** Reset the FIFO.
 * This bit resets the FIFO buffer when set to 1 while FIFO_EN equals 0. This
 * bit automatically clears to 0 after the reset has been triggered.
 * @see MPU9250_RA_USER_CTRL
 * @see MPU9250_USERCTRL_FIFO_RESET_BIT
 */
void MPU9250_resetFIFO(void)
{
    IICwriteBit(devAddr, MPU9250_RA_USER_CTRL, MPU9250_USERCTRL_FIFO_RESET_BIT, 1);
}

/** Get current FIFO buffer size.
 * This value indicates the number of bytes stored in the FIFO buffer. This
 * number is in turn the number of bytes that can be read from the FIFO buffer
 * and it is directly proportional to the number of samples available given the
 * set of sensor data bound to be stored in the FIFO (register 35 and 36).
 * @return Current FIFO buffer size
 */
uint16_t MPU9250_getFIFOCount(void) 
{
    IICreadBytes(devAddr, MPU9250_RA_FIFO_COUNTH, 2, buffer);
    return (((uint16_t)buffer[0]) << 8) | buffer[1];
}


//------------------End of File----------------------------
