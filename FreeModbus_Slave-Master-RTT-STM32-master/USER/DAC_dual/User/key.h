#define KEY_ON 0
#define KEY_OFF 1
#include "stm32f10x.h"




void Key_GPIO_Config(void);
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);
