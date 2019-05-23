#include "osCore.h"
#include "Hal_HTU.h"
#include "hal_i2c.h"

#define DBG_HTU21	0

unsigned char flag = 0;
/*================================================================
���� �ơ�void Delay(unsigned int t)
���� �ܡ���ʱ��
================================================================*/
static void Delay(unsigned int t)
{
	osSleep(t/10);
}

/*================================================================
���� �ơ�void SHT21Init(void)
���� �ܡ�SHT21��ʼ������
================================================================*/
void HTU21DInit(void)
{
	Hal_I2C_Init();		//I2C��ʼ��
	Hal_I2C_Start();		//����I2C
	Hal_I2C_WriteByte(HTU21DADDR&0xfe);		//дSHT21��I2C��ַ
	Hal_I2C_WriteByte(0xfe);
	Hal_I2C_Stop();		//ֹͣI2C
	Delay(600);		//����ʱ
}


/*================================================================
���� �ơ�long Sht21Work(unsigned char order)
���� �ܡ�Sht21������ʪ��
================================================================*/
int HTU21DWork(unsigned char order)
{
	float temp = 0;
	unsigned char MSB,LSB;
	unsigned int shidu,wendu;
	int tt;
	Hal_I2C_Start();
	if(Hal_I2C_WriteByte(HTU21DADDR & 0xfe) == I2C_ACK)
	{
		if(Hal_I2C_WriteByte(order) == I2C_ACK)
		{
			do
			{
				Delay(10);
				Hal_I2C_Start();
			}
			while(Hal_I2C_WriteByte(HTU21DADDR | 0x01) == I2C_NACK);
			MSB = Hal_I2C_ReadByte(I2C_ACK);
			Delay(10);
			LSB = Hal_I2C_ReadByte(I2C_ACK);
			Hal_I2C_ReadByte(I2C_NACK);
			Hal_I2C_Stop();
			LSB &= 0xfc;
			tt = MSB;tt&=0x00FF;
			tt = (tt<<8)|LSB;
			osLogI(DBG_HTU21,"H:%02x, L:%02x ,temp:%d \r\n",MSB,LSB,tt);
			if (order == 0xf3)//���������¶ȼ��
			{
				temp=(175.72)*tt/65536-46.85;//�¶�:T= -46.85 + 175.72 * ST/2^16
				wendu =(unsigned int)(temp*100);
				return wendu;	
			}
			else
			{
				temp = (tt*125)/65536-6;
				shidu = (unsigned int)(temp*100);//ʪ��: RH%= -6 + 125 * SRH/2^16
				return shidu;
			}
		}
		else
		{
			osLogI(DBG_HTU21,"error \r\n");
		}
	}
	else
	{
		osLogI(DBG_HTU21,"error \r\n");
	}
	return 0;
}
