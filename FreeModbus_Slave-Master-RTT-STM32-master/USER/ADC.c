/***********************************************************************
�ļ����ƣ�adc.C
��    �ܣ���ɶ�adc����
��дʱ�䣺2012.11.22
�� д �ˣ�
ע    �⣺
***********************************************************************/
#include "ADC.h"
// #include "USART1.h"

uint16_t ADC_RCVTab[7] ;   //�Լ����

/***********************************************************************
�������ƣ�void ADC_Configuration(void) 
��    �ܣ����adc������
���������
���������

		  
***********************************************************************/
void ADC_Configuration(void)
{
	
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO | RCC_APB2Periph_ADC1 ,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);//ʹ��DMAʱ��
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)&ADC1->DR;  //DMA����ADC����
	DMA_InitStructure.DMA_MemoryBaseAddr =(u32)ADC_RCVTab;//�ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//dma���䷽����
	DMA_InitStructure.DMA_BufferSize = 7;//����DMA�ڴ���ʱ�������ĳ��� word
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//����DMA���������ģʽ��һ������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//����DMA���ڴ����ģʽ��
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//���������ֳ�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//�ڴ������ֳ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//����DMA�Ĵ���ģʽ���������ϵ�ѭ��ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//����DMA�����ȼ���
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//����DMA��2��memory�еı����������
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* ADC1 Configuration ------------------------------------------------------*/
	ADC_DeInit(ADC1);  //������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//������ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;   //����ת��
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //ת������������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //�Ҷ��� 
	ADC_InitStructure.ADC_NbrOfChannel = 7;//ɨ��ͨ���� 
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
	ADC_ResetCalibration(ADC1);          //��λָ����ADC1��У׼�Ĵ���           
	/* Check the end of ADC1 reset calibration register */           
	while(ADC_GetResetCalibrationStatus(ADC1));        //��ȡADC1��λУ׼�Ĵ�����״̬,����״̬��ȴ�
	/* Start ADC1 calibaration */           
	ADC_StartCalibration(ADC1);                //��ʼָ��ADC1��У׼״̬         
	/* Check the end of ADC1 calibration */          
	while(ADC_GetCalibrationStatus(ADC1));                //��ȡָ��ADC1��У׼����,����״̬��ȴ�
	/* Start ADC1 Software Conversion */
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); 
	DMA_Cmd(DMA1_Channel1, ENABLE);  //����DMAͨ��
}
/***********************************************************************
�������ƣ�void ADC_Show(void) 
��    �ܣ�
���������
���������

		  
***********************************************************************/
float p_ch[7];
void ADC_Show(void)
{

	unsigned char i = 0;
	for(i = 0;i < 7;i ++)//���7·��ѹֵ
	{
		p_ch[i] = (ADC_RCVTab[i]) * 3.3 / 4095.0;
	//	printf("%4.2f   ",p_ch[i]);
	}
	

	//printf("\n");
}

