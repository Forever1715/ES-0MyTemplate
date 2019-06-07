#include "timer.h"
//==============================================================
//功能描述：Timer2 Channel3初始化，PWM模式
//参数：//计数器TOP值,预分频 (ARR,PSC)
//返回：无
//==============================================================
void TIM2_PWM_Init(u16 period, u16 prescaler)  //计数器TOP值,预分频 (ARR,PSC)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeStruct;
	TIM_OCInitTypeDef TIM_OCInitTypeStruct;
	
	//部分重映射
	GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2,ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //使能定时器5时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
		
	//使能端口PB10
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //GPIOB PB10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//初始化TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//TIM2时钟使能
	TIM_TimeBaseInitTypeStruct.TIM_Period = period;
	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = prescaler;
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up; //上行计数
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitTypeStruct); //TIM2初始化
	
	//初始化TIM2 Channel3 PWM2
	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM2; //CNT>CCR有效
	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_Low;  //输出极性低电平
	TIM_OC3Init(TIM2,&TIM_OCInitTypeStruct);
	
	//使能TIM2 Channel3预装载寄存器
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_Cmd(TIM2,ENABLE);
}


//==============================================================
//功能描述：Timer3初始化，普通模式
//参数：//计数器TOP值,预分频 (ARR,PSC)
//返回：无
//==============================================================
void TIM3_Normal_Init(u16 period, u16 prescaler)  //计数器TOP值,预分频 (ARR,PSC)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeStruct;
	NVIC_InitTypeDef NVIC_InitTypeStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//TIM3时钟使能
	TIM_TimeBaseInitTypeStruct.TIM_Period = period;
	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = prescaler;
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up; //上行计数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitTypeStruct); //TIM3初始化
	
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //更新中断(溢出)使能 TimeOut = (perid+1)(prescaler+1)/Tclk 
	NVIC_InitTypeStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitTypeStruct); //优先级设置
	
	TIM_Cmd(TIM3,ENABLE);
}

//==============================================================
//功能描述：Timer3 Channel2初始化，PWM模式
//参数：//计数器TOP值,预分频 (ARR,PSC)
//返回：无
//注意：使用TIM_SetCompare2(TIM3,6000);改变占空比
//==============================================================
void TIM3_PWM_Init(u16 period, u16 prescaler)  //计数器TOP值,预分频 (ARR,PSC)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeStruct;
	TIM_OCInitTypeDef TIM_OCInitTypeStruct;
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //使能定时器3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	//部分重映射
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
	
	//使能端口PB5
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //GPIOB PB5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//初始化TIM3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//TIM3时钟使能
	TIM_TimeBaseInitTypeStruct.TIM_Period = period;
	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = prescaler;
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up; //上行计数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitTypeStruct); //TIM3初始化
	
	//初始化TIM3 Channel2 PWM2
	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM2; //CNT>CCR有效
	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_High;  //输出极性高电平
	TIM_OC2Init(TIM3,&TIM_OCInitTypeStruct);
	
	//使能TIM3 Channel2预装载寄存器
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_Cmd(TIM3,ENABLE);
}



//==============================================================
//功能描述：Timer4 Channel1-2初始化，PWM模式
//参数：//计数器TOP值,预分频 (ARR,PSC)
//返回：无
//==============================================================
void TIM5_PWM_Init(u16 period, u16 prescaler)  //计数器TOP值,预分频 (ARR,PSC)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeStruct;
	TIM_OCInitTypeDef TIM_OCInitTypeStruct;
	
	//使能RCC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //使能定时器5时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//部分重映射
	//GPIO_PinRemapConfig(GPIO_Remap_TIM5,ENABLE);
	
	//使能端口PA2 PA3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //GPIOA PA2 PA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//初始化TIM5
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);//TIM5时钟使能
	TIM_TimeBaseInitTypeStruct.TIM_Period = period;
	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = prescaler;
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up; //上行计数
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitTypeStruct); //TIM5初始化
	
	//初始化TIM5 Channel3/Channel4 PWM2
	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM2; //CNT>CCR有效
	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_Low;  //输出极性低电平
	TIM_OC3Init(TIM5,&TIM_OCInitTypeStruct);
	TIM_OC4Init(TIM5,&TIM_OCInitTypeStruct);
	
	//使能TIM5 Channel3/Channel4 预装载寄存器
	TIM_OC3PreloadConfig(TIM5,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM5,TIM_OCPreload_Enable);
	TIM_Cmd(TIM5,ENABLE);
}

//==============================================================
//功能描述：通用定时器7中断初始化
//         Tout=((period+1)*(prescaler+1))/Ft us
//参数：//计数器TOP值,预分频 (ARR,PSC)
//返回：无
//==============================================================
void TIM7_Int_Init(u16 period,u16 prescaler)
{	
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);//TIM7时钟使能    
	
	//定时器TIM7初始化
	TIM_TimeBaseStructure.TIM_Period = period; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =prescaler; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE ); //使能指定的TIM7中断,允许更新中断
	
	TIM_Cmd(TIM7,ENABLE);//开启定时器7
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
}

extern vu16 USART3_RX_STA;


//==============================================================
//功能描述：Timer7中断服务函数
//参数：无
//返回：无
//==============================================================
void TIM7_IRQHandler(void)
{ 	
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)//是更新中断
	{	 			   
		USART3_RX_STA|=1<<15;	//标记接收完成
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );  //清除TIM7更新中断标志    
		TIM_Cmd(TIM7, DISABLE);  //关闭TIM7 
	}
}

//==============================================================
//功能描述：Timer3中断服务函数
//参数：无
//返回：无
//==============================================================
void TIM3_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM3,TIM_FLAG_Update))
	{
		/*Code*/
		if(LED0_State)
			LED0_Off;
		else
			LED0_On;
		/*End*/
		
		
		TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	}
}
