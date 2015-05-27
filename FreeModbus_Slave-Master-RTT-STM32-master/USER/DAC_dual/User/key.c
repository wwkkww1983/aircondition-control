/*
Key_GPIO_Config
ÅäÖÃ°´¼üÓÃGPIO
*/
#include "key.h"


void Delay( __IO u32 nCount)
{
	for(;nCount !=0; nCount--);
}


void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//¿ªÆô°´¼ü¶Ë¿ÚÊ±ÖÓ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

//Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
//¼ì²â°´¼üÊÇ·ñ°´ÏÂ
//Êä³öKEY_OFF£¨Ã»ÓÐ°´ÏÂ£© KEY_ON£¨°´ÏÂ°´¼ü£
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{
	//¼ì²âÊÇ·ñ°´ÏÂ
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON)
	{
		Delay(10000);
			if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON)
			{
				//µÈ´ý°´¼üÊÍ·Å
				while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON);
				return KEY_ON;
			}
			else
				return KEY_OFF;
	}
	else
		return KEY_OFF;
}
