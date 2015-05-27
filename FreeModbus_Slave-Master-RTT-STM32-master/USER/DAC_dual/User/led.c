/*
name: led.c
discribe: led
author: Fan
PC3--LED1
PC4--LED2
PC5--LED3
*/

#include "led.h"



void LED_GPIO_Config(void)

{
	//����һ��GPIO_InitTypeDef���͵Ľṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructuree;
	//����GPIOC������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
	//ѡ��Ҫ���Ƶ�GPIO����
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_0;
	GPIO_InitStructuree.GPIO_Pin=GPIO_Pin_7 | GPIO_Pin_8;
	//��������ģʽΪͨ���������
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_InitStructuree.GPIO_Mode =GPIO_Mode_Out_PP;
	//������������Ϊ50MHZ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructuree.GPIO_Speed = GPIO_Speed_50MHz;
	//���ÿ⺯������ʼ��GPIOC
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_Init(GPIOF,&GPIO_InitStructuree);
	//�ر�����LED
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	GPIO_SetBits(GPIOF, GPIO_Pin_7|GPIO_Pin_8);
}
