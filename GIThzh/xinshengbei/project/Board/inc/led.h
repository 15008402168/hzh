#ifndef _LED_H_
#define _LED_H_ 
#include "stm32f10x.h" 
//��ö������з�װ
typedef enum 
{
	LED1,
	LED2,
	LED3,
	LED_ALL
}LED;

extern uint16_t Light_Val;          															//�Ƶ����ȱ���
	
extern void Led_Init(LED Led);
extern void Led_Set(LED Led, uint8_t State);
extern void Set_RGB_Value(uint16_t Red, uint16_t Green, uint16_t Blue);
 
#endif
