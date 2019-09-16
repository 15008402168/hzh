#include "led.h"
#include "TIM.h"

uint16_t Light_Val = 0;

/**
  * @brief  LED��ʼ��
  * @param  Led��LED�ƣ�LED1 - LED3��
  * @retval ��
  * @example Led_Init(LED1);
  */
void Led_Init(LED Led)
{
	if(Led==LED1)
	{
		GPIO_InitTypeDef  GPIO_InitStructure;	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOE ,&GPIO_InitStructure);
	}
	else if(Led==LED2)
	{
		GPIO_InitTypeDef  GPIO_InitStructure;	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOE ,&GPIO_InitStructure);
	}
	else if(Led==LED3)
	{
		GPIO_InitTypeDef  GPIO_InitStructure;	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOE ,&GPIO_InitStructure);
	}
	else if(Led==LED_ALL)
	{
		GPIO_InitTypeDef  GPIO_InitStructure;	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOE ,&GPIO_InitStructure);
	}
}

/**
  * @brief  ����LED״̬
  * @param  Led��LED�ƣ�LED1 - LED3��
  * @param  State�� ���õ�״̬��0��1��
  * @retval ��
  * @example Led_Init(LED1,1);
  */
void Led_Set(LED Led, uint8_t State)
{
	if(Led==LED1)
	{
		if(State==0)
			GPIO_ResetBits(GPIOE,GPIO_Pin_4);
		else if(State==1)
			GPIO_SetBits(GPIOE,GPIO_Pin_4);
	}
	else if(Led==LED2)
	{
		if(State==0)
			GPIO_ResetBits(GPIOE,GPIO_Pin_3);
		else if(State==1)
			GPIO_SetBits(GPIOE,GPIO_Pin_3);
	}
	else if(Led==LED3)
	{
		if(State==0)
			GPIO_ResetBits(GPIOE,GPIO_Pin_5);
		else if(State==1)
			GPIO_SetBits(GPIOE,GPIO_Pin_5);
	}
	else if(Led==LED_ALL)
	{
		if(State==0)
			GPIO_ResetBits(GPIOE,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);
		else if(State==1)
			GPIO_SetBits(GPIOE,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);
	}
}
const uint16_t MAXCOLORVALUE = GENERAL_TIM_Period;	//RGBֵ�����õ����ֵ��

/**
  * @brief	����RGB�Ƶ�R��G��B��ֵ
  *	@param	Red: R��ֵ
  *	@param  Green: G��ֵ
  *	@param  Blue: B��ֵ
  *	@retval ��
  */
void Set_RGB_Value(uint16_t Red, uint16_t Green, uint16_t Blue)
{
	//����R��G��B��ֵ���������ֵ
	if(Red > MAXCOLOR_VALUE)
		Red = MAXCOLOR_VALUE;
	if(Green > MAXCOLOR_VALUE)
		Green = MAXCOLOR_VALUE;
	if(Blue > MAXCOLOR_VALUE)
		Blue = MAXCOLOR_VALUE;
	
	//�ı�PWMֵ
	TIM_SetCompare4(ADVANCED_TIM, MAXCOLOR_VALUE - Red);
	TIM_SetCompare3(ADVANCED_TIM, MAXCOLOR_VALUE - Green);
	TIM_SetCompare4(GENERAL_TIM, MAXCOLOR_VALUE  - Blue);
}
