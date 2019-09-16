/****************************************************************************************************
【平    台】龙邱K66FX智能车VD母板
【编    写】CHIUSIR
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2018年4月28日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
------------------------------------------------
【dev.env.】IAR7.80.4及以上
【Target  】K66FX1M0VLQ18
【Crystal 】 50.000Mhz
【busclock】110.000MHz
【pllclock】220.000MHz
=============================================================
*******************************************************************************************************/
#include "include.h" 
#include "motor.h"
#include "findtrack.h"
#include "Test.h"
#include "DialSwitch.h"
#include "steer.h"
#include "common.h"
#include "motor.h"
#include "magnet.h"
#include "ADC.h"


//定义舵机参数
//舵机宏定义
#define S3010_FTM   FTM3
#define S3010_CH    FTM_CH0
//#define S3010_HZ    (50)
#define S3010_PIN   FTM3_CH0

#define     Step_Right       1940 //总线频率改变，值需要重新标定
#define     Step_Middle      1690 //总线频率改变，中值需要重新标定
#define     Step_Left        1440 //总线频率改变，值需要重新标定


//电机宏定义
#define MOTOR_HZ    (1000)


#define MOTOR  PTC
#define MOTOR_FTM   FTM0
#define MOTOR1_PWM  FTM_CH1
#define MOTOR2_PWM  FTM_CH2

#define MOTOR1_PWM_IO  FTM0_CH1
#define MOTOR2_PWM_IO  FTM0_CH2


void Motor_Init(void)             //初始化各个通道PWM
{
  
  GPIO_Init(MOTOR,1,GPO,LOW);
  GPIO_Init(MOTOR,2,GPO,LOW);
  
  
  FTM_PWM_Init(FTM0,FTM_CH0,bus_clk_M*1000000/12500/8,0);//Mot0-PTC1
  FTM_PWM_Init(FTM0,FTM_CH1,bus_clk_M*1000000/12500/8,0);//Mot1-PTC2 
  FTM_PWM_Init(FTM0,FTM_CH2,bus_clk_M*1000000/12500/8,0);//Mot2-PTC3
  FTM_PWM_Init(FTM0,FTM_CH3,bus_clk_M*1000000/12500/8,0);//Mot3-PTC4 
  
  Servo_FTM_PWM_Init(S3010_FTM,S3010_CH,bus_clk_M*1000000/64/50,Step_Middle);//Mot11-PTC10    舵机方向左边大右边小
  
}
void ftm_init(void)
{
  FTM_AB_Init(FTM1);
  FTM_AB_Init(FTM2);
}


int countt=0,countyy=0;char qazwsx[100];
int llspeedx,lspeedx,speedx,speedy,speedD;
int speeee[3];
//主函数
void main(void)
{       
  DisableInterrupts;           //关闭中断
  PLL_Init(PLL220);            //初始化PLL为?M,总线为？M
  UART_Init(UART_4,9600);    //UART初始化
  LED_Init();  
  DialSwitchInit(); 
  //LQMT9V034_Init();
  TFTSPI_Init();
  Motor_Init();                //舵机和电机初始化
  ftm_init();
  ADC_Init(ADC_0);             //电源低压报警ADC初始化 
  ADC_Init(ADC_1);             //电源低压报警ADC初始化
  PIT_Init(PIT0, 8);
  EnableInterrupts;            //开启中断
  TFTSPI_CLS(u16BLACK);
   FTM_PWM_Duty(FTM3,FTM_CH0,2410);
   
  while(1)
  {
    
    
    while(UART_Query_Str(UART_4,qazwsx,99)!=0)
    {
      llspeedx=lspeedx;
      lspeedx=speedx;
      //UART_Put_Str(UART_4,qazwsx);
      if(qazwsx[0]=='X') {countt=1;countyy=0;}
        else if(qazwsx[0]=='-'&&countt==1) countt=2;
        else if(qazwsx[0]>='0'&&countt==2&&qazwsx[0]!='Y') {countt=3;speedx = -(qazwsx[0] - '0');}
        else if(qazwsx[0]>='0'&&countt==3&&qazwsx[0]!='Y') {countt=4;speedx = speedx*10-(qazwsx[0] - '0');}
        else if(qazwsx[0]>='0'&&countt==1&&qazwsx[0]!='Y') {countt=6;speedx = (qazwsx[0] - '0');}
        else if(qazwsx[0]>='0'&&countt==6&&qazwsx[0]!='Y') {countt=7;speedx = speedx*10+(qazwsx[0] - '0');}
        
        if(qazwsx[0]=='Y'&&qazwsx[0]!='X') {countt=0;countyy=1;}
        else if(qazwsx[0]=='-'&&countyy==1) countyy=2;
        else if(qazwsx[0]>='0'&&countyy==2&&qazwsx[0]!='X') {countyy=3;speedy = -(qazwsx[0] - '0');}
        else if(qazwsx[0]>='0'&&countyy==3&&qazwsx[0]!='X') {countyy=4;speedy = speedy*10-(qazwsx[0] - '0');}
        else if(qazwsx[0]>='0'&&countyy==1&&qazwsx[0]!='X') {countyy=6;speedy = (qazwsx[0] - '0');}
        else if(qazwsx[0]>='0'&&countyy==6&&qazwsx[0]!='X') {countyy=7;speedy = speedy*10+(qazwsx[0] - '0');}

     //speedx=(llspeedx+lspeedx+speedx)/3;
     
    }


    speedD=(int)(sqrt(speedy*speedy+speedx*speedx));
    
    
     if(speedy>=0)
      {
        
       FTM_PWM_Duty(FTM0,FTM_CH1,speedD*5);
       FTM_PWM_Duty(FTM0,FTM_CH3,speedD*5);
       FTM_PWM_Duty(FTM0,FTM_CH0,0);
       FTM_PWM_Duty(FTM0,FTM_CH2,0);
       FTM_PWM_Duty(FTM3,FTM_CH0,(int)(2410-0.9*(speedx+lspeedx+llspeedx)));
        
      }
    if(speedy<0)
      {
        
       FTM_PWM_Duty(FTM0,FTM_CH1,0);
       FTM_PWM_Duty(FTM0,FTM_CH3,0);
       FTM_PWM_Duty(FTM0,FTM_CH0,speedD*5);
       FTM_PWM_Duty(FTM0,FTM_CH2,speedD*5); 
       FTM_PWM_Duty(FTM3,FTM_CH0,(int)(2410-0.9*(speedx+lspeedx+llspeedx)));
        
      } 
    
    
   // LPTMR_delay_ms(10);
  }
  
  
  
  

  
  
}






