#include "key.h"


//==============================================================
//功能描述：按键初始化，使用前必须进行初始化
//参数：无
//返回：无
//==============================================================
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	delay_init(); //使用按键时需要初始化延迟函数
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA,ENABLE);//使能PE/PA时钟
	

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //下拉输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;     //PA0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //速度50MHz
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;     //PE2/PE3/PE4
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //速度50MHz
	GPIO_Init(GPIOE,&GPIO_InitStructure);
}


//==============================================================
//功能描述：当需要使用按键时，将此程序复制到main函数中使用
//参数：Mood:/1-支持连续按下检测 /0-不支持连续按下检测
//返回：u8类型，返回各按键状态
//==============================================================
u8 KEY_Scan(u8 Mood) //1-支持连续按下 /0-不支持连续扫描
{
	static u8 key_up = 1; //记录上次按键状态
	if(Mood) key_up = 1; //支持连续按下
	if(key_up && (WK_UP == 1 || KEY0 == 0 || KEY1 == 0 || KEY2 == 0))
	{
		key_up = 0;
		delay_ms(10);
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1)  return WKUP_PRES;    //返回WKUP键按下
		else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) == 0) return KEY2_PRES; //返回KEY2键按下
		else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) == 0) return KEY1_PRES; //返回KEY1键按下
		else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) == 0) return KEY0_PRES; //返回KEY0键按下
	}
	else if(WK_UP == 0 && KEY0 == 1 && KEY1 == 1 && KEY2 == 1) key_up = 1;
	return 0;
}


void KEY_Multi_Scan(u8 Mood, u8 *Key_Result) //1-支持连续按下 /0-不支持连续扫描
{
	static u8 key_up = 1; //记录上次按键状态
	if(Mood) key_up = 1; //支持连续按下
	if(key_up)
	{
		if(WK_UP == 1 || KEY0 == 0 || KEY1 == 0 || KEY2 == 0)
		{
			Key_Result[0] = 1;
			key_up = 0;       //只能进入一次
			delay_ms(10);
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1)  Key_Result[WKUP_PRES] = 1;    //返回WKUP键按下
			else Key_Result[WKUP_PRES] = 0;
			if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) == 0) Key_Result[KEY2_PRES] = 1; //返回KEY2键按下
			else Key_Result[KEY2_PRES] = 0;
			if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) == 0) Key_Result[KEY1_PRES] = 1; //返回KEY1键按下
			else Key_Result[KEY1_PRES] = 0;
			if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) == 0) Key_Result[KEY0_PRES] = 1; //返回KEY0键按下
			else Key_Result[KEY0_PRES] = 0;
		}

	}
	else
	{
		Key_Result[0] = 0;
		if(WK_UP == 0 && KEY0 == 1 && KEY1 == 1 && KEY2 == 1) 
		{
			key_up = 1; //所有按键释放时key_up复位，等待下次按键按下
		}
	}
}



//==============================================================
//功能描述：当需要使用按键时，将此程序复制到main函数中使用
//参数：需要在main中定义u8 key
//返回：无
//==============================================================
int KEY_main(void)
{
	u8 key;
	while(1)
	{
		key = KEY_Scan(0);
		if(key)
		{
			
			switch(key)
			{
				case WKUP_PRES:
				{
					//此处写入WKUP被按下时需要处理内容
					break;
				}
			  case KEY0_PRES:
				{
					//此处写入KEY0被按下时需要处理内容
					break;
				}
				case KEY1_PRES:
				{
					//此处写入KEY1被按下时需要处理内容
				}
				case KEY2_PRES:
				{
					//此处写入KEY2被按下时需要处理内容
						break;
				}
			}//switch(key)
		}//if(key)
	}//while(1)
}
