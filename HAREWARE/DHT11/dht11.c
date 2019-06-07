#include "Global.h"

#define DHT11_GPIOx GPIOA
#define DHT11_Pin_x GPIO_Pin_1




u8 g_TRHData[5] = {0x00,0x00,0x00,0x00,0x00}; //�����ʪ������


//ժ��P10����ñ
void dht11_gpio_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PAʱ��
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������ģʽ
	GPIO_InitStructure.GPIO_Pin = DHT11_Pin_x;     //PA1
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶ�50MHz
	GPIO_Init(DHT11_GPIOx,&GPIO_InitStructure);
	GPIO_SetBits(DHT11_GPIOx,DHT11_Pin_x);   //Ĭ������ߵ�ƽ���ȴ����뿪���ź�
}

void dht11_gpio_outhigh()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������ģʽ
	GPIO_InitStructure.GPIO_Pin = DHT11_Pin_x;     //PA1
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶ�50MHz
	GPIO_Init(DHT11_GPIOx,&GPIO_InitStructure);
	GPIO_SetBits(DHT11_GPIOx,DHT11_Pin_x);   //Ĭ������ߵ�ƽ���ȴ����뿪���ź�
}

void dht11_gpio_outlow()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������ģʽ
	GPIO_InitStructure.GPIO_Pin = DHT11_Pin_x;     //PA1
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶ�50MHz
	GPIO_Init(DHT11_GPIOx,&GPIO_InitStructure);
	GPIO_ResetBits(DHT11_GPIOx,DHT11_Pin_x);   //Ĭ������ߵ�ƽ���ȴ����뿪���ź�
}


void dht11_gpio_inhigh()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //�������ģʽ
	GPIO_InitStructure.GPIO_Pin = DHT11_Pin_x;     //PA1
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶ�50MHz
	GPIO_Init(DHT11_GPIOx,&GPIO_InitStructure);
}

void dht11_gpio_inlow()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //�������ģʽ
	GPIO_InitStructure.GPIO_Pin = DHT11_Pin_x;     //PA1
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶ�50MHz
	GPIO_Init(DHT11_GPIOx,&GPIO_InitStructure);
}

void DHT11_Init()
{
	delay_init();
	dht11_gpio_Init();
}

int DHT11_Read()
{
	int i,j,read_state = 0;
	DHT11_OUT_LOW;
	delay_ms(25);
	DHT11_OUT_HIGH;
	delay_us(30);
	DHT11_IN_HIGH;
	while(DHT11_IN_LEVEL);
	if(!DHT11_IN_LEVEL)
	{				
		while(!DHT11_IN_LEVEL);
		while(DHT11_IN_LEVEL);
		for(i = 0; i < 5; i++)
    {
			g_TRHData[i] = 0;
			for(j = 7; j >= 0; j--)
			{
				while(DHT11_IN_LEVEL);
				while(!DHT11_IN_LEVEL);
				delay_us(50);
				if(!DHT11_IN_LEVEL)
				{
				g_TRHData[i] &= ~(1<<j);
				}
				else
				{
					g_TRHData[i] |= (1<<j);
				}
			}
    }
		while(!DHT11_IN_LEVEL);
    i = g_TRHData[0] + g_TRHData[1] + g_TRHData[2] + g_TRHData[3];
    if(i == g_TRHData[4])
		{
      read_state = 1;
		}
	}
	return read_state;
}


//���ü��Ӧ����2s
float DHT11_Get_T(void)
{
	if(DHT11_Read())
	{
		if(0 != g_TRHData[4])
		{
			return g_TRHData[2]+g_TRHData[3]/10;
		}
	}
	return 0;
}

//Ӧ����get_Tһͬʹ��
float DHT11_Get_RH(void)
{
	if(0 != g_TRHData[4])
	{
		return 0;
	}
	return g_TRHData[0];
}
