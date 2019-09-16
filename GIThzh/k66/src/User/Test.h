#ifndef __TEST_H__
#define __TEST_H__

#define BuzzerOpen  1 //�򿪷�����

#define LedOpen     1 //��Led

extern void BuzzerInit();
extern void LedInit();
extern void BuzzerTest(unsigned char flag);
extern void LeftUpLedTest(unsigned char flag);
extern void LeftUnderLedTest(unsigned char flag);
extern void RightUnderLedTest(unsigned char flag);
extern void RightUpLedTest(unsigned char flag);


#define  BuzzerRing           GPIO_Ctrl   (PTB,19, 1) //��������
#define  BuzzerQuiet          GPIO_Ctrl   (PTB,19, 0) //����������

#define  LeftUpLedBright      GPIO_Ctrl   (PTB,20, 0) //���ϵ�Led�� 
#define  LeftUpLedDark        GPIO_Ctrl   (PTB,20, 1) //���ϵ�Led�� 

#define  LeftUnderLedBright   GPIO_Ctrl   (PTB,21, 0) //���µ�Led�� 
#define  LeftUnderLedDark     GPIO_Ctrl   (PTB,21, 1) //���µ�Led�� 

#define  RightUnderLedBright  GPIO_Ctrl   (PTB,22, 0) //���µ�Led�� 
#define  RightUnderLedDark    GPIO_Ctrl   (PTB,22, 1) //���µ�Led�� 

#define  RightUpLedBright     GPIO_Ctrl   (PTB,23, 0) //���ϵ�Led�� 
#define  RightUpLedDark       GPIO_Ctrl   (PTB,23, 1) //���ϵ�Led�� 


#endif