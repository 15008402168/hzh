#define OUT1     ADC0_SE13
#define OUT2     ADC0_SE12
#define OUT3     ADC1_SE11
#define OUT4     ADC1_SE10
#define OUT5     ADC1_SE13
#define OUT6     ADC1_SE12

#include "ADC.h"
#include "common.h"
#include "include.h"
#include "steer.h"
#include "findtrack.h"
#include "motor.h"
#include "DialSwitch.h"

int kongzhi;
int circle1=0;
int circle2=0;
int break1,break2;
int key1=0;
int key2=0;
int circleout1=0;
int circleout2=0;
int magleft[4]={0,0,0,0},
magmiddle[4]={0,0,0,0},
magright[4]={0,0,0,0},
maglleft[4]={0,0,0,0},
magrright[4]={0,0,0,0},magF1,magF2,magF3,out;
float lasterror=0;
float mid;
int qianzhan=0;
extern float Error;
extern int kongzhi;
int stopstop;
int yyy;
float error;
float error1,error2;
extern int circle;
extern int SeCovered;
float kr=1.0;
float kl=1.0;
int Firstride=0;
int STEER;

int magnetanalysis1(void)
{
  float k1,k2;
  maglleft[0]=maglleft[1]; maglleft[1]=maglleft[2];
   magleft[0]=magleft[1]; magleft[1]=magleft[2];
    magmiddle[0]=magmiddle[1]; magmiddle[1]=magmiddle[2];
     magright[0]=magright[1]; magright[1]=magright[2];
      magrright[0]=magrright[1]; magrright[1]=magrright[2];
  
  maglleft[2]=ADC_Ave(ADC_1,ADC1_SE11,ADC_12bit,10);
  magleft[2]=ADC_Ave(ADC_0,ADC0_SE13,ADC_12bit,10);
  magmiddle[2]=ADC_Ave(ADC_1,ADC1_SE12,ADC_12bit,10);
  magright[2]=ADC_Ave(ADC_1,ADC1_SE10,ADC_12bit,10);
  magrright[2]=ADC_Ave(ADC_1,ADC1_SE13,ADC_12bit,10);
  
  maglleft[3]=(int)(0.5*maglleft[2]+0.3*maglleft[1]+0.2*maglleft[0]);
  magleft[3]=(int)(0.5*magleft[2]+0.3*magleft[1]+0.2*magleft[0]);
  magmiddle[3]=(int)(0.5*magmiddle[2]+0.3*magmiddle[1]+0.2*magmiddle[0]);
  magright[3]=(int)(0.5*magright[2]+0.3*magright[1]+0.2*magright[0]);
  magrright[3]=(int)(0.5*magrright[2]+0.3*magrright[1]+0.2*magrright[0]);
  
  
  
  lasterror=error;
  //error=500*(magleft[3]-magright[3])/(magleft[3]+magright[3]);//980

   error=237*(1.3*maglleft[3]+0.8*magleft[3]-1.3*magrright[3]-0.8*magright[3])/(1.3*maglleft[3]+1.3*magrright[3]+0.8*magleft[3]+0.8*magright[3]);
   error1=237*(kl*maglleft[3]-kr*magrright[3])/(kr*magrright[3]+kl*maglleft[3]);
   error2=237*(magleft[3]-magright[3])/(magright[3]+magleft[3]);
  //k1=0.216+(error* error)*0.00042;//0.256 0.00052  sped55
  //k2=4.945;//+error*error*0.00034;//4.8 0.00046
  //k2=5.00;
  k2=6.0+(error* error)*0.00038;
  k2=0;
 k1=0.2+(error* error)*0.00038;//45 49
 // if(k1>15)  k1=15;
 // k2=8.2+(error* error)*0.0058;
 // if(k2>70)  k2=70;
  
  
  if((ABS(error1-error2)>28)&&(circle==0))
    error=error1;
  else if(circle==1)
    error=error1;
    out=(int)(k1*error+k2*(error-lasterror));
  
  if(out>260)
    out=260;
  if(out<-260)
    out=-260;
  
  stopstop=(int)((maglleft[2]+magleft[2]+magmiddle[2]+magright[2]+magrright[2])/5);
  
  
  GPIO_Ctrl (PTB,0,1); //trig置高电平
  LPTMR_delay_us(12);   //15us
  GPIO_Ctrl (PTB,0,0); //trig置低电平
  
  if(guole==2)
  {
    bizhangJ=2500;
    guole=3;
  }
  
  
  if(guole==3)
  {
    
    if(DialSwitch_4)
    {
      if(bizhangJ>0)
       bizhangJ--;
 else  if(magleft[3]>200||magmiddle[3]>200)//左
    {
      guole=4;
      mid=300;
    }
    }
    else{
      if(bizhangJ>0)
       bizhangJ--;
  else if(magright[3]>200||magmiddle[3]>200)//右   
    {
      guole=4;
      mid=300;
    }
    } 
  }
  yyy=1;
  Error=0;
  
  
  return out;
}

