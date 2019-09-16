
#include "common.h"
#include "include.h"
#include "motor.h"
#include "DialSwitch.h"
#include "steer.h"
#include "findtrack.h"
#include "FTM.h"
#include "magnet.h"

int16  NumPulseFTMR,NumPulseFTML;//脉冲计数寄存器的值
int32  RightMotorPulseAccumulate;
int32  LeftMotorPulseAccumulate;
int  GetRightMotorPules,GetLeftMotorPules; //获得的一次脉冲总数（用于PID电机的数据处理）

int bizhangR=0;
int bizhangZ=0;
int bizhangS=0;
int bizhangJ=0;
int bizhangH=0;
int MOTORBZ=0;
int32 SpeedSet=0;



#if 1

float  SpeedP;//50.0;40
float  SpeedI;//16.0;50,0.0006
float  SpeedD;//1.3,10.0

#endif


float  Differential_P=0.0;//0.0250,0.1050


///////////////////////////////
//////////////////////////////
//////////////////////////////////

struct pid{
  double p;
  double i;
  double d;
  int jifen;
  int shangci;
  int qiwang;
  int shuchu;
};
struct pid MotorLeft = {20,0,2.4,0,0,0,0};
struct pid MotorRight = {20,0,2.4,0,0,0,0};


//struct pid MotorLeft = {25,0.0001,3.4,0,0,0,0};
//struct pid MotorRight = {25,0.0001,3.4,0,0,0,0};

#if OpenLoop//开环控制方式

int32  OpendLoopPwmL; //开环左边电机的PWM值
int32  OpendLoopPwmR; //开环右边电机的PWM值



//开环控制分为两个档位，通过3号拨码开关选择
//1.占空比不会变的开环匀速  2.开环变速，根据偏差拟和
void MotorControle(int speede)
{
  OpendLoopPwmR=speede;
  OpendLoopPwmL=speede;
  
  FTM_PWM_Duty(FTM0,FTM_CH1,OpendLoopPwmR);
  FTM_PWM_Duty(FTM0,FTM_CH3,OpendLoopPwmL);
}
void MotorControlOpenLoop(void)
{
  //  int ErrorError=0;
  
  
  //   OpendLoopPwmR=mide;
  //   OpendLoopPwmL=mide;
  OpendLoopPwmR=350;
  OpendLoopPwmL=350;
  
  //      //差速
  //      OpendLoopPwmL=(int)(OpendLoopPwmL-(OpendLoopPwmL*Error*000.1));
  //      
  //      if(OpendLoopPwmL>=890)  OpendLoopPwmL=890;
  //      if(OpendLoopPwmL<=200)    OpendLoopPwmL=200;
  //      
  //      OpendLoopPwmR=(int)(OpendLoopPwmR+(OpendLoopPwmR*Error*000.1));
  //            
  //      if(OpendLoopPwmR>=890)  OpendLoopPwmR=890;
  //      if(OpendLoopPwmR<=200)    OpendLoopPwmR=200;
  
  FTM_PWM_Duty(FTM0,FTM_CH1,OpendLoopPwmR);
  FTM_PWM_Duty(FTM0,FTM_CH3,OpendLoopPwmL); //PTC2,左电机 
  
}




#endif





#if CloseLoop //闭环控制


void GetTargetSpeed(void)
{
  
  if(1)
  {
    
    /////////////////////两米每秒是8ms 92个脉冲

    if(guole==1)
    {
      if(DIS>50&&DIS!=0)  SpeedSet=30;
      else if(DIS<45) SpeedSet=-30;
      else {SpeedSet=0;
             if(GetRightMotorPules==0)
               guole=2;
            }
      MotorLeft.qiwang=SpeedSet;
      MotorRight.qiwang=SpeedSet;
    }
    
    
    
    else if(guole>=2)
    {
      MOTORBZ=(bizhangH/1400)*15+30;;
      if(MOTORBZ>80)
      MOTORBZ=80;
      MotorLeft.qiwang=MOTORBZ;
      MotorRight.qiwang=MOTORBZ;
    }
    
    else if(ABS(out)>100)
    {
      SpeedSet=60;
      Differential_P=0.00045;//调差速，调太大会跳轮
      MotorLeft.qiwang=(int32)(SpeedSet-(Differential_P*out*SpeedSet)) ;//左轮差速
      if(MotorLeft.qiwang<=53)    MotorLeft.qiwang=53;
      if(MotorLeft.qiwang>=70)  MotorLeft.qiwang=70; 
      MotorLeft.qiwang=(int)(MotorLeft.qiwang);
      MotorRight.qiwang=(int32)(SpeedSet+(Differential_P*out) );//右轮差速
      if(MotorRight.qiwang<=55)    MotorRight.qiwang=55;
      if(MotorRight.qiwang>=70)  MotorRight.qiwang=70; 
      MotorRight.qiwang=(int)(MotorRight.qiwang);
      
    }
    else if((ABS(Error))>=13)
    {
      SpeedSet=110;//   加上速度控制舵机前129  下面是117  135   145   135
      Differential_P=0.005 ;//调差速，调太大会跳轮
      MotorLeft.qiwang=(int32)(SpeedSet-(Differential_P*Error*SpeedSet)) ;//左轮差速
      if(MotorLeft.qiwang<=50)    MotorLeft.qiwang=50;
      if(MotorLeft.qiwang>=115) MotorLeft.qiwang=115;
      MotorLeft.qiwang=(int)(MotorLeft.qiwang);
      MotorRight.qiwang=(int32)(SpeedSet+(Differential_P*Error*SpeedSet) );//右轮差速
      if(MotorRight.qiwang<=50)    MotorRight.qiwang=50;
      if(MotorRight.qiwang>=115)  MotorRight.qiwang=115; 
      MotorRight.qiwang=(int)(MotorRight.qiwang);
    }
    
    else if(yyy==0)
    {    
     if(broken_p==1&&broken_m==0)
        SpeedSet=110;
      if(broken_m)
        SpeedSet=110;
      if(BrokenFlag==1)
        SpeedSet=92;
      else
      {
        SpeedSet=115;   
      }
      MotorLeft.qiwang=(int)(SpeedSet) ;
      MotorRight.qiwang=(int)(SpeedSet) ;  
    }
    
    else
    {
      SpeedSet=90;
      MotorLeft.qiwang=(int)(SpeedSet) ;
      MotorRight.qiwang=(int)(SpeedSet) ;
    }
    
    if(stopstop<70&&guole==0)
    {
      MotorLeft.qiwang=0 ;
      MotorRight.qiwang=0 ;
    }
  } 
}


