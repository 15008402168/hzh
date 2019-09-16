#include "stm32f10x.h"
#include "usart.h"
#include "serialport.h"
	  
/**
  *@brief  gpio����
  *@param  None
  *@retval None
  **/
static void USART_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(USART_GPIO_CLK, ENABLE);   //�򿪶˿�ʱ��
	
	//USART1_TX   GPIOA.10
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX;           //PA.10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	        //�����������
	GPIO_Init(DEBUG_USART_GPIO_PORT, &GPIO_InitStructure);  //��ʼ��GPIOA.2
   
	//USART1_RX	  GPIOA.11��ʼ��
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX;//PA.11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(DEBUG_USART_GPIO_PORT, &GPIO_InitStructure);//��ʼ��GPIOA.3 
}


/**
  *@brief  USART����
  *@param  bound ��������
  *@retval None
  **/
static void USART_Mode_Config(uint32_t bound)
{
	USART_InitTypeDef USART_InitStructure;
#if APB_CLK
	RCC_APB2PeriphClockCmd(USART_CLK, ENABLE);
#else
	RCC_APB1PeriphClockCmd(USART_CLK, ENABLE);
#endif
	
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(DEBUG_USART, &USART_InitStructure); //��ʼ������1
	
	USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_Cmd(DEBUG_USART, ENABLE);                    //ʹ�ܴ���1 
}

/**
  *@brief  USART�ж�����
  *@param  None
  *@retval None
  **/
static void USART_NVIC_Config()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//Usart1 NVIC ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}

/**
  *@brief  USART��ʼ��
  *@param  None
  *@retval None
  **/
void USART_Config()
{
	USART_GPIO_Config();
	USART_NVIC_Config();
	USART_Mode_Config(9600);
}
void DEBUG_USART_IRQHandler(void)
{
	uint8_t Receive;
	while(USART_GetITStatus(DEBUG_USART, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Receive = USART_ReceiveData(DEBUG_USART);	//��ȡ���յ�������
	}
	Get_Serial_Info(Receive, &g_serialinfo);
}


/***************�������´���,֧��printf����,������Ҫѡ��use MicroLIB***********************/
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((DEBUG_USART->SR&0X40)==0){};//ѭ������,ֱ���������   
    DEBUG_USART->DR = (u8) ch;      
	return ch;
}
#endif 
/****************************************************************************************/
