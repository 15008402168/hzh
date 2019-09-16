
/*2018年718智能车基础寻迹程序*/


/*
delay.h: 延时头文件
track.h: 循迹程序的头文件
carset.h:电机，舵机，光电对管的配置头文件
menu.h:  菜单头文件
oled.h:  oled的头文件
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


extern double K_basic;	                                     //调用其他.c文件的变量
extern double K_turn;
extern double DelayCC;
extern double BS;

int control=1;  //小车寻迹模式和调参模式标志位
int T_CROSS=0;

void EXTI2_IRQHandler(void)
{
	delay_ms(10);                                                //消抖
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0)
	{
		control+=1;                                               //切换模式
	}
	EXTI_ClearITPendingBit(EXTI_Line2);                          //清除 LINE2 上的中断标志位
}

int main()
{
	GPIO_servo_init();                                         //舵机端口初始化
	TIM_servo_init(1000);                                      //舵机定时器初始化
	delay_init();			    //延时初始化
	
	while (1)
	{
		  TIM_SetCompare3(TIM3,900);
			//Tracking(GetError());	                                  //循迹主体函数
	    ProcessInfo(&g_serialinfo);	
	
		
 }
}

//按键中断函数，每按一次Key2切换一次模式标志位
//切换到寻迹程序需要两步：一、按下Key2，二、在oled菜单中点击quit退出（即退出Menu_ShowPar()）


 

