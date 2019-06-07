#ifndef __LED_H
#define __LED_H

#include "Global.h"

#define LED0_State !GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5)
#define LED1_State !GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_5)
#define LED0_On GPIO_ResetBits(GPIOB,GPIO_Pin_5)
#define LED1_On GPIO_ResetBits(GPIOE,GPIO_Pin_5)
#define LED0_Off GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define LED1_Off GPIO_SetBits(GPIOE,GPIO_Pin_5)


void LED_Init(void);

#endif

