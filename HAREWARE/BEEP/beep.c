#include "beep.h"

/************************************************
功能：蜂鸣器初始化及打开关闭函数
************************************************/

//==============================================================
//功能描述：初始化蜂鸣器
//参数：无
//返回：无
//==============================================================
void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PB时钟
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;     //PE8
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //速度50MHz
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);   //默认输出低电平/蜂鸣器关闭
}

//==============================================================
//功能描述：打开蜂鸣器
//参数：无
//返回：无
//==============================================================
void BEEP_Open(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_8);   //输出高电平/蜂鸣器打开
}

//==============================================================
//功能描述：关闭化蜂鸣器
//参数：无
//返回：无
//==============================================================
void BEEP_Close(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);   //输出低电平/蜂鸣器关闭
}
