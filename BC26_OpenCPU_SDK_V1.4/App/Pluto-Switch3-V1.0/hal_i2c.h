/*
 * hal_i2c.h
 *
 *  Created on: 2019��5��1��
 *      Author: Administrator
 */

#ifndef APP_GATEWAY_ZB_V01_HAL_I2C_H_
#define APP_GATEWAY_ZB_V01_HAL_I2C_H_

#include "osCore.h"

#define I2C_NACK		1
#define I2C_ACK			0

void Hal_I2C_Init(void);
/*================================================================
���� �ơ�void I2CStart(void)
���� �ܡ�I2C�����ź�
���� ע��SCL��SDAͬΪ�ߣ�SDA����ɵ�֮��SCL����ɵ�
================================================================*/
void Hal_I2C_Start(void);
/*================================================================
���� �ơ�void I2CStop(void)
���� �ܡ�I2Cֹͣ�ź�
���� ע��SCL��SDAͬΪ�ͣ�SCL����ɸ�֮��SDA����ɸ�
================================================================*/
void Hal_I2C_Stop(void);
/*================================================================
���� �ơ�uint8 I2CWRByte(uint8 WriteData)
���� �ܡ�I2Cдһ���ֽ����ݣ�����ACK����NACK
���� ע���Ӹߵ��ͣ����η���
================================================================*/
uint8 Hal_I2C_WriteByte(uint8 WriteData);
/*================================================================
���� �ơ�uint8 I2CRDByte(uint8 AckValue)
���� �ܡ�I2C��һ���ֽ����ݣ���ڲ������ڿ���Ӧ��״̬��ACK����NACK
���� ע���Ӹߵ��ͣ����ν���
================================================================*/
uint8 Hal_I2C_ReadByte(uint8 AckValue);

#endif /* APP_GATEWAY_ZB_V01_HAL_I2C_H_ */
