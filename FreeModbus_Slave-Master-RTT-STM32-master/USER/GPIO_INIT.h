#include "stm32f10x.h"
#include "user_mb_app.h"

void GPIO_INIT(void);


//   DI输入定义

#define DI_Channel_0 GPIOD,GPIO_Pin_0
#define DI_Channel_1 GPIOD,GPIO_Pin_1
#define DI_Channel_2 GPIOD,GPIO_Pin_2
#define DI_Channel_3 GPIOD,GPIO_Pin_3
#define DI_Channel_4 GPIOD,GPIO_Pin_4
#define DI_Channel_5 GPIOD,GPIO_Pin_5
#define DI_Channel_6 GPIOD,GPIO_Pin_6
#define DI_Channel_7 GPIOD,GPIO_Pin_7
#define DI_Channel_8 GPIOD,GPIO_Pin_8
#define DI_Channel_9 GPIOD,GPIO_Pin_9
#define DI_Channel_10 GPIOD,GPIO_Pin_10
#define DI_Channel_11 GPIOD,GPIO_Pin_11
#define DI_Channel_12 GPIOD,GPIO_Pin_12
#define DI_Channel_13 GPIOD,GPIO_Pin_13
#define DI_Channel_14 GPIOD,GPIO_Pin_14
#define DI_Channel_15 GPIOD,GPIO_Pin_15
#define DI_Channel_16 GPIOE,GPIO_Pin_0
#define DI_Channel_17 GPIOE,GPIO_Pin_1
#define DI_Channel_18 GPIOE,GPIO_Pin_2
#define DI_Channel_19 GPIOE,GPIO_Pin_3
#define DI_Channel_20 GPIOE,GPIO_Pin_4
#define DI_Channel_21 GPIOE,GPIO_Pin_5
#define DI_Channel_22 GPIOE,GPIO_Pin_6
#define DI_Channel_23 GPIOE,GPIO_Pin_7

// DO 输出定义

#define DO_Channel_0 GPIOE,GPIO_Pin_8
#define DO_Channel_1 GPIOE,GPIO_Pin_9
#define DO_Channel_2 GPIOE,GPIO_Pin_10
#define DO_Channel_3 GPIOE,GPIO_Pin_11
#define DO_Channel_4 GPIOE,GPIO_Pin_12
#define DO_Channel_5 GPIOE,GPIO_Pin_13
#define DO_Channel_6 GPIOE,GPIO_Pin_14
#define DO_Channel_7 GPIOE,GPIO_Pin_15
#define DO_Channel_8 GPIOF,GPIO_Pin_0
#define DO_Channel_9 GPIOF,GPIO_Pin_1
#define DO_Channel_10 GPIOF,GPIO_Pin_2
#define DO_Channel_11 GPIOF,GPIO_Pin_3
#define DO_Channel_12 GPIOF,GPIO_Pin_4
#define DO_Channel_13 GPIOF,GPIO_Pin_5
#define DO_Channel_14 GPIOF,GPIO_Pin_6
#define DO_Channel_15 GPIOF,GPIO_Pin_7

void DO_OUT(void);


extern uint16_t ucSCoilBuf[];
