/*
Key_GPIO_Config
���ð�����GPIO
*/
#include "key.h"


void Delay( __IO u32 nCount)
{
	for(;nCount !=0; nCount--);
}


void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//���������˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

//Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
//��ⰴ���Ƿ���
//���KEY_OFF��û�а��£� KEY_ON�����°����
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{
	//����Ƿ���
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON)
	{
		Delay(10000);
			if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON)
			{
				//�ȴ������ͷ�
				while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON);
				return KEY_ON;
			}
			else
				return KEY_OFF;
	}
	else
		return KEY_OFF;
}
