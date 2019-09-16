
/*2018��718���ܳ�����Ѱ������*/


/*
delay.h: ��ʱͷ�ļ�
track.h: ѭ�������ͷ�ļ�
carset.h:�������������Թܵ�����ͷ�ļ�
menu.h:  �˵�ͷ�ļ�
oled.h:  oled��ͷ�ļ�
*/

#include "stm32f10x.h"
#include "delay.h"
#include "track.h"
#include "carset.h"
#include "menu.h"
#include "oled.h"
#include "usart.h"
#include "TIM.h"
#include "serialport.h"


extern double K_basic;	                                     //��������.c�ļ��ı���
extern double K_turn;
extern double DelayCC;
extern double BS;

int control=1;  //С��Ѱ��ģʽ�͵���ģʽ��־λ
int T_CROSS=0;

void EXTI2_IRQHandler(void)
{
	delay_ms(10);                                                //����
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0)
	{
		control+=1;                                               //�л�ģʽ
	}
	EXTI_ClearITPendingBit(EXTI_Line2);                          //��� LINE2 �ϵ��жϱ�־λ
}

int main()
{
	GPIO_servo_init();                                         //����˿ڳ�ʼ��
	TIM_servo_init(1000);                                      //�����ʱ����ʼ��
	delay_init();			    //��ʱ��ʼ��
	
	while (1)
	{
		  TIM_SetCompare3(TIM3,900);
			//Tracking(GetError());	                                  //ѭ�����庯��
	    ProcessInfo(&g_serialinfo);	
	
		
 }
}

//�����жϺ�����ÿ��һ��Key2�л�һ��ģʽ��־λ
//�л���Ѱ��������Ҫ������һ������Key2��������oled�˵��е��quit�˳������˳�Menu_ShowPar()��


 

