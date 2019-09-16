#include "common.h"
#include "include.h"
#include "steer.h"
#include "findtrack.h"
#include "motor.h"
#include "FTM.h"
#include "magnet.h"

/*********define for SteerControl**********/

float  KP=15;//舵机方向比例系数，影响舵机的打角范围
float  KD=8;//10//7.5//舵机方向微分系数,影响舵机的打角反应
float  SteerPwmAdd=0.0;//舵机pwm增量
float  Error;//偏差值
float  EError;
float  LastError;//上次的偏差
float  WeightSum=0;
float  EWeightSum=0;
float  CenterMeanValue=0;
float  ECenterMeanValue=0;
float  CenterSum=0;
float  ECenterSum=0;
float  J=0.0066;//调节p和偏差的关系，越大，作用越强   0.67   加上速度控制前 好的  J=0.0062   JD=0.030   basicp=2.8   basicd=7；
//float  JS=0.0004;
float  JD=0.031;//调节p和偏差的关系，越大，作用越强   0.1
float  BasicP=2.7; //基本的P值  3.0
float  BasicD=7; //基本的P值  6.9
double p;
int chuchu=15;

uint32 SteerPwm=0,LastSteerSwm=0;//舵机的pwm值和上次舵机的pwm值

//加权平均，权值的选取











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
  //KP=BasicP+(Error* Error)*J+(speed_steer*speed_steer)*JS;//动态二次p模型


   KP=BasicP+(Error* Error)*J;
  if(KP>=17) KP=17;//p值限幅
  
  KD=BasicD+(Error* Error)*JD;
  
  if(KD>=80) KD=80;//p值限幅
  
/*  
  if((GetRightMotorPules+GetLeftMotorPules)<180&&ABS(Error)>10)
  {
  KP=(Error* Error)*J*2-15;
  if(KP>=17) KP=17;//p值限幅
  if(KP<0)   KP=1;
  KD=(Error* Error)*JD*1.5;
  
  if(KD>=70) KD=70;//p值限幅
  }
  else 
  {
    KP=BasicP+(Error* Error)*J;
  if(KP>=17) KP=17;//p值限幅
  
  KD=BasicD+(Error* Error)*JD;
  
  if(KD>=65) KD=65;//p值限幅
  }
*/  
  
  
  SteerPwmAdd=(KP*Error)+KD*(Error-LastError);//舵机的pd控制器
  
  if(SteerPwmAdd>=260)
    
    SteerPwmAdd=260;
  
  if(SteerPwmAdd<=-260)
    
    SteerPwmAdd=-260;
  
  
  SteerPwm=(uint16)(SteerPwmAdd+SteerMidle);////有修改
  
  
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
  
  if(SteerPwm>=SteerMax)//限幅
    
    SteerPwm=SteerMax;
  
  if(SteerPwm<=SteerMin)
    
    SteerPwm=SteerMin;
  
  FTM_PWM_Duty(FTM3,FTM_CH0,SteerPwm);//舵机pwm更新           
  LastSteerSwm=SteerPwm;//记录pwm值
  
}










