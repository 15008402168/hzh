#include "findtrack.h"

#ifndef __MOTOR_H__
#define __MOTOR_H__

#define  MotorControlPeriod   1     //电机控制值更新周期
#define  SteetControlPeriod   20    //舵机控制周期

#define  OpenLoop 1 //宏定义置1，速度开环控制
#define  CloseLoop 1 //宏定义置1，速度闭环控制
//#define USE_FULL_ASSERT


extern  int GetRightMotorPules;
extern  int GetLeftMotorPules;
extern  float Error;
extern  int   BlackEndM ; 
extern float  SteerPwmAdd;
extern  int32 SpeedSet;
extern int bizhangR,bizhangZ,bizhangS,bizhangJ,bizhangH;

extern void MotorInit(void);
void CalculateMotorSpeedError(float LeftMotorTarget,float RightMotorTarget);
void MotorControle(int speede);
void MotorControlOpenLoop(void);
extern void MotorControl(void);

void GetTargetSpeed(void);


#endif