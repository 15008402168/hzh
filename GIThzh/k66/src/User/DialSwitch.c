#include "common.h"
#include "include.h"
#include "DialSwitch.h"


#if  OpenDialSwitch


void DialSwitchInit(void)
{
  //���ϲ�����1��������ʱ����0
     GPIO_Init(PTC,6, GPI,0);//1
     GPIO_Init(PTC,7,GPI,0);//2
     GPIO_Init(PTC,8,GPI,0);//3
     GPIO_Init(PTC,9,GPI,0);//4
     
     GPIO_Init(PTA,11,GPI,0);//5
     GPIO_Init(PTA,18,GPI,0);//6
    // GPIO_Init(PTD,14,GPI,0);//7   
}

#endif