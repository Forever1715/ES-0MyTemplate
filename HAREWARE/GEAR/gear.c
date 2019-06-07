#include "gear.h"

void Gear_Init(void)
{
	TIM2_PWM_Init(39999,35); //ʹ�ö�ʱ��2��ͨ��3,PB10
	TIM_SetCompare3(TIM2,3000);//��ʼ��ʱ��ת�Ƕ�Ϊ0
}

void Gear_Angle(int angle)
{
	int time2ch1cmp;
	angle = angle + 90;               //��(-90) - 90��������
	time2ch1cmp = 1000 + angle * 4000 / 180; //��1000 - 5000����
	TIM_SetCompare3(TIM2,time2ch1cmp); 
}