void magnetcontrol(int input)
{
   if(guole==4)
   {
     if(mid>0)
     {
       if(DialSwitch_4)
     input=-260;//右
     else
       input=260;//左
     mid--;
     }
     else
       guole=0;
   }
    FTM_PWM_Duty(FTM3,FTM_CH0,SteerMidle+input);////有修改

}

void circlescanning(void)
{
  if((circle==0)&&(magmiddle[2]>3100))
  {
    circle=1;
    for(int i=0;i<500000;i++)
      {
        magnetcontrol(0);
       }//SeCovered=0;
  }
  /*if((Firstride==0)&&(circle==1)&&(maglleft[2]>magrright[2]))
  {
    kr=0.1;
    kl=100;
    Firstride=1;
  }
  else if((Firstride==0)&&(circle==1)&&(magrright[2]>maglleft[2]))
  {
    kl=0.1;
    kr=100;
    Firstride=1;
  }
  if((kl!=1.0)&&(magmiddle[2]<1800))
  {
    kr=kl=1.0;
    circle=0;
    Firstride=0;
  }*/
 
  if((circle==2)&&(magmiddle[2]>2700))//&&(SeCovered>200))
  {
    for(int i=0;i<200000;i++)
          {
            out=0;
            magnetcontrol(out);
            FTM_PWM_Duty(FTM0,FTM_CH1,180);
            FTM_PWM_Duty(FTM0,FTM_CH3,180); 
          }
          circle=0;
  }
  /*if((circle==2)&&(magrright[2]>2700))//&&(SeCovered>200))
  {
    for(int i=0;i<200000;i++)
          {
            out=0;
            magnetcontrol(out);
            FTM_PWM_Duty(FTM0,FTM_CH1,180);
            FTM_PWM_Duty(FTM0,FTM_CH3,180); 
          }
          circle=0;
  }*/
  if((circle==1)&&(magright[2]-100>magleft[2]))
  {
    for(int i=0;i<650000;i++)
          {
            out=260;
            magnetcontrol(out);
            //FTM_PWM_Duty(FTM0,FTM_CH0,180);
            //FTM_PWM_Duty(FTM0,FTM_CH3,180); 
          }
          circle=2;
   }
  else if((circle==1)&&(magleft[2]-100>magright[2]))
      {
        for(int j=0;j<700000;j++)
          {
            out=-260;
            magnetcontrol(out);
            //FTM_PWM_Duty(FTM0,FTM_CH0,180);
            //FTM_PWM_Duty(FTM0,FTM_CH3,180); 
          }
          circle=2;
       }
}






/*void MovingAverage(void)
{
for (int i=0;i<6;i++)//采集5次
{
mag3[0][i]=adc_once   (ADC0,OUT1, ADC_8bit) ;
mag3[1][i]=adc_once   (ADC0,OUT2, ADC_8bit) ;
mag3[2][i]=adc_once   (ADC1,OUT3, ADC_8bit) ;
   }
//排序
for(int j=0;j<3;j++)
{
for(int a=0;a<4;a++)
{
for(int b=0;b<4-a;b++)
{
if(mag3[j][b]>mag3[j][b+1])
{
int temp;
temp=mag3[j][b+1];
mag3[j][b+1]=mag3[j][b];
mag3[j][b]=temp;
        }
      }
    }
  }
//取中间三个ADC值均值
for(k=0;k<3;k++)
{
sum[k]=(mag3[k][1]+mag3[k][2]+mag3[k][3])/3;
  }
//滤波
int i1=0;
int i2=0;
int i3=0;
int i4=0;
int i5=0;
int i6=0;
float sum1,sum2,sum3,sum4,sum5;

float maggee1[20];
float maggee2[20];
float maggee3[20];
float maggee4[20];
float maggee5[20];
float maggee6[20];

maggee1[i1++]=adc_once   (ADC1,OUT1, ADC_8bit) ;
maggee2[i2++]=adc_once   (ADC0,OUT2, ADC_8bit) ;
maggee3[i3++]=adc_once   (ADC0,OUT3, ADC_8bit) ;
maggee4[i4++]=adc_once   (ADC1,OUT4, ADC_8bit) ;
maggee5[i5++]=adc_once   (ADC0,OUT5, ADC_8bit) ;
maggee6[i6++]=adc_once   (ADC1,OUT6, ADC_8bit) ;

if(i1==20)
i1=0;
if(i2==20)
i2=0;
if(i3==20)
i3=0;
if(i4==20)
i4=0;
if(i5==20)
i5=0;
if(i6==20)
i6=0;

for(int count=0;count<20;count++)
{
sum1+=maggee1[count];
sum2+=maggee2[count];
sum3+=maggee3[count];
sum4+=maggee4[count];
sum5+=maggee5[count];
sum6+=maggee6[count];
  }//sumk与前方sum[k]等效

}
*/