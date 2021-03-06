/*
Key_GPIO_Config
配置按键用GPIO
*/
#include "key.h"


void Delay( __IO u32 nCount)
{
	for(;nCount !=0; nCount--);
}


void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//开启按键端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

//Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
//检测按键是否按下
//输出KEY_OFF（没有按下） KEY_ON（按下按键�
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{
	//检测是否按下
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON)
	{
		Delay(10000);
			if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON)
			{
				//等待按键释放
				while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON);
				return KEY_ON;
			}
			else
				return KEY_OFF;
	}
	else
		return KEY_OFF;
}
