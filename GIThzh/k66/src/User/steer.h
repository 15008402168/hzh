#ifndef __STEER_H__
#define __SYEER_H__

#define S3010_FTM   FTM3       //FTM1模块
#define S3010_CH    FTM_CH0   //通道号PTA8
#define S3010_HZ    50 
//舵机的频率


#if 1


#define SteerMax 2690    //舵机最大值
#define SteerMin  2140    //舵机最小值
#define SteerMidle 2410 //舵机中值

#endif



extern float  LastError;
extern float  Error;
extern float  EError;
extern int ok;

void SteerInit(void);//舵机初始化
void CalculateError(void);
extern void SteerControl(void);


#endif
