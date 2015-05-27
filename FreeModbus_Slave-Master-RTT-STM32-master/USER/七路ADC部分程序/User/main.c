/**
  ******************************************************************************
  * @file    main.c
  * @author  Fan
  * @version V1.0
  * @date   
  * @brief   
  ******************************************************************************
  * @attention

  ******************************************************************************
  */
  
//#include "stm32f10x.h"
#include "USART1.h"
#include "ADC.h"
//#include "stdio.h"





/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
	

float ADC_ConvertedValueLocal;
void Delay (__IO uint32_t nCount)
{
	for(;nCount != 0; nCount--);
}
int main(void)
{
  //USART1 Config 115200 8-N-1
	USART1_Config();
  ADC_Configuration();
	printf ("\r\n---------------This is a ADC experiment--------------------\r\n");
	
	for(;;)
	{
    ADC_Show();
		
		Delay (0xffffee);
	}
	
	
}





/*********************************************END OF FILE**********************/

