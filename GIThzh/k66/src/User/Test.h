#ifndef __TEST_H__
#define __TEST_H__

#define BuzzerOpen  1 //打开蜂鸣器

#define LedOpen     1 //打开Led

extern void BuzzerInit();
extern void LedInit();
extern void BuzzerTest(unsigned char flag);
extern void LeftUpLedTest(unsigned char flag);
extern void LeftUnderLedTest(unsigned char flag);
extern void RightUnderLedTest(unsigned char flag);
extern void RightUpLedTest(unsigned char flag);


#define  BuzzerRing           GPIO_Ctrl   (PTB,19, 1) //蜂鸣器响
#define  BuzzerQuiet          GPIO_Ctrl   (PTB,19, 0) //蜂鸣器不响

#define  LeftUpLedBright      GPIO_Ctrl   (PTB,20, 0) //左上的Led亮 
#define  LeftUpLedDark        GPIO_Ctrl   (PTB,20, 1) //左上的Led暗 

#define  LeftUnderLedBright   GPIO_Ctrl   (PTB,21, 0) //左下的Led亮 
#define  LeftUnderLedDark     GPIO_Ctrl   (PTB,21, 1) //左下的Led暗 

#define  RightUnderLedBright  GPIO_Ctrl   (PTB,22, 0) //右下的Led亮 
#define  RightUnderLedDark    GPIO_Ctrl   (PTB,22, 1) //右下的Led暗 

#define  RightUpLedBright     GPIO_Ctrl   (PTB,23, 0) //右上的Led亮 
#define  RightUpLedDark       GPIO_Ctrl   (PTB,23, 1) //右上的Led暗 


#endif