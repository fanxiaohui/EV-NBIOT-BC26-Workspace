/***********************************************************************************************
*
*
*
*
*
*
*
*
***************************************************************************************************/
#include "osCore.h"

#define I2C_SCL_PIN		PINNAME_GPIO4			 // ���ӵ�SCLʱ���ߵ�GPIO
#define I2C_SDA_PIN		PINNAME_GPIO5			 // ���ӵ�SDA�����ߵ�GPIO

#define I2C_NACK		1
#define I2C_ACK			0

static uint8 I2C_SCL_READ(void);
static uint8 I2C_SDA_READ(void);
static uint8 I2C_SCL_1(void);
static uint8 I2C_SCL_0(void);
static uint8 I2C_SDA_1(void);
static uint8 I2C_SDA_0(void);
static void I2C_Delay (uint8 t);

static uint8 I2C_SCL_READ(void)
{
	uint8 ret = 0;
	do{
		Ql_GPIO_SetDirection(I2C_SCL_PIN,PINDIRECTION_IN);
		if(Ql_GPIO_GetLevel(I2C_SCL_PIN))
			ret = 1;
	}while(0);
	return ret;
}
static uint8 I2C_SDA_READ(void)
{
	uint8 ret = 0;
	do{
		Ql_GPIO_SetDirection(I2C_SDA_PIN,PINDIRECTION_IN);
		if(Ql_GPIO_GetLevel(I2C_SDA_PIN))
			ret = 1;
	}while(0);
	return ret;
}
static uint8 I2C_SCL_1(void)
{
	uint8 ret = 0;
	do{
		Ql_GPIO_SetDirection(I2C_SCL_PIN,PINDIRECTION_OUT);
		Ql_GPIO_SetLevel(I2C_SCL_PIN,1);
	}while(0);
	return ret;
}
static uint8 I2C_SCL_0(void)
{
	uint8 ret = 0;
	do{
		Ql_GPIO_SetDirection(I2C_SCL_PIN,PINDIRECTION_OUT);
		Ql_GPIO_SetLevel(I2C_SCL_PIN,0);
	}while(0);
	return ret;
}
static uint8 I2C_SDA_1(void)
{
	uint8 ret = 0;
	do{
		Ql_GPIO_SetDirection(I2C_SDA_PIN,PINDIRECTION_OUT);
		Ql_GPIO_SetLevel(I2C_SDA_PIN,1);
	}while(0);
	return ret;
}
static uint8 I2C_SDA_0(void)
{
	uint8 ret = 0;
	do{
		Ql_GPIO_SetDirection(I2C_SDA_PIN,PINDIRECTION_OUT);
		Ql_GPIO_SetLevel(I2C_SDA_PIN,0);
	}while(0);
	return ret;
}
/*================================================================
���� �ơ�void I2C_Delay (uint8 t)
���� �ܡ�ģ��IIC�õĶ���ʱ
================================================================*/
static void I2C_Delay (uint8 t)
{
	//osSleep(1);
}
/*================================================================
���� �ơ�void I2CInit(void)
���� �ܡ�I2C��ʼ��������״̬
================================================================*/
void Hal_I2C_Init(void)
{
	Ql_GPIO_Init(I2C_SCL_PIN,//Enum_PinName       pinName,
				PINDIRECTION_OUT,//Enum_PinDirection  dir,
				PINLEVEL_HIGH,//Enum_PinLevel      level,
				PINPULLSEL_DISABLE//Enum_PinPullSel    pullSel
	            );
	Ql_GPIO_Init(I2C_SDA_PIN,//Enum_PinName       pinName,
				PINDIRECTION_OUT,//Enum_PinDirection  dir,
				PINLEVEL_HIGH,//Enum_PinLevel      level,
				PINPULLSEL_PULLUP//Enum_PinPullSel    pullSel
	            );
	I2C_SDA_1();
	I2C_Delay(10);
	I2C_SCL_1();
	I2C_Delay(10);
}
/*================================================================
���� �ơ�void I2CStart(void)
���� �ܡ�I2C�����ź�
���� ע��SCL��SDAͬΪ�ߣ�SDA����ɵ�֮��SCL����ɵ�
================================================================*/
void Hal_I2C_Start(void)
{
  	I2C_SDA_1();
  	I2C_SCL_1();
  	I2C_Delay(10);
  	I2C_SDA_0();
  	I2C_Delay(10);
  	I2C_SCL_0();
  	I2C_Delay(10);
}
/*================================================================
���� �ơ�void I2CStop(void)
���� �ܡ�I2Cֹͣ�ź�
���� ע��SCL��SDAͬΪ�ͣ�SCL����ɸ�֮��SDA����ɸ�
================================================================*/
void Hal_I2C_Stop(void)
{
		I2C_SDA_0();
  	I2C_SCL_0();
		I2C_Delay(10);
  	I2C_SCL_1();
  	I2C_Delay(10);
  	I2C_SDA_1();
  	I2C_Delay(10);
}
/*================================================================
���� �ơ�uint8 I2CWRByte(uint8 WriteData)
���� �ܡ�I2Cдһ���ֽ����ݣ�����ACK����NACK
���� ע���Ӹߵ��ͣ����η���
================================================================*/
uint8 Hal_I2C_WriteByte(uint8 WriteData)
{
	uint8 i;
	I2C_SCL_0();
	for(i = 0;i < 8;i++)
	{
		if(WriteData & 0x80)
			{
			I2C_SDA_1();
			}
		else
			I2C_SDA_0();
		I2C_Delay(100);
		I2C_SCL_1();	    //���SDA�ȶ�������SCL���������أ��ӻ���⵽��������ݲ���
		I2C_Delay(500);
		I2C_SCL_0();
		I2C_Delay(100);
		WriteData <<= 1;
//		I2C_SCL_0();
	}
	I2C_Delay(20);
	I2C_SDA_1();
	I2C_SCL_1();
	I2C_Delay(30);
	if(I2C_SDA_READ() == 1)			//SDAΪ�ߣ��յ�NACK
	{
		return I2C_NACK;
	}
	else 				    //SDAΪ�ͣ��յ�ACK
	{
		I2C_SCL_0();
		I2C_Delay(50);
		return I2C_ACK;
	}
}
/*================================================================
���� �ơ�uint8 I2CRDByte(uint8 AckValue)
���� �ܡ�I2C��һ���ֽ����ݣ���ڲ������ڿ���Ӧ��״̬��ACK����NACK
���� ע���Ӹߵ��ͣ����ν���
================================================================*/
uint8 Hal_I2C_ReadByte(uint8 AckValue)
{
	uint8 i,ReadData = 0;
	I2C_SCL_0();
	I2C_SDA_1();			//�ͷ�����
	for(i = 0;i < 8;i++)
	{
		I2C_SCL_1();		//����������
		I2C_Delay(30);	//��ʱ�ȴ��ź��ȶ�
		ReadData <<= 1;
		if(I2C_SDA_READ() == 1) 		//������ȡ����
		{
			ReadData |= 0x01;
		}
		else
		{
			ReadData &= 0xfe;
		}
		I2C_Delay(10);
		I2C_SCL_0();   		//�½��أ��ӻ�������һλֵ
		I2C_Delay(20);
	}
	if(AckValue)//Ӧ��״̬
	{
		I2C_SCL_1();
	}
	else
	{
		I2C_SCL_0();
	}
	I2C_Delay(10);
	I2C_SCL_1();
  	I2C_Delay(50);
  	I2C_SCL_0();
	  I2C_Delay(50);
	return ReadData;
}
