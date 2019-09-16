#include "stm32f10x.h"
#include "usart.h"
#include "serialport.h"
	  
/**
  *@brief  gpio配置
  *@param  None
  *@retval None
  **/
static void USART_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(USART_GPIO_CLK, ENABLE);   //打开端口时钟
	
	//USART1_TX   GPIOA.10
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX;           //PA.10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	        //复用推挽输出
	GPIO_Init(DEBUG_USART_GPIO_PORT, &GPIO_InitStructure);  //初始化GPIOA.2
   
	//USART1_RX	  GPIOA.11初始化
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX;//PA.11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(DEBUG_USART_GPIO_PORT, &GPIO_InitStructure);//初始化GPIOA.3 
}


/**
  *@brief  USART配置
  *@param  bound ：波特率
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
	
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(DEBUG_USART, &USART_InitStructure); //初始化串口1
	
	USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_Cmd(DEBUG_USART, ENABLE);                    //使能串口1 
}

/**
  *@brief  USART中断配置
  *@param  None
  *@retval None
  **/
static void USART_NVIC_Config()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//Usart1 NVIC 配置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
}

/**
  *@brief  USART初始化
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
	while(USART_GetITStatus(DEBUG_USART, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Receive = USART_ReceiveData(DEBUG_USART);	//读取接收到的数据
	}
	Get_Serial_Info(Receive, &g_serialinfo);
}


/***************加入以下代码,支持printf函数,而不需要选择use MicroLIB***********************/
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((DEBUG_USART->SR&0X40)==0){};//循环发送,直到发送完毕   
    DEBUG_USART->DR = (u8) ch;      
	return ch;
}
#endif 
/****************************************************************************************/
