/***********************************************************************
文件名称：adc.C
功    能：完成对adc操作
编写时间：2012.11.22
编 写 人：
注    意：
***********************************************************************/
#include "ADC.h"
// #include "USART1.h"

uint16_t ADC_RCVTab[7] ;   //自己添加

/***********************************************************************
函数名称：void ADC_Configuration(void) 
功    能：完成adc的配置
输入参数：
输出参数：

		  
***********************************************************************/
void ADC_Configuration(void)
{
	
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO | RCC_APB2Periph_ADC1 ,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);//使能DMA时钟
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)&ADC1->DR;  //DMA外设ADC基地
	DMA_InitStructure.DMA_MemoryBaseAddr =(u32)ADC_RCVTab;//内存地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//dma传输方向单向
	DMA_InitStructure.DMA_BufferSize = 7;//设置DMA在传输时缓冲区的长度 word
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//设置DMA的外设递增模式，一个外设
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//设置DMA的内存递增模式，
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//外设数据字长
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//内存数据字长
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//设置DMA的传输模式：连续不断的循环模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//设置DMA的优先级别
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//设置DMA的2个memory中的变量互相访问
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* ADC1 Configuration ------------------------------------------------------*/
	ADC_DeInit(ADC1);  //将外设 ADC1 的全部寄存器重设为缺省值
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//连续多通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;   //连续转换
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //转换不受外界决定
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //右对齐 
	ADC_InitStructure.ADC_NbrOfChannel = 7;//扫描通道数 
	ADC_Init(ADC1, &ADC_InitStructure);
	/* ADC1 regular channel10 configuration */
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 1, ADC_SampleTime_28Cycles5);	 	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10,2, ADC_SampleTime_28Cycles5);	   
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11,3, ADC_SampleTime_28Cycles5);	 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12,4, ADC_SampleTime_28Cycles5);	   
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13,5, ADC_SampleTime_28Cycles5);	   	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14,6, ADC_SampleTime_28Cycles5);	   	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15,7, ADC_SampleTime_28Cycles5);	   	
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	/* Enable ADC1 reset calibaration register */              
	ADC_ResetCalibration(ADC1);          //复位指定的ADC1的校准寄存器           
	/* Check the end of ADC1 reset calibration register */           
	while(ADC_GetResetCalibrationStatus(ADC1));        //获取ADC1复位校准寄存器的状态,设置状态则等待
	/* Start ADC1 calibaration */           
	ADC_StartCalibration(ADC1);                //开始指定ADC1的校准状态         
	/* Check the end of ADC1 calibration */          
	while(ADC_GetCalibrationStatus(ADC1));                //获取指定ADC1的校准程序,设置状态则等待
	/* Start ADC1 Software Conversion */
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); 
	DMA_Cmd(DMA1_Channel1, ENABLE);  //启动DMA通道
}
/***********************************************************************
函数名称：void ADC_Show(void) 
功    能：
输入参数：
输出参数：

		  
***********************************************************************/
float p_ch[7];
void ADC_Show(void)
{

	unsigned char i = 0;
	for(i = 0;i < 7;i ++)//输出7路电压值
	{
		p_ch[i] = (ADC_RCVTab[i]) * 3.3 / 4095.0;
	//	printf("%4.2f   ",p_ch[i]);
	}
	

	//printf("\n");
}

