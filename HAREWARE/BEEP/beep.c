#include "beep.h"

/************************************************
���ܣ���������ʼ�����򿪹رպ���
************************************************/

//==============================================================
//������������ʼ��������
//��������
//���أ���
//==============================================================
void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PBʱ��
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;     //PE8
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶ�50MHz
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);   //Ĭ������͵�ƽ/�������ر�
}

//==============================================================
//�����������򿪷�����
//��������
//���أ���
//==============================================================
void BEEP_Open(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_8);   //����ߵ�ƽ/��������
}

//==============================================================
//�����������رջ�������
//��������
//���أ���
//==============================================================
void BEEP_Close(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);   //����͵�ƽ/�������ر�
}
