#include "common.h"
#include "include.h"
#include "Test.h"

#if BuzzerOpen //��������˷������궨��

//��������ʼ������
void BuzzerInit()
{
  GPIO_Init (PTA,19, GPO, 0);//��������ʼ��
}

void BuzzerTest(unsigned char flag)
{
  unsigned char Flag=0;
  Flag=0;
  Flag=flag;
  if(Flag)
  {
    BuzzerRing;
  }
  
  else
  {
    BuzzerQuiet;
  }
}

#endif


#if LedOpen

//Led��ʼ��
/*void LedInit()
{
   GPIO_Init (PTB,20, GPO,1);//����
   GPIO_Init (PTB,21, GPO,1);//����
   GPIO_Init (PTB,22, GPO,1);//����
   GPIO_Init (PTB,23, GPO,1);//����
}*/

//�����Ͻǵ�ledȥ���Ա�־λ
void  LeftUpLedTest(unsigned char flag)
{
  
 unsigned char Flag=0;
  Flag=0;
  Flag=flag;
  if(Flag)
  {
    LeftUpLedBright;
  }
  else
  {
    LeftUpLedDark;
  }
}

//�����½ǵ�ledȥ���Ա�־λ

void LeftUnderLedTest(unsigned char flag)
{
  
 unsigned char Flag=0;
  Flag=0;
  Flag=flag;
  if(Flag)
  {
    LeftUnderLedBright;
  }
  else
  {
    LeftUnderLedDark;
  }
}

//�����Ͻǵ�ledȥ���Ա�־λ
void RightUpLedTest(unsigned char flag)
{
  
 unsigned char Flag=0;
  Flag=0;
  Flag=flag;
  if(Flag)
  {
    RightUpLedBright;
  }
  else
  {
   RightUpLedDark;
  }
}

//�����½ǵ�ledȥ���Ա�־λ

void RightUnderLedTest(unsigned char flag)
{
  
 unsigned char Flag=0;
  Flag=0;
  Flag=flag;
  if(Flag)
  {
    RightUnderLedBright;
  }
  else
  {
    RightUnderLedDark;
  }
}

#endif