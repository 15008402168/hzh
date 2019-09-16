
#include "stm32f10x.h"
#include "carset.h"




//电机端口初始化

void GPIO_motor_init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//使能 GPIO 功能时钟
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//电机端口
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
}

//电机tim初始化
void TIM_motor_init(u16 ccr)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period=500;	//设置自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler=71;		//设置时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision=0;	 //设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;	//TIM 向上计数
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);		//初始化 TIM3
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;			//选择 PWM 模式 1
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;	 //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;	//输出极性高
	TIM_OCInitStructure.TIM_Pulse=ccr;
	TIM_OC1PreloadConfig(TIM5,TIM_OCPreload_Enable);	//使能预装载寄存器
	TIM_OC1Init(TIM5,&TIM_OCInitStructure);						//初始化外设 TIM OC2
	TIM_OC2PreloadConfig(TIM5,TIM_OCPreload_Enable);
	TIM_OC2Init(TIM5,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM5,TIM_OCPreload_Enable);
	TIM_OC3Init(TIM5,&TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM5,TIM_OCPreload_Enable);
	TIM_OC4Init(TIM5,&TIM_OCInitStructure);
	TIM_ARRPreloadConfig(TIM5,ENABLE);
	TIM_Cmd(TIM5,ENABLE);
	
	
}
void delayms(int a)
{
int i,j;
	for(i=a;i>=0;i--)
	for(j=12000;j>=0;j--)
	{
		;;
	}
}

//光电端口初始化

void GPIO_infrared_init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15;//开启光电对管的端口
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		//下拉输入
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//开启光电对管的端口
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		//下拉输入
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
}


////舵机端口初始化
void GPIO_servo_init(void)
{
	  
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}
//舵机tim初始化
void TIM_servo_init(u16 ccr)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period=(20000);	//设置自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler=(71);		//设置时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;	//设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;	//TIM 向上计数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse=ccr;

	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
}
//key2初始化
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE); //使能PORTE
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//GPIOE2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
	GPIO_Init(GPIOE, &GPIO_InitStructure); //初始化GPIOE2

}
//按键中断初始化
void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	KEY_Init(); //按键端口初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //开启 AFIO 时钟
	//GPIOE.2 中断线以及中断初始化配置,下降沿触发
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure); 
		
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn; //使能按键外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; //抢占优先级 2，
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //子优先级 2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道

	NVIC_Init(&NVIC_InitStructure);
}


