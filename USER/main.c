#include "Global.h"
#include "lcd.h"
#include "math.h"
//#include "oled.h"
//#include "exfuns.h"
//#include "malloc.h"

/************************************************
 ALIENTEK ս��STM32F103������ʵ��0
 ����ģ��
 ע�⣬�����ֲ��е��½������½�ʹ�õ�main�ļ� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
#define TableOn11 GPIO_SetBits(GPIOA,GPIO_Pin_0)
#define TableOn12 GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define TableOn13 GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define TableOn14 GPIO_SetBits(GPIOA,GPIO_Pin_3)
//PA0 1 2 3
#define TableOn21 GPIO_SetBits(GPIOC,GPIO_Pin_0)
#define TableOn22 GPIO_SetBits(GPIOC,GPIO_Pin_1)
#define TableOn23 GPIO_SetBits(GPIOC,GPIO_Pin_2)
#define TableOn24 GPIO_SetBits(GPIOC,GPIO_Pin_3)
//PC0 1 2 3 
#define TableOn31 GPIO_SetBits(GPIOC,GPIO_Pin_4)
#define TableOn32 GPIO_SetBits(GPIOC,GPIO_Pin_5)
#define TableOn33 GPIO_SetBits(GPIOC,GPIO_Pin_6)
#define TableOn34 GPIO_SetBits(GPIOC,GPIO_Pin_7)
//PC4 5 6 7
#define TableOn41 GPIO_SetBits(GPIOC,GPIO_Pin_8)
#define TableOn42 GPIO_SetBits(GPIOC,GPIO_Pin_9)
#define TableOn43 GPIO_SetBits(GPIOC,GPIO_Pin_10)
#define TableOn44 GPIO_SetBits(GPIOC,GPIO_Pin_11)
//PC8 9 10 11
#define TableOn51 GPIO_SetBits(GPIOC,GPIO_Pin_12)
#define TableOn52 GPIO_SetBits(GPIOC,GPIO_Pin_13)
#define TableOn53 GPIO_SetBits(GPIOG,GPIO_Pin_7)
#define TableOn54 GPIO_SetBits(GPIOG,GPIO_Pin_8)
//PC12 13 PG7 8 

//�ֱ��Ӧ�����ƵĿ���IO
GPIO_TypeDef* PowerOnGPIOx[21]={0,GPIOG,GPIOA,GPIOA,GPIOA,GPIOC,GPIOC,GPIOC,GPIOC,GPIOC,GPIOC,GPIOC,GPIOC,GPIOC,GPIOC,GPIOC,GPIOC,GPIOE,GPIOE,GPIOE,GPIOG};
uint16_t PowerOnPinx[21]={0,GPIO_Pin_15,GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3,GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3,GPIO_Pin_4,GPIO_Pin_5,
														GPIO_Pin_6,GPIO_Pin_7,GPIO_Pin_8,GPIO_Pin_9,GPIO_Pin_10,GPIO_Pin_11,GPIO_Pin_2,GPIO_Pin_3,GPIO_Pin_4,GPIO_Pin_13};

void ZutaiGPIO_Init(void)
{
	u8 i;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //GPIOC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE); //GPIOG
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE); //GPIOG
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
//	GPIO_Init(GPIOC,&GPIO_InitStructure);
//	GPIO_ResetBits(GPIOC,GPIO_Pin_0);
	for(i=1;i<=20;i++)
	{
	GPIO_InitStructure.GPIO_Pin = PowerOnPinx[i];
	GPIO_Init(PowerOnGPIOx[i],&GPIO_InitStructure);
	GPIO_ResetBits(PowerOnGPIOx[i],PowerOnPinx[i]);
		delay_ms(10);
	}
}

int main()
{
	u32 key,port = 0,port_temp = 0;
	u32 TableStatus=0, TableStatus_pre = 0;
	int i=1,j=0;
	u8 port_str[6] = {'1','\0'};
	uart_init(9600);
	usart3_init(115200);		//��ʼ������3 
	//DHT11_Init();
	delay_init();
	//LCD_Init();
	LCD_DisplayOn();
	//LED_Init();
	ZutaiGPIO_Init();
	//LCD_Init();
	//LCD_DisplayOff();
	//KEY_Init();
	RC522_Init();       //��ʼ����Ƶ��ģ��
	 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"TOUCH TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/15");
	while(1)
	{
		///ˢ��������
		RC522_Handel();
		delay_ms(300);

		///��ȡTable����
		u3_printf("Read\r\n");
		delay_ms(300); //�ȴ����ݷ���
		///�������յ�������
		if(USART3_RX_STA&1<<15)
		{
			
			i = 0;
			j = 0;
			while(USART3_RX_BUF[i]!='\0')
			{
				i++;
			}
			TableStatus = 0;
			while(i > 0)
			{
				if(USART3_RX_BUF[0]=='O') 
				{
					TableStatus=TableStatus_pre;
					USART3_RX_BUF[0]=USART3_RX_BUF[1]=USART3_RX_BUF[2]=USART3_RX_BUF[3]=USART3_RX_BUF[4]='\0';
					break;
				}
				i--;
				TableStatus = TableStatus + (USART3_RX_BUF[j]-0x30) * pow(10,i);
				USART3_RX_BUF[j++] = '\0';
			}
			USART3_RX_STA = 0;
			LCD_ShowxNum(1,1,TableStatus,8,16,(1<<7));
			
		}
		
		///ִ�е�������
		if(TableStatus!=TableStatus_pre)
		{
			for(i=1; i<=20; i++)
			{
				if(TableStatus&(1<<i))
				{
					//Table On
					LED0_On;
					//GPIO_SetBits(GPIOC,GPIO_Pin_0);
					GPIO_SetBits(PowerOnGPIOx[i],PowerOnPinx[i]);
				}
				else
				{
					//Table Off
					LED1_On;
					GPIO_ResetBits(PowerOnGPIOx[i],PowerOnPinx[i]);
				}
			}
			TableStatus_pre = TableStatus;
		}

		///����
		key = KEY_Scan(0);
		if(key)
		{
			switch(key)
			{
				case WKUP_PRES:
				{
					//�˴�д��WKUP������ʱ��Ҫ��������			
					break;
				}
			  case KEY0_PRES:
				{
					GPIO_SetBits(GPIOC,GPIO_Pin_12);
					//�˴�д��KEY0������ʱ��Ҫ��������
					//printf("%s","A0F016475\r");
					break;
				}
				case KEY1_PRES:
				{
					//�˴�д��KEY1������ʱ��Ҫ��������
					port+=1;
					break;
				}
				case KEY2_PRES:
				{
					//�˴�д��KEY2������ʱ��Ҫ��������
					port+=2;
					break;
				}
			}//switch(key)
		}//if(key)
	}
}
