#ifndef __STEER_H__
#define __SYEER_H__

#define S3010_FTM   FTM3       //FTM1ģ��
#define S3010_CH    FTM_CH0   //ͨ����PTA8
#define S3010_HZ    50 
//�����Ƶ��


#if 1


#define SteerMax 2690    //������ֵ
#define SteerMin  2140    //�����Сֵ
#define SteerMidle 2410 //�����ֵ

#endif



extern float  LastError;
extern float  Error;
extern float  EError;
extern int ok;

void SteerInit(void);//�����ʼ��
void CalculateError(void);
extern void SteerControl(void);


#endif
