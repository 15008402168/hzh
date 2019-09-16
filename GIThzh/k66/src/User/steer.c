#include "common.h"
#include "include.h"
#include "steer.h"
#include "findtrack.h"
#include "motor.h"
#include "FTM.h"
#include "magnet.h"

/*********define for SteerControl**********/

float  KP=15;//����������ϵ����Ӱ�����Ĵ�Ƿ�Χ
float  KD=8;//10//7.5//�������΢��ϵ��,Ӱ�����Ĵ�Ƿ�Ӧ
float  SteerPwmAdd=0.0;//���pwm����
float  Error;//ƫ��ֵ
float  EError;
float  LastError;//�ϴε�ƫ��
float  WeightSum=0;
float  EWeightSum=0;
float  CenterMeanValue=0;
float  ECenterMeanValue=0;
float  CenterSum=0;
float  ECenterSum=0;
float  J=0.0066;//����p��ƫ��Ĺ�ϵ��Խ������Խǿ   0.67   �����ٶȿ���ǰ �õ�  J=0.0062   JD=0.030   basicp=2.8   basicd=7��
//float  JS=0.0004;
float  JD=0.031;//����p��ƫ��Ĺ�ϵ��Խ������Խǿ   0.1
float  BasicP=2.7; //������Pֵ  3.0
float  BasicD=7; //������Pֵ  6.9
double p;
int chuchu=15;

uint32 SteerPwm=0,LastSteerSwm=0;//�����pwmֵ���ϴζ����pwmֵ

//��Ȩƽ����Ȩֵ��ѡȡ











void SteerControl(void)
{
  
  //   CalculateError();
  
  double px,py,pp,pangle;
  double speed_steer,EP;
  speed_steer=0.5*(GetRightMotorPules+GetLeftMotorPules);
  if(speed_steer<95)
  {
    px=(midline_x[5]-78)/2;
  py=(140-midline_y[4])/2;
  EP=1750;
  }
  else{
  px=(midline_x[7]-78)/2;
  py=(140-midline_y[7])/2;
  EP=1700;
  }
  
 
  
  pangle=atan(px/py);
  pp=sqrt(px*px+py*py);
  //  if(pangle>1.5707963)
  //     p=-sin(pangle)/
  //  else
  p=-sin(pangle)/pp;
  LastError=Error;
  Error=(int)(p*EP);//1700
  
   speed_steer=0.5*(GetRightMotorPules+GetLeftMotorPules);  
  //KP=BasicP+(Error* Error)*J+(speed_steer*speed_steer)*JS;//��̬����pģ��


   KP=BasicP+(Error* Error)*J;
  if(KP>=17) KP=17;//pֵ�޷�
  
  KD=BasicD+(Error* Error)*JD;
  
  if(KD>=80) KD=80;//pֵ�޷�
  
/*  
  if((GetRightMotorPules+GetLeftMotorPules)<180&&ABS(Error)>10)
  {
  KP=(Error* Error)*J*2-15;
  if(KP>=17) KP=17;//pֵ�޷�
  if(KP<0)   KP=1;
  KD=(Error* Error)*JD*1.5;
  
  if(KD>=70) KD=70;//pֵ�޷�
  }
  else 
  {
    KP=BasicP+(Error* Error)*J;
  if(KP>=17) KP=17;//pֵ�޷�
  
  KD=BasicD+(Error* Error)*JD;
  
  if(KD>=65) KD=65;//pֵ�޷�
  }
*/  
  
  
  SteerPwmAdd=(KP*Error)+KD*(Error-LastError);//�����pd������
  
  if(SteerPwmAdd>=260)
    
    SteerPwmAdd=260;
  
  if(SteerPwmAdd<=-260)
    
    SteerPwmAdd=-260;
  
  
  SteerPwm=(uint16)(SteerPwmAdd+SteerMidle);////���޸�
  
  
  if(roundflagl==1)
  {
    chuchu=15;
    //   if(ABS(Error)<40)//40
    //    SteerPwm=SteerPwm+250;
    if((Error)<30)//40
    {
      SteerPwm=SteerPwm+465;
      Error=Error+60;
    }
    
  }
  else if(roundflagr==1)
  {
    chuchu=15;
    //  if(ABS(Error)<40)
    //  SteerPwm=SteerPwm-250;
    if((Error)>-30)
    {
      SteerPwm=SteerPwm-465;
      Error=Error-60;
    }
    
  }
  if(roundflagr==2||roundflagl==2)
  {
    if(chuchu>0)
    {
      SteerPwm=SteerMidle;
      chuchu--;
    }
  }
  
  if(SteerPwm>=SteerMax)//�޷�
    
    SteerPwm=SteerMax;
  
  if(SteerPwm<=SteerMin)
    
    SteerPwm=SteerMin;
  
  FTM_PWM_Duty(FTM3,FTM_CH0,SteerPwm);//���pwm����           
  LastSteerSwm=SteerPwm;//��¼pwmֵ
  
}










