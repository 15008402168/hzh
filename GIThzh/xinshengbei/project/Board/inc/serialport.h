#ifndef _SERIAL_PORT_H_
#define _SERIAL_PORT_H_

#include "stm32f10x.h"

#define BUFFERSIZE 20

typedef unsigned char queueinfo;

typedef enum
{
	Button1 = 1,
	Button2,
	Button3,
	Button4,
	Button5
	
}Buttonx_e;

typedef struct
{
	int x_speed;
	int y_speed;
	int x_speed_old;
	int y_speed_old;
	uint8_t flag;
	queueinfo queuebuffer[BUFFERSIZE + 4];	//串口信息队列, 防止发送大量信息导致信息丢失
}SerialPortInfo;


extern void Serial_Port_Init(void);
extern void Get_Serial_Info(unsigned char data, SerialPortInfo *info);
extern void ProcessInfo(SerialPortInfo *info);
extern __weak void Button1_Event(void);
extern __weak void Button2_Event(void);
extern __weak void Button3_Event(void);
extern __weak void Button4_Event(void);
extern __weak void Button5_Event(void);
extern __weak void Button6_Event(void);
extern __weak void Joystick_Event(int x, int y);

extern SerialPortInfo g_serialinfo;

#endif
