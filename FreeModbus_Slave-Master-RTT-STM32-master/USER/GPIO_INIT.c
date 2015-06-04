#include "GPIO_INIT.h"

void DI_INIT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE, ENABLE );
  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;                 // …Ë÷√
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}


void DO_INIT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF, ENABLE );
  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;                 // …Ë÷√
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;          
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
}

void GPIO_INIT(void)
{
		DI_INIT();
	  DO_INIT();
}

void DO_OUT(void)
{
	
	
	unsigned char i=0;
  uint16_t coilbit=0x0001;
  unsigned short GPIO_Pin_DO;
	coilbit=0x0001;
		 GPIO_Pin_DO=GPIO_Pin_8;	
	
			for(i=0;i<8;i++)
			{
				if((ucSCoilBuf[0]&coilbit)==coilbit )
				{	
					GPIO_SetBits(GPIOE,GPIO_Pin_DO);
				}
					else
						GPIO_ResetBits(GPIOE,GPIO_Pin_DO);
					
					coilbit=coilbit<<1;
					GPIO_Pin_DO=GPIO_Pin_DO<<1;
			}
		//	GPIO_SetBits(GPIOE,GPIO_Pin_8);
		//  GPIO_ResetBits(GPIOE,GPIO_Pin_8);
			
		 coilbit=0x0100;
		 GPIO_Pin_DO=GPIO_Pin_0;	
			for(i=0;i<8;i++)
			{
				if((ucSCoilBuf[0]&coilbit)==coilbit )
				{	
					GPIO_SetBits(GPIOF,GPIO_Pin_DO);
				}
					else
						GPIO_ResetBits(GPIOF,GPIO_Pin_DO);
					
					coilbit=coilbit<<1;
					GPIO_Pin_DO=GPIO_Pin_DO<<1;
			}	
			
			
}

