#include "gear.h"

void Gear_Init(void)
{
	TIM2_PWM_Init(39999,35); //使用定时器2的通道3,PB10
	TIM_SetCompare3(TIM2,3000);//初始化时旋转角度为0
}

void Gear_Angle(int angle)
{
	int time2ch1cmp;
	angle = angle + 90;               //将(-90) - 90的域量化
	time2ch1cmp = 1000 + angle * 4000 / 180; //到1000 - 5000的域
	TIM_SetCompare3(TIM2,time2ch1cmp); 
}
