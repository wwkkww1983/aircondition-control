//DAC


#include "DAC.h"


void Dac1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitType;
   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );     //使能PA时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );     //使能DAC时钟
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;                 // PA4设置
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;          
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOA, &GPIO_InitStructure);
   // GPIO_SetBits(GPIOA,GPIO_Pin_4)    ;//PA.4 为高
    
    DAC_InitType.DAC_Trigger=DAC_Trigger_Software;    //不适用触发
    DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//不适用波形发生
    DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、
    DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;    //DAC1输出缓冲
    DAC_Init(DAC_Channel_1,&DAC_InitType);     //???DAC??1
    
    DAC_Cmd(DAC_Channel_1, ENABLE); //使能
    DAC_SetChannel1Data(DAC_Align_12b_R, 0); //12位，右对齐。0为输出数值
	  DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE); // 触发DAC1
}


void Dac2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitType;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );     //使能PA时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );     //使能DAC时钟
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;                 // PA4设置
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;          
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOA, &GPIO_InitStructure);
    //GPIO_SetBits(GPIOA,GPIO_Pin_5)    ;//PA.5 输出高
    
    DAC_InitType.DAC_Trigger=DAC_Trigger_Software;    //不适用触发
    DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//不适用波形发生
    DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽
    DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;    //DAC2输出缓冲
    DAC_Init(DAC_Channel_2,&DAC_InitType);     //???DAC??2
    
    DAC_Cmd(DAC_Channel_2, ENABLE); //使能
    DAC_SetChannel2Data(DAC_Align_12b_R, 0); //12位，右对齐。0为输出数值
	  DAC_SoftwareTriggerCmd(DAC_Channel_2,ENABLE); // 触发DAC2
}

void DAC_INIT(void)
{
		Dac2_Init();
	  Dac1_Init();
}


void DAC_OUTPUT(unsigned int voltage1, unsigned int voltage2)
{
	 DAC_SetChannel1Data(DAC_Align_12b_R, (voltage1)*4096/3.3); //12位，右对齐。
	 DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE); // 触发DAC1
	 DAC_SetChannel2Data(DAC_Align_12b_R, (voltage2)*4096/3.3); //12位，右对齐.
	 DAC_SoftwareTriggerCmd(DAC_Channel_2,ENABLE); // 触发DAC1
}






