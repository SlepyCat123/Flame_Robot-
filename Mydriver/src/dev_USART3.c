/**********************************************************************************************************/
#include "stm32f10x.h"

#define  LEN3  10

/**********************************************************************************************************
*函 数 名: USART3_Configuration(void)
*功能说明: 初始化CPU的USART3串口硬件设备，接收中断
*形    参：无
*返 回 值: 无
**********************************************************************************************************/
void USART3_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
    
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  // 使能复用总线时钟和对应的IO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); // 使能串口时钟
	
	USART_InitStructure.USART_BaudRate = 115200;                //速率115200bps
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;      //停止位1位
	USART_InitStructure.USART_Parity = USART_Parity_No;         //无校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件流控
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  //收发模式
	USART_Init(USART3, &USART_InitStructure);                        //配置串口参数函数
	
	USART_Cmd(USART3, ENABLE);// 使能 USART， 配置完毕
	
	/* 串口配置好，如果直接Send，则第1个字节发送不出去
	如下语句解决第1个字节无法正确发送出去的问题： 清发送完成标志，Transmission Complete flag */
	USART_ClearFlag(USART3, USART_FLAG_TC);  //USART_FLAG_TC 传输完成标志
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);   //使能接收中断
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);   //使能空闲中断
	//USART_ITConfig(USART3, USART_IT_TXE, ENABLE);  //使能"发送缓冲空"中断     在中断发送之前使能
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	
//	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//	NVIC_Init(&NVIC_InitStructure);
//	
//	USART_Cmd(USART1, ENABLE);
	
}
extern  u16 rcvcnt3;
extern  u8 Re_update3,state_machine3,rcvdat3;
extern  u8 rebuf3[LEN3];

/**********************************************************************************************************
*函 数 名: void usart3_send(void)
*功能说明: USART3发BN字节
*形    参：无
*返 回 值: 无
**********************************************************************************************************/
void usart3_send(u8 *trbuf,u16 BN)
{
	u16 i;
	for(i=0;i<BN;i++)
	{
		USART_SendData(USART3,trbuf[i]);   //发送时，清TXE
		while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET); //等待发送完毕
	}
}
/**********************************************************************************************************
*函 数 名: void USART3_IRQHandler(void)
*功能说明: 串口3 中断服务程序
*形    参：无
*返 回 值: 无
**********************************************************************************************************/
void USART3_IRQHandler(void)
{
	u8 clear=clear;
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)	//若接收到1个字节
	{
		rebuf3[rcvcnt3++]=USART3->DR;	//读DR寄存器 
    if(rcvcnt3>=LEN3)
		{
			rcvcnt3=LEN3;
		}				
	}
	else if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)	//若接收到1帧数据
	{
		clear=USART3->SR;	//读SR寄存器
		clear=USART3->DR;	//读DR寄存器(先读SR再读DR，就是为了清除IDLE中断)		
		
		Re_update3=0xAA;
 
	}		
	if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)	//这段是为了避免STM32 USART 第一个字节发不出去的BUG
	{
		USART_ITConfig(USART3, USART_IT_TXE, DISABLE); //禁止发缓冲器空中断，
	}
}

