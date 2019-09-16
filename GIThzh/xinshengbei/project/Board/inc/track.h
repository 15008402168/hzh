#ifndef __TRACK_H
#define __TRACK_H

#include "stm32f10x.h"







void MotorRun(int speed1,int speed2);
void Tracking(int error);


int GetError(void);



void Servo_open(void);
void Servo_close(void);
void Servo_OFF(void);

#endif