//增量式PID控制算法

void MotorControl(void)
{ 
  GetTargetSpeed();
 
  
  MotorRight.jifen += MotorRight.qiwang - GetRightMotorPules;
  if(MotorRight.jifen>100000)
    MotorRight.jifen=100000;
  if(MotorRight.jifen<-100000)
    MotorRight.jifen=-100000;  
  MotorRight.shuchu = (int)(MotorRight.p*(MotorRight.qiwang - GetRightMotorPules) + MotorRight.i*MotorRight.jifen + MotorRight.d*(GetRightMotorPules-MotorRight.shangci));
  
  MotorLeft.jifen += MotorLeft.qiwang - GetLeftMotorPules;
  if(MotorLeft.jifen>100000)
    MotorLeft.jifen=100000;
  if(MotorLeft.jifen<-100000)
    MotorLeft.jifen=-100000;  
  MotorLeft.shuchu =(int) (MotorLeft.p*(MotorLeft.qiwang - GetLeftMotorPules) + MotorLeft.i*MotorLeft.jifen + MotorLeft.d*(GetLeftMotorPules-MotorLeft.shangci));
   
  
  if(MotorLeft.shuchu<=-700)               MotorLeft.shuchu=-700;
   if(MotorLeft.shuchu>=700)             MotorLeft.shuchu=700;
   if(MotorRight.shuchu<=-700)              MotorRight.shuchu=-700;
   if(MotorRight.shuchu>=700)            MotorRight.shuchu=700; 
  
  if(MotorRight.shuchu>=0)
  {
    FTM_PWM_Duty(FTM0,FTM_CH1,MotorRight.shuchu);
    FTM_PWM_Duty(FTM0,FTM_CH0,0);
  }
  else
  {
    FTM_PWM_Duty(FTM0,FTM_CH0,-MotorRight.shuchu);
    FTM_PWM_Duty(FTM0,FTM_CH1,0);
  }
  if(MotorLeft.shuchu>=0)
  {
    FTM_PWM_Duty(FTM0,FTM_CH3,MotorLeft.shuchu);
    FTM_PWM_Duty(FTM0,FTM_CH2,0);
  }
  else
  {
    FTM_PWM_Duty(FTM0,FTM_CH2,-MotorLeft.shuchu); 
    FTM_PWM_Duty(FTM0,FTM_CH3,0);
  }
  
  //PTC2,左电机       
}


#endif







void SpeedGet(void)

{
  LeftMotorPulseAccumulate=FTM_AB_Get(FTM1); 
  RightMotorPulseAccumulate=FTM_AB_Get(FTM2);//取寄存器的值
}


void PIT0_Interrupt()//PIT0_IRQHandler
{  
  disable_irq(PIT0_IRQn);            //关PIT中断
  PIT_Flag_Clear(PIT0);                           //清中断标志位
  SpeedGet();                        //每次进来累加一次速度
  GetRightMotorPules=(int)((-RightMotorPulseAccumulate));  //保持好这次测得的总数，10ms一共测得的脉冲
  GetLeftMotorPules=(int)((LeftMotorPulseAccumulate));
  
  if(guole>=2)
  {
    bizhangR+=GetRightMotorPules;
    bizhangZ+=GetLeftMotorPules;
  }
  else
  {
    bizhangR=0;
    bizhangZ=0;
  }
  bizhangH=(int)(0.5*(bizhangR+bizhangZ));
  
  enable_irq(PIT0_IRQn);//使能中断	
}





