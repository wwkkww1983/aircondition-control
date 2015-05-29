//DAC


#include "DAC.h"


void Dac1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitType;
   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );     //ʹ��PAʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );     //ʹ��DACʱ��
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;                 // PA4����
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;          
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOA, &GPIO_InitStructure);
   // GPIO_SetBits(GPIOA,GPIO_Pin_4)    ;//PA.4 Ϊ��
    
    DAC_InitType.DAC_Trigger=DAC_Trigger_Software;    //�����ô���
    DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//�����ò��η���
    DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//���Ρ�
    DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;    //DAC1�������
    DAC_Init(DAC_Channel_1,&DAC_InitType);     //???DAC??1
    
    DAC_Cmd(DAC_Channel_1, ENABLE); //ʹ��
    DAC_SetChannel1Data(DAC_Align_12b_R, 0); //12λ���Ҷ��롣0Ϊ�����ֵ
	  DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE); // ����DAC1
}


void Dac2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitType;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );     //ʹ��PAʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );     //ʹ��DACʱ��
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;                 // PA4����
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;          
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOA, &GPIO_InitStructure);
    //GPIO_SetBits(GPIOA,GPIO_Pin_5)    ;//PA.5 �����
    
    DAC_InitType.DAC_Trigger=DAC_Trigger_Software;    //�����ô���
    DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//�����ò��η���
    DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//����
    DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;    //DAC2�������
    DAC_Init(DAC_Channel_2,&DAC_InitType);     //???DAC??2
    
    DAC_Cmd(DAC_Channel_2, ENABLE); //ʹ��
    DAC_SetChannel2Data(DAC_Align_12b_R, 0); //12λ���Ҷ��롣0Ϊ�����ֵ
	  DAC_SoftwareTriggerCmd(DAC_Channel_2,ENABLE); // ����DAC2
}

void DAC_INIT(void)
{
		Dac2_Init();
	  Dac1_Init();
}


void DAC_OUTPUT(unsigned int voltage1, unsigned int voltage2)
{
	 DAC_SetChannel1Data(DAC_Align_12b_R, (voltage1)*4096/3.3); //12λ���Ҷ��롣
	 DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE); // ����DAC1
	 DAC_SetChannel2Data(DAC_Align_12b_R, (voltage2)*4096/3.3); //12λ���Ҷ���.
	 DAC_SoftwareTriggerCmd(DAC_Channel_2,ENABLE); // ����DAC1
}






