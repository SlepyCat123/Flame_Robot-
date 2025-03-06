#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>
#include <Serial.h>
#define  LEN3  10

char Serial_RxPacket[100];				//"@MSG\r\n"
uint8_t Serial_RxFlag;
extern  u16 rcvcnt3;
extern  u8 Re_update3,state_machine3,rcvdat3;
extern  u8 rebuf3[LEN3];

void Serial_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//stm32的TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//STM32的RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	USART_InitStructure.USART_BaudRate = 115200;//这个是通信速度
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//停止位一位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//发送的字节两位
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1, ENABLE);
}

void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}

void USART1_IRQHandler(void)
{
//	static uint8_t RxState = 0;
//	static uint8_t pRxPacket = 0;
//	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
//	{
//		uint8_t RxData = USART_ReceiveData(USART1);
//		
//		if (RxState == 0)
//		{
//			if (RxData == '@' && Serial_RxFlag == 0)
//			{
//				RxState = 1;
//				pRxPacket = 0;
//				//这个是包头的地方
//			}
//		}
//		else if (RxState == 1)
//		{
//			if (RxData == '\r')
//			{
//				RxState = 2;
//				//第一个停止位
//			}
//			else
//			{
//				Serial_RxPacket[pRxPacket] = RxData;
//				pRxPacket ++;
//			}
//		}
//		else if (RxState == 2)
//		{
//			if (RxData == '\n')
//			{
//				RxState = 0;
//				Serial_RxPacket[pRxPacket] = '\0';
//				Serial_RxFlag = 1;
//				//第二个停止位
//			}
//		}
//		
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//	}
    
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
