/****************************************************************************************************
��ƽ    ̨������K66FX���ܳ�VDĸ��
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2018��4��28��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.80.4������
��Target  ��K66FX1M0VLQ18
��Crystal �� 50.000Mhz
��busclock��110.000MHz
��pllclock��220.000MHz
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


//����������
//����궨��
#define S3010_FTM   FTM3
#define S3010_CH    FTM_CH0
//#define S3010_HZ    (50)
#define S3010_PIN   FTM3_CH0

#define     Step_Right       1940 //����Ƶ�ʸı䣬ֵ��Ҫ���±궨
#define     Step_Middle      1690 //����Ƶ�ʸı䣬��ֵ��Ҫ���±궨
#define     Step_Left        1440 //����Ƶ�ʸı䣬ֵ��Ҫ���±궨


//����궨��
#define MOTOR_HZ    (1000)


#define MOTOR  PTC
#define MOTOR_FTM   FTM0
#define MOTOR1_PWM  FTM_CH1
#define MOTOR2_PWM  FTM_CH2

#define MOTOR1_PWM_IO  FTM0_CH1
#define MOTOR2_PWM_IO  FTM0_CH2


void Motor_Init(void)             //��ʼ������ͨ��PWM
{
  
  GPIO_Init(MOTOR,1,GPO,LOW);
  GPIO_Init(MOTOR,2,GPO,LOW);
  
  
  FTM_PWM_Init(FTM0,FTM_CH0,bus_clk_M*1000000/12500/8,0);//Mot0-PTC1
  FTM_PWM_Init(FTM0,FTM_CH1,bus_clk_M*1000000/12500/8,0);//Mot1-PTC2 
  FTM_PWM_Init(FTM0,FTM_CH2,bus_clk_M*1000000/12500/8,0);//Mot2-PTC3
  FTM_PWM_Init(FTM0,FTM_CH3,bus_clk_M*1000000/12500/8,0);//Mot3-PTC4 
  
  Servo_FTM_PWM_Init(S3010_FTM,S3010_CH,bus_clk_M*1000000/64/50,Step_Middle);//Mot11-PTC10    ���������ߴ��ұ�С
  
}
void ftm_init(void)
{
  FTM_AB_Init(FTM1);
  FTM_AB_Init(FTM2);
}


int countt=0,countyy=0;char qazwsx[100];
int llspeedx,lspeedx,speedx,speedy,speedD;
int speeee[3];
//������
void main(void)
{       
  DisableInterrupts;           //�ر��ж�
  PLL_Init(PLL220);            //��ʼ��PLLΪ?M,����Ϊ��M
  UART_Init(UART_4,9600);    //UART��ʼ��
  LED_Init();  
  DialSwitchInit(); 
  //LQMT9V034_Init();
  TFTSPI_Init();
  Motor_Init();                //����͵����ʼ��
  ftm_init();
  ADC_Init(ADC_0);             //��Դ��ѹ����ADC��ʼ�� 
  ADC_Init(ADC_1);             //��Դ��ѹ����ADC��ʼ��
  PIT_Init(PIT0, 8);
  EnableInterrupts;            //�����ж�
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






