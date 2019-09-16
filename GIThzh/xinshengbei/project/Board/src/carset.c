
#include "stm32f10x.h"
#include "carset.h"




//����˿ڳ�ʼ��

void GPIO_motor_init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//ʹ�� GPIO ����ʱ��
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//����˿�
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
}

//���tim��ʼ��
void TIM_motor_init(u16 ccr)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period=500;	//�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler=71;		//����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=0;	 //����ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;	//TIM ���ϼ���
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);		//��ʼ�� TIM3
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;			//ѡ�� PWM ģʽ 1
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;	 //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;	//������Ը�
	TIM_OCInitStructure.TIM_Pulse=ccr;
	TIM_OC1PreloadConfig(TIM5,TIM_OCPreload_Enable);	//ʹ��Ԥװ�ؼĴ���
	TIM_OC1Init(TIM5,&TIM_OCInitStructure);						//��ʼ������ TIM OC2
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

//���˿ڳ�ʼ��

void GPIO_infrared_init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15;//�������ԹܵĶ˿�
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		//��������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//�������ԹܵĶ˿�
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		//��������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
}


////����˿ڳ�ʼ��
void GPIO_servo_init(void)
{
	  
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}
//���tim��ʼ��
void TIM_servo_init(u16 ccr)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period=(20000);	//�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler=(71);		//����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;	//����ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;	//TIM ���ϼ���
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
//key2��ʼ��
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE); //ʹ��PORTE
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//GPIOE2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
	GPIO_Init(GPIOE, &GPIO_InitStructure); //��ʼ��GPIOE2

}
//�����жϳ�ʼ��
void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	KEY_Init(); //�����˿ڳ�ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //���� AFIO ʱ��
	//GPIOE.2 �ж����Լ��жϳ�ʼ������,�½��ش���
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure); 
		
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn; //ʹ�ܰ����ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; //��ռ���ȼ� 2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //�����ȼ� 2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��

	NVIC_Init(&NVIC_InitStructure);
}


