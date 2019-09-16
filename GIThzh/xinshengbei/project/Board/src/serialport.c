#include "serialport.h"
#include "usart.h"
#include "track.h"
#include "delay.h"


extern int control;

SerialPortInfo g_serialinfo = {0,0,0,0,0};

/*static void Print_Error()
{
	printf("If you see this, it means that you not change the code!\n");
}
*/
static void Process_Button(SerialPortInfo *info)
{
	int i;
	for(i=0; i<BUFFERSIZE; i++)
	{
		if(info->queuebuffer[i] == 'B' && i<BUFFERSIZE-1)
		{
			info->queuebuffer[i] = 0;	//清空
			switch(info->queuebuffer[i+1])
			{
				case '1':
					Button1_Event();break;
				case '2':
					Button2_Event();break;
				case '3':
					Button3_Event();break;
				case '4':
					Button4_Event();break;
				case '5':
					Button5_Event();break;		
				case '6':
					Button6_Event();break;				
			}
		}
	}
}

static void Process_Joystick(SerialPortInfo *info)
{
	int i;
	info->x_speed_old = info->x_speed;
	info->y_speed_old = info->y_speed;
	
	for(i=0; i<BUFFERSIZE; i++)
	{
		if(info->queuebuffer[i] == 'X' && i<BUFFERSIZE-1)
		{
			info->queuebuffer[i] = 0;
			if(info->queuebuffer[i+1] == '-')
			{
				if(info->queuebuffer[i+2] - '0' >=0 && info->queuebuffer[i+2] - '0' <=9)
				{
					info->x_speed = -(info->queuebuffer[i+2] - '0');
					if(info->queuebuffer[i+3] - '0' >=0 && info->queuebuffer[i+3] - '0' <=9)
					{
						info->x_speed = info->x_speed * 10 - (info->queuebuffer[i+3] - '0');
					}
				}
			}
			
			else if(info->queuebuffer[i+1] - '0' >=0 && info->queuebuffer[i+1] - '0' <=9)
			{
				info->x_speed = info->queuebuffer[i+1] - '0';
				if(info->queuebuffer[i+2] - '0' >=0 && info->queuebuffer[i+2] - '0' <=9)
				{
					info->x_speed = info->x_speed * 10 + (info->queuebuffer[i+2] - '0');
				}
			}
		}
		
		if(info->queuebuffer[i] == 'Y' && i<BUFFERSIZE-1)
		{
			info->queuebuffer[i] = 0;
			if(info->queuebuffer[i+1] == '-')
			{
				if(info->queuebuffer[i+2] - '0' >=0 && info->queuebuffer[i+2] - '0' <=9)
				{
					info->y_speed = -(info->queuebuffer[i+2] - '0');
					if(info->queuebuffer[i+3] - '0' >=0 && info->queuebuffer[i+3] - '0' <=9)
					{
						info->y_speed = info->y_speed * 10 - (info->queuebuffer[i+3] - '0');
					}
				}
			}
			
			else if(info->queuebuffer[i+1] - '0' >=0 && info->queuebuffer[i+1] - '0' <=9)
			{
				info->y_speed = info->queuebuffer[i+1] - '0';
				if(info->queuebuffer[i+2] - '0' >=0 && info->queuebuffer[i+2] - '0' <=9)
				{
					info->y_speed = info->y_speed * 10 + info->queuebuffer[i+2] - '0';
				}
			}
		}
	}
	//判断速度是否更新
	if(info->x_speed != info->x_speed_old || info->y_speed != info->y_speed_old)
	{
		Joystick_Event(info->x_speed, info->y_speed);
		info->x_speed = 0;
		info->y_speed = 0;
	}
}

/**
  *@brief 获得串口的信息
  *@params info 串口的信息
  *@retval None
  */
void Get_Serial_Info(unsigned char data, SerialPortInfo *info)
{
	int i=0;
	//队列移动
	for(; i<BUFFERSIZE-1; i++)
	{
		info->queuebuffer[i] = info->queuebuffer[i+1];
	}
	//添加信息到队尾
	info->queuebuffer[BUFFERSIZE-1] = data;
	info->flag = 1;	//队列发生更新
}

void ProcessInfo(SerialPortInfo *info)
{	
	if(info->flag == 1)
	{
		Process_Button(info);
		Process_Joystick(info);
		info->flag = 0;		//去除更新标记
	}
}

void Serial_Port_Init()
{
	USART_Config();
}

__weak void Button1_Event()
{
	printf("Servo Open\n");
	Servo_open();
}

__weak void Button2_Event()
{ 
	printf("Servo Close\n");
	Servo_close();
}

__weak void Button3_Event()
{
	printf("STOP\n");
	TIM_SetCompare1(TIM5,0);
  TIM_SetCompare2(TIM5,0);
	TIM_SetCompare4(TIM5,0);
	TIM_SetCompare3(TIM5,0);
}

__weak void Button4_Event()
{
	printf("BallOFF\n");
	Servo_OFF();
}

__weak void Button5_Event()
{
	printf("LeftTurn\n");
	MotorRun(350,-50);
}

__weak void Button6_Event()
{
	printf("RightTurn\n");
	MotorRun(-50,350);
}

__weak void Joystick_Event(int x, int y)
{
	int s=0;
	if(x>0&&y>0)
	{
		if(x>65&&y>65)
		{
			printf("BackFull");
			MotorRun(-1,-1);
		}
		else 
		{
		  s=0.5*(x+y);
		  MotorRun(5*s,5*s);
		}
	}
	else if(x>0&&y<0)
	{
		MotorRun(400,400);
			delay_ms(500);
		control=0;}
	else if(x<0&&y>0)
		control=1;
	else 
		MotorRun(0,0);
	printf("x: %d, y: %d, s: %d\n", x, y, s);
}

