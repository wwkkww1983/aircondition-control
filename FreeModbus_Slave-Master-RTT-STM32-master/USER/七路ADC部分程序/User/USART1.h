#include "stm32f10x.h"
#include "stdio.h"
#define USART1_DR_Base 0x40013804
#define SENDBUFF_SIZE 5000
extern uint8_t SendBuff[SENDBUFF_SIZE];
void USART1_Config(void);
int fputc(int ch, FILE *f);
void DMA_Config(void);
