/**********************************************************************************************************/
#include "stm32f10x.h"

#define  LEN3  10

/**********************************************************************************************************
*�� �� ��: USART3_Configuration(void)
*����˵��: ��ʼ��CPU��USART3����Ӳ���豸�������ж�
*��    �Σ���
*�� �� ֵ: ��
**********************************************************************************************************/
void USART3_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
    
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  // ʹ�ܸ�������ʱ�ӺͶ�Ӧ��IOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); // ʹ�ܴ���ʱ��
	
	USART_InitStructure.USART_BaudRate = 115200;                //����115200bps
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;      //ֹͣλ1λ
	USART_InitStructure.USART_Parity = USART_Parity_No;         //��У��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  //�շ�ģʽ
	USART_Init(USART3, &USART_InitStructure);                        //���ô��ڲ�������
	
	USART_Cmd(USART3, ENABLE);// ʹ�� USART�� �������
	
	/* �������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ
	�����������1���ֽ��޷���ȷ���ͳ�ȥ�����⣺ �巢����ɱ�־��Transmission Complete flag */
	USART_ClearFlag(USART3, USART_FLAG_TC);  //USART_FLAG_TC ������ɱ�־
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);   //ʹ�ܽ����ж�
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);   //ʹ�ܿ����ж�
	//USART_ITConfig(USART3, USART_IT_TXE, ENABLE);  //ʹ��"���ͻ����"�ж�     ���жϷ���֮ǰʹ��
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
*�� �� ��: void usart3_send(void)
*����˵��: USART3��BN�ֽ�
*��    �Σ���
*�� �� ֵ: ��
**********************************************************************************************************/
void usart3_send(u8 *trbuf,u16 BN)
{
	u16 i;
	for(i=0;i<BN;i++)
	{
		USART_SendData(USART3,trbuf[i]);   //����ʱ����TXE
		while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET); //�ȴ��������
	}
}
/**********************************************************************************************************
*�� �� ��: void USART3_IRQHandler(void)
*����˵��: ����3 �жϷ������
*��    �Σ���
*�� �� ֵ: ��
**********************************************************************************************************/
void USART3_IRQHandler(void)
{
	u8 clear=clear;
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)	//�����յ�1���ֽ�
	{
		rebuf3[rcvcnt3++]=USART3->DR;	//��DR�Ĵ��� 
    if(rcvcnt3>=LEN3)
		{
			rcvcnt3=LEN3;
		}				
	}
	else if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)	//�����յ�1֡����
	{
		clear=USART3->SR;	//��SR�Ĵ���
		clear=USART3->DR;	//��DR�Ĵ���(�ȶ�SR�ٶ�DR������Ϊ�����IDLE�ж�)		
		
		Re_update3=0xAA;
 
	}		
	if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)	//�����Ϊ�˱���STM32 USART ��һ���ֽڷ�����ȥ��BUG
	{
		USART_ITConfig(USART3, USART_IT_TXE, DISABLE); //��ֹ�����������жϣ�
	}
}

