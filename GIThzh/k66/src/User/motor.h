#include "findtrack.h"

#ifndef __MOTOR_H__
#define __MOTOR_H__

#define  MotorControlPeriod   1     //�������ֵ��������
#define  SteetControlPeriod   20    //�����������

#define  OpenLoop 1 //�궨����1���ٶȿ�������
#define  CloseLoop 1 //�궨����1���ٶȱջ�����
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