#ifndef __DIALSWITCH_H__
#define __DIALSWITCH_H__

#include "common.h"
#include "include.h"

#define OpenDialSwitch 1  //启用拨码开关功能

#define  DialSwitch_1    GPIO_Get(PTA7 )
#define  DialSwitch_2    GPIO_Get(PTA8)
#define  DialSwitch_3    GPIO_Get(PTA9 )
#define  DialSwitch_4    GPIO_Get(PTA10)
#define  DialSwitch_5    GPIO_Get(PTA11)
#define  DialSwitch_6    GPIO_Get(PTA18)
//#define  DialSwitch_7    GPIO_Get(PTD14)

extern void DialSwitchInit(void);


#endif