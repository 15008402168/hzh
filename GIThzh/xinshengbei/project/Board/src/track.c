
#include "stm32f10x.h"
#include "track.h"
#include "usart.h"
#include "delay.h"
//#define GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) g11;
//#define GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12) g12;
//#define GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13) g13;
//#define GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) g14;
//#define GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15) g15;



double K_basic=5;      //��������ٶȵĲ���,itsincrease'll set'error'greater influence on Speed Basic
double K_turn=7;	                                  //��������ٶ�
int    BlackNumber=0;	                              //�жϵ����ߵĹ��Թܸ���
int    error_ago=0;	//��һ�ε����
double    DelayCC=5000;
double BS=400;

//�������


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


//ѭ���ж� ��·���Թ�
int GetError(void)
{
	extern int T_CROSS;
	int temp=0,error=0;                                //�������
	BlackNumber=0;
	                                                   
	if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==1)   //�м�Ĺ��Թܼ�⵽����ʱ������
		{
		temp+=0; 			//�м�
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
	
	if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==1)   //�ұߵ�һ�������м����������Ĺ��Թܼ�⵽����ʱ����10
		{
		// T_CROSS+=1;                                       //��С
		if((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==1)&&(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1))
			BlackNumber+=0; 
    else
		{
			temp+=30;
      BlackNumber+=1;
		}
		}
	
	if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==1)   //�ұߵڶ��������м����������Ĺ��Թܼ�⵽����ʱ����30
		{			//�Ҵ�
		if((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==1)&&(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1))
			BlackNumber+=0; 
    else
		{
			temp+=55; 
      BlackNumber+=1;		
		}
		}
	
	if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1)   //��ߵ�һ�������м����������Ĺ��Թܼ�⵽����ʱ����10
		{
		//T_CROSS+=1;                                   //��С
		if((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==1)&&(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==1))
			BlackNumber+=0; 
    else
		{
			temp+=(-1)*30;
      BlackNumber+=1;			
		}
		}
	
	if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==1)   //��ߵڶ��������м����������Ĺ��Թܼ�⵽����ʱ����30
		{                                                          
		                                   //���
		if((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==1)&&(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==1))
			BlackNumber+=0; 
    else
		{ 
			temp+=(-1)*55;
      BlackNumber+=1;	
		}
		}
	if (BlackNumber==0)                                //û�й���⵽����
		error=error_ago;	                               //����֮ǰ�������
	
	else
	{
		error=temp/BlackNumber;	                         //�������������ʹ��Լ�⵽���ߵĹ��Թ���
		error_ago=error;				                         //�����ϴ����
	}
	
	return error;
}

//ѭ������
void Tracking(int error)
{	
	extern int T_CROSS;
	
	int Speed_Basic=400;                               //�����ٶ�,itsdecrease'll slow down the motor on the whole
	int Speed_Turn=0;	                                 //ת���ٶ�
	int Speed_LeftWheel=0;	                           //�����ٶ�
	int Speed_RightWheel=0;                           	//�����ٶ�
	
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
	
	if (error<0)	                                     //�����������Ҫת��������ٶȽ���
		Speed_Basic=BS+error*K_basic;
	else
		Speed_Basic=BS-error*K_basic;
	
	Speed_Turn=error*K_turn;                           //����ת�����
	Speed_LeftWheel=Speed_Basic+Speed_Turn;		         //����������ʵ���ٶ�
	Speed_RightWheel=Speed_Basic-Speed_Turn;
	if(out_left+out_right==0)
	{
		if(T_CROSS==1)
		{
			MotorRun(600,-1);
			delay_ms(100);
			T_CROSS=4;
		}
 	MotorRun(Speed_RightWheel,Speed_LeftWheel);	//�����Ӧ�ź�
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



//������ƺ��� ��е�۵��ſ��͹ر�
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