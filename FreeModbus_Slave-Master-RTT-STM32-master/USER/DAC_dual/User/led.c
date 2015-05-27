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
	//定义一个GPIO_InitTypeDef类型的结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructuree;
	//开启GPIOC的外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
	//选择要控制的GPIO引脚
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_0;
	GPIO_InitStructuree.GPIO_Pin=GPIO_Pin_7 | GPIO_Pin_8;
	//设置引脚模式为通用推挽输出
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_InitStructuree.GPIO_Mode =GPIO_Mode_Out_PP;
	//设置引脚速率为50MHZ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructuree.GPIO_Speed = GPIO_Speed_50MHz;
	//调用库函数，初始化GPIOC
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_Init(GPIOF,&GPIO_InitStructuree);
	//关闭所有LED
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	GPIO_SetBits(GPIOF, GPIO_Pin_7|GPIO_Pin_8);
}
