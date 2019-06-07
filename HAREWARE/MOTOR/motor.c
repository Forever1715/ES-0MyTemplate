#include "motor.h"

void Motor_Init()
{
	TIM5_PWM_Init(199,71);
	TIM_SetCompare3(TIM5,0);//≥ı ºŒﬁPWM
	TIM_SetCompare4(TIM5,0);//
}

void Motor_Left()
{
	
}

void Motor_Right()
{
	
}
