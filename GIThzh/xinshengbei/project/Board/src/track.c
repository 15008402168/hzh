
#include "stm32f10x.h"
#include "track.h"
#include "usart.h"
#include "delay.h"
//#define GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) g11;
//#define GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12) g12;
//#define GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13) g13;
//#define GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) g14;
//#define GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15) g15;



double K_basic=5;      //计算基础速度的参数,itsincrease'll set'error'greater influence on Speed Basic
double K_turn=7;	                                  //计算差速速度
int    BlackNumber=0;	                              //判断到黑线的光电对管个数
int    error_ago=0;	//上一次的误差
double    DelayCC=5000;
double BS=400;

//电机控制


void MotorRun(int speed1,int speed2)
{
	                                                  
	if(speed1>=0){
		TIM_SetCompare1(TIM5,0);
		TIM_SetCompare2(TIM5,speed1);
	}
	else{
		TIM_SetCompare1(TIM5,speed1);
		TIM_SetCompare2(TIM5,0);
	}
	
	if(speed2>=0){
		TIM_SetCompare4(TIM5,0);
		TIM_SetCompare3(TIM5,speed2);
	}
	else{
		TIM_SetCompare4(TIM5,speed2);
		TIM_SetCompare3(TIM5,0);
	}
}


//循迹判断 五路光电对管
int GetError(void)
{
	extern int T_CROSS;
	int temp=0,error=0;                                //本次误差
	BlackNumber=0;
	                                                   
	if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==1)   //中间的光电对管检测到黑线时误差不增加
		{
		temp+=0; 			//中间
		if((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==1)&&(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==1))	
		{
			BlackNumber+=0;
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0)
			T_CROSS+=1;
		}
    else if((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==1)&&(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1))		
		{
			BlackNumber+=0;
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==0)
			T_CROSS+=1;
		}
	/*	else if((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==1))
		{
			while (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)!=1)
				MotorRun(0,500);
		}
		else if((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==1))
		{
			while (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)!=1)
				MotorRun(500,0);
		}*/
		else
			BlackNumber+=1;
		}
	
	if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==1)   //右边第一个（从中间自右数）的光电对管检测到黑线时误差加10
		{
		// T_CROSS+=1;                                       //右小
		if((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==1)&&(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1))
			BlackNumber+=0; 
    else
		{
			temp+=30;
      BlackNumber+=1;
		}
		}
	
	if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==1)   //右边第二个（从中间自右数）的光电对管检测到黑线时误差加30
		{			//右大
		if((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==1)&&(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1))
			BlackNumber+=0; 
    else
		{
			temp+=55; 
      BlackNumber+=1;		
		}
		}
	
	if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1)   //左边第一个（从中间自左数）的光电对管检测到黑线时误差减10
		{
		//T_CROSS+=1;                                   //左小
		if((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==1)&&(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==1))
			BlackNumber+=0; 
    else
		{
			temp+=(-1)*30;
      BlackNumber+=1;			
		}
		}
	
	if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==1)   //左边第二个（从中间自左数）的光电对管检测到黑线时误差减30
		{                                                          
		                                   //左大
		if((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==1)&&(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==1))
			BlackNumber+=0; 
    else
		{ 
			temp+=(-1)*55;
      BlackNumber+=1;	
		}
		}
	if (BlackNumber==0)                                //没有光电检测到黑线
		error=error_ago;	                               //按照之前的误差跑
	
	else
	{
		error=temp/BlackNumber;	                         //本次误差等于误差和处以检测到黑线的光电对管数
		error_ago=error;				                         //更新上次误差
	}
	
	return error;
}

//循迹计算
void Tracking(int error)
{	
	extern int T_CROSS;
	
	int Speed_Basic=400;                               //基础速度,itsdecrease'll slow down the motor on the whole
	int Speed_Turn=0;	                                 //转向速度
	int Speed_LeftWheel=0;	                           //左轮速度
	int Speed_RightWheel=0;                           	//右轮速度
	
	int out_left=0;
	int out_right=0;
	
	
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==1)    //out_right
	{
		out_left=0;
		out_right=0;
		if((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0)&&(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==0))
		out_right=1;
	}
  if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==1)    //out_left
	{
		out_left=0;
		out_right=0;
		if((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==0)&&(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==0))
		out_left=-1;
	}
	
	if (error<0)	                                     //如果有误差，即需要转向，则基础速度降低
		Speed_Basic=BS+error*K_basic;
	else
		Speed_Basic=BS-error*K_basic;
	
	Speed_Turn=error*K_turn;                           //计算转向差速
	Speed_LeftWheel=Speed_Basic+Speed_Turn;		         //计算左右轮实际速度
	Speed_RightWheel=Speed_Basic-Speed_Turn;
	if(out_left+out_right==0)
	{
		if(T_CROSS==1)
		{
			MotorRun(600,-1);
			delay_ms(100);
			T_CROSS=4;
		}
 	MotorRun(Speed_RightWheel,Speed_LeftWheel);	//输出相应信号
	}
	else if(out_left+out_right==1)
	{
		MotorRun(-40,500);
		//delay_ms(15);
		
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)!=1)
		{
			MotorRun(-40,500);
		//delay_ms(650);
		}
	}	
  else if(out_left+out_right==-1)
	{
		MotorRun(500,-40);
		//delay_ms(15);

		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)!=1)
    {
			MotorRun(500,-40);
		//delay_ms(650);
		}
		
	}		
}	



//舵机控制函数 机械臂的张开和关闭
void Servo_open(void)
{
	TIM_SetCompare3(TIM3,1750);
}
void Servo_close(void)
{
	TIM_SetCompare3(TIM3,1100);
}
void Servo_OFF(void)
{
  TIM_SetCompare3(TIM3,1250);
}