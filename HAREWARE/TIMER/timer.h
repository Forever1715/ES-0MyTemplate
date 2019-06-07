#ifndef __TIMER_H
#define __TIMER_H

#include "Global.h"

void TIM3_Normal_Init(u16 period, u16 prescaler); //计数器TOP值,预分频 (ARR,PSC) //TimeOut = (perid+1)(prescaler+1)/Tclk
void TIM3_PWM_Init(u16 period, u16 prescaler);  //计数器TOP值,预分频 (ARR,PSC) 
void TIM2_PWM_Init(u16 period, u16 prescaler);  //计数器TOP值,预分频 (ARR,PSC)
void TIM7_Int_Init(u16 period, u16 prescaler);   
void TIM5_PWM_Init(u16 period, u16 prescaler);  //计数器TOP值,预分频 (ARR,PSC)
#endif
