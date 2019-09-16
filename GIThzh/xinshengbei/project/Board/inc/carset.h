#ifndef __CARSET_H
#define __CARSET_H

#include "stm32f10x.h"



void GPIO_motor_init(void);
void TIM_motor_init(u16 ccr);

void delayms(int a);

void GPIO_infrared_init(void);
void TIM_servo_init(u16 ccr);

void GPIO_servo_init(void);

void KEY_Init(void);
void EXTIX_Init(void);


#endif

