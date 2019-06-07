#ifndef __KEY_H
#define __KEY_H
#include "Global.h"

#define WKUP_PRES (4)  //WK_UP被按下
#define KEY2_PRES (3)  //KEY2被按下
#define KEY1_PRES (2)  //KEY1被按下
#define KEY0_PRES (1)  //KEY0被按下
#define WK_UP GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define KEY2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)

void KEY_Init(void);
u8 KEY_Scan(u8);
void KEY_Multi_Scan(u8 Mood, u8 *Key_Result);
#endif

