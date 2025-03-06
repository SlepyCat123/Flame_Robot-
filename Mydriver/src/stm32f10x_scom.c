/*******************************************************************************
  * @file    stm32f10x_scom.c
  * @author  W. Dong
  * @version V1.0.1
  * @date    23/09/2022
  * @brief   ��������  ���ú����ٷ�������	
*******************************************************************************/

#include "stm32f10x_scom.h"	 
#include <string.h>


typedef struct __SCOM_RX_Buffer_Struct
{  
   uint8_t      len;                           /*���ڽ��ջ������ݵ���Ч����*/ 
   uint8_t      data[RX_BUFFER_MAX_SIZE];      /*���ڽ��ջ�������*/
} SCOM_RX_Buffer_Struct;

/** 
  * @brief  SCOM_TX_Buffer structure definition
  */

typedef struct __SCOM_TX_Buffer_Struct
{  
   uint8_t      len;                          /*���ڷ��ͻ������ݵ���Ч����*/ 
   uint8_t      data[TX_BUFFER_MAX_SIZE];     /*���ڷ��ͻ�������*/
} SCOM_TX_Buffer_Struct;

/* --------------------------- SCOM_BASE --------------------------- */
SCOM_TypeDef_Struct       SCOM1_BASE, SCOM2_BASE, SCOM3_BASE;

/* --------------------------- �ж�  �洢���� ---------------------- */
static  uint32_t           __SCOM_CPU_PRIMASK_REG_SAVE_VALUE;

/* --------------------------- ���ͽ��ջ����� ---------------------- */
SCOM_RX_Buffer_Struct      SCOM1_rxDataBuffer;     //��Ŵ��ڷ���������
SCOM_TX_Buffer_Struct      SCOM1_txDataBuffer;     //��ŷ������ڵ�����

SCOM_RX_Buffer_Struct      SCOM2_rxDataBuffer;
SCOM_TX_Buffer_Struct      SCOM2_txDataBuffer;

SCOM_RX_Buffer_Struct      SCOM3_rxDataBuffer;
SCOM_TX_Buffer_Struct      SCOM3_txDataBuffer;

/* --------------------------- ������������ ---------------------- */

//�յ�����֡�󣬽����ջ��������ݴ��ڴ˱��������û���������ȡ
SCOM_READ_DATA_Struct      SCOM1_rxData;
SCOM_READ_DATA_Struct      SCOM2_rxData;
SCOM_READ_DATA_Struct      SCOM3_rxData;

/*********************  SCOM_Private_Function Prototypes***********************************/

static __INLINE void __SCOM_Disable_IRQ(void);    //���жϺ���
static __INLINE void __SCOM_Restore_IRQ(void);    //���жϺ���

ErrorStatus SCOM_USART_SendData(SCOM_TypeDef_Struct *SCOMx);

/*********************  SCOM_Private_Function  ********************************************/

/*****************************************************************
  * @brief   ���ж�                                              *
  * @param   void                                                *
  * @retval  void                                                *
*****************************************************************/	
static __INLINE void __SCOM_Disable_IRQ(void)
{
    __SCOM_CPU_PRIMASK_REG_SAVE_VALUE = __get_PRIMASK();
	  __disable_irq();
}

/*****************************************************************
  * @brief   ���ж�                                              *
  * @param   void                                                *
  * @retval  void                                                *
*****************************************************************/	
static __INLINE void __SCOM_Restore_IRQ(void)
{
    __set_PRIMASK(__SCOM_CPU_PRIMASK_REG_SAVE_VALUE) ;
}

/*****************************************************************************************
  * @brief   ��DMAģʽ��ָ���Ĵ���д������                                               *
  * @param   SCOMx: д�����ݵĴ��ڣ�x ������1 to SCOM_NUM_USED.                          *                                               
  * @retval  ERROR or SUCCESS.                                                           *
*****************************************************************************************/	
ErrorStatus SCOM_USART_SendData(SCOM_TypeDef_Struct *SCOMx)
{
		static uint8_t  cnt[3] = {0};      //���ڷ����ֽڸ���
	
    if(SCOMx  == NULL)
			  return ERROR;
		
    if(SCOMx == SCOM1)
		{			
				if(cnt[0] < SCOM1_txDataBuffer.len)
				{
					 USART_SendData(SCOMx->SCOM_Hardware.USARTx, (uint16_t)SCOM1_txDataBuffer.data[cnt[0]]);
					 cnt[0] ++;
				}
				else       
				{
					 SCOMx->SCOM_Operating.USART_txAllowFlag = SET;
					 cnt[0] = 0;
				}
	  }
    else if(SCOMx == SCOM2)
		{			
				if(cnt[1] < SCOM2_txDataBuffer.len)
				{
					 USART_SendData(SCOMx->SCOM_Hardware.USARTx, (uint16_t)SCOM2_txDataBuffer.data[cnt[1]]);
					 cnt[1] ++;
				}
				else 
				{
					 SCOMx->SCOM_Operating.USART_txAllowFlag = SET;
					 cnt[1] = 0;
				}
	  }		
    else if(SCOMx == SCOM3)
		{			
				if(cnt[2] < SCOM3_txDataBuffer.len)
				{
					 USART_SendData(SCOMx->SCOM_Hardware.USARTx, (uint16_t)SCOM3_txDataBuffer.data[cnt[2]]);
					 cnt[2] ++;
				}
				else 
				{
					 SCOMx->SCOM_Operating.USART_txAllowFlag = SET;
					 cnt[2] = 0;
				}
	  }			
    else 
        return ERROR;			
		
		return SUCCESS;		
}		
/*********************  SCOM_Exported_Function  ******************************************/


/*******************************************************************************************     
  * @brief  ��Ĭ�ϲ������ SCOM_InitStruct.                                                *
  * @param  SCOM_InitStruct : ��Ҫ����ʼ���� SCOM_InitTypeDef_structure ���͵����ݽṹ     *
  * @retval  None                                                                          *
*******************************************************************************************/
void SCOM_StructInit(SCOM_InitTypeDef_Struct* SCOMx_InitStruct)
{
    SCOMx_InitStruct->enable_SCOM   = ENABLE_SCOM_DEFAULT;
	SCOMx_InitStruct->enable_DMA    = ENABLE_DMA_DEFAULT;
	SCOMx_InitStruct->commMode      = SCOM_COMMMODE_DEFAULT;                        
	
	USART_StructInit(&SCOMx_InitStruct->usartInitParm);
	
	SCOMx_InitStruct->usartInitParm.USART_BaudRate     = SCOM_BAUDRATE_DEFAULT;
	SCOMx_InitStruct->usartInitParm.USART_Parity       = SCOM_PARITY_DEFAULT;
    SCOMx_InitStruct->usartInitParm.USART_StopBits     = SCOM_STOPBIT_DEFAULT;
    SCOMx_InitStruct->usartInitParm.USART_WordLength   = SCOM_WORDLENGTH_DEFAULT;
    SCOMx_InitStruct->usartInitParm.USART_HardwareFlowControl = SCOM_HARDWAREFLOWCONTROL_DEFAULT;	
	
    if(SCOMx_InitStruct->commMode == Comm_RX)	
		    SCOMx_InitStruct->usartInitParm.USART_Mode = USART_Mode_Rx;
    else if(SCOMx_InitStruct->commMode == Comm_TX)
		    SCOMx_InitStruct->usartInitParm.USART_Mode = USART_Mode_Tx;
	else
		    SCOMx_InitStruct->usartInitParm.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	SCOMx_InitStruct->SCOM_USART_PreemptionPriority      = SCOM_USART_PREEMPTIONPRIORITY_DEFAULT;
    SCOMx_InitStruct->SCOM_USART_SubPriority             = SCOM_USART_SUBPRIORITY_DEFAULT;
	SCOMx_InitStruct->SCOM_DMA_PreemptionPriority        = SCOM_DMA_PREEMPTIONPRIORITY_DEFAULT;
	SCOMx_InitStruct->SCOM_DMA_SubPriority               = SCOM_DMA_SUBPRIORITY_DEFAULT;
}

/*******************************************************************************************
  * @brief  ���ݳ�ʼ�����SCOM_InitStruct ��ʼ������ SCOMx                                 *
  * @param  SCOMx: ָ����Ҫ��ʼ���Ĵ��ڣ�x ������1 to 3.                                   *
  * @param  SCOM_InitStruct : �Ѿ�����ʼ���� SCOM_InitTypeDef_Struct ���͵����ݽṹ        *
  * @retval ERROR or SUCCESS.                                                              *

*******************************************************************************************/
ErrorStatus SCOM_Init(SCOM_TypeDef_Struct* SCOMx, SCOM_InitTypeDef_Struct* SCOMx_InitStruct)
{
	  GPIO_InitTypeDef     GPIO_InitStructure;
	  DMA_InitTypeDef      DMA_InitStructure;
      NVIC_InitTypeDef     NVIC_InitStructure;  
	
		if ( (SCOMx == NULL) || (SCOMx_InitStruct == NULL) )
		{
				return ERROR;
		}
		  /** Ӳ����ʼ��*****/
		if (SCOMx == SCOM1)
		{
        SCOM1_BASE.SCOM_Hardware.USARTx = SCOM1_USART;		
		}		
		else if(SCOMx == SCOM2)
		{
        SCOM2_BASE.SCOM_Hardware.USARTx = SCOM2_USART;		
		}
		else if(SCOMx == SCOM3)
		{
        SCOM3_BASE.SCOM_Hardware.USARTx = SCOM3_USART;		
		}
    else
		{
        return ERROR;
		}			
		
		if (SCOMx->SCOM_Hardware.USARTx == USART1)
		{
		    SCOMx->SCOM_Hardware.rx_GPIOx              = GPIOA;
		    SCOMx->SCOM_Hardware.rx_GPIO_Pin           = GPIO_Pin_10;			
			SCOMx->SCOM_Hardware.rx_DMAy_Channelx      = DMA1_Channel5;
			SCOMx->SCOM_Hardware.rx_DMAy_Channelx_IRQn = 15;
			SCOMx->SCOM_Hardware.tx_GPIOx              = GPIOA;
			SCOMx->SCOM_Hardware.tx_GPIO_Pin           = GPIO_Pin_9;
			SCOMx->SCOM_Hardware.tx_DMAy_Channelx      = DMA1_Channel4;
			SCOMx->SCOM_Hardware.tx_DMAy_Channelx_IRQn = 14;
			SCOMx->SCOM_Hardware.USARTx_IRQn           = 37;			
		}
		else if (SCOMx->SCOM_Hardware.USARTx == USART2)
		{
		    SCOMx->SCOM_Hardware.rx_GPIOx              = GPIOA;
		    SCOMx->SCOM_Hardware.rx_GPIO_Pin           = GPIO_Pin_3;			
			SCOMx->SCOM_Hardware.rx_DMAy_Channelx      = DMA1_Channel6;
			SCOMx->SCOM_Hardware.rx_DMAy_Channelx_IRQn = 16;
			SCOMx->SCOM_Hardware.tx_GPIOx              = GPIOA;
			SCOMx->SCOM_Hardware.tx_GPIO_Pin           = GPIO_Pin_2;
			SCOMx->SCOM_Hardware.tx_DMAy_Channelx      = DMA1_Channel7;
		    SCOMx->SCOM_Hardware.tx_DMAy_Channelx_IRQn = 17;	
			SCOMx->SCOM_Hardware.USARTx_IRQn           = 38;					
		}
		else if (SCOMx->SCOM_Hardware.USARTx == USART3)
		{
		    SCOMx->SCOM_Hardware.rx_GPIOx              = GPIOB;
		    SCOMx->SCOM_Hardware.rx_GPIO_Pin           = GPIO_Pin_11;			
			SCOMx->SCOM_Hardware.rx_DMAy_Channelx      = DMA1_Channel3;
			SCOMx->SCOM_Hardware.rx_DMAy_Channelx_IRQn = 13;
			SCOMx->SCOM_Hardware.tx_GPIOx              = GPIOB;
			SCOMx->SCOM_Hardware.tx_GPIO_Pin           = GPIO_Pin_10;
			SCOMx->SCOM_Hardware.tx_DMAy_Channelx      = DMA1_Channel2;
			SCOMx->SCOM_Hardware.tx_DMAy_Channelx_IRQn = 12;
			SCOMx->SCOM_Hardware.USARTx_IRQn           = 39;					
		}		
		else
		{
			  return ERROR;	
		}			
		
    GPIO_StructInit(&GPIO_InitStructure);

  	GPIO_InitStructure.GPIO_Pin = SCOMx->SCOM_Hardware.tx_GPIO_Pin;					
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
  	GPIO_Init(SCOMx->SCOM_Hardware.tx_GPIOx, &GPIO_InitStructure);
	  
    GPIO_InitStructure.GPIO_Pin = SCOMx->SCOM_Hardware.rx_GPIO_Pin; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(SCOMx->SCOM_Hardware.rx_GPIOx, &GPIO_InitStructure);				

      /**�������ó�ʼ��**/
    SCOMx->SCOM_Operating.enable_SCOM = SCOMx_InitStruct->enable_SCOM;	 /*enable_SCOM*/
		
    if ((SCOMx->SCOM_Hardware.tx_DMAy_Channelx == NULL) ||
	(SCOMx->SCOM_Hardware.rx_DMAy_Channelx == NULL))
	 SCOMx->SCOM_Operating.enable_DMA = DISABLE;
    else
	 SCOMx->SCOM_Operating.enable_DMA = SCOMx_InitStruct->enable_DMA;  /*enable_DMA*/	

    if(SCOMx->SCOM_Operating.enable_DMA != DISABLE)	
    {
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		}	

	SCOMx->SCOM_Operating.commMode = SCOMx_InitStruct->commMode;
		
		/*Initializing rx  buffer  txstart Flag  */		
    SCOM1_rxDataBuffer.len  = 0;
    SCOM2_rxDataBuffer.len  = 0;
    SCOM3_rxDataBuffer.len  = 0;			  
    SCOM1_txDataBuffer.len  = 0;
    SCOM2_txDataBuffer.len  = 0;
    SCOM3_txDataBuffer.len  = 0;

    SCOM1_rxData.Fresh  = RESET;
    SCOM2_rxData.Fresh  = RESET;
    SCOM3_rxData.Fresh  = RESET;		
		
		// USART_txStartFlag
    SCOMx->SCOM_Operating.USART_txAllowFlag = SET;    		

   /* -----Initializing Hardware, including GPIO, USART, DMA, NVIC--------*/	

    if(SCOMx_InitStruct->commMode == Comm_RX)	
		    SCOMx_InitStruct->usartInitParm.USART_Mode = USART_Mode_Rx;
		else if(SCOMx_InitStruct->commMode == Comm_TX)
		    SCOMx_InitStruct->usartInitParm.USART_Mode = USART_Mode_Tx;
		else
		    SCOMx_InitStruct->usartInitParm.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		
		SCOMx->SCOM_Operating.USART_Parm = SCOMx_InitStruct->usartInitParm;
		
		USART_Init(SCOMx->SCOM_Hardware.USARTx, &SCOMx_InitStruct->usartInitParm);
				
		if ( SCOMx->SCOM_Operating.enable_DMA == DISABLE )
		{
				USART_ITConfig(SCOMx->SCOM_Hardware.USARTx, USART_IT_RXNE, ENABLE);
  			USART_ITConfig(SCOMx->SCOM_Hardware.USARTx, USART_IT_TC, ENABLE); 			
		}
		else
		{         
        if((SCOMx->SCOM_Hardware.rx_DMAy_Channelx  != NULL) &(SCOMx->SCOM_Hardware.tx_DMAy_Channelx  != NULL))
  		       USART_DMACmd(SCOMx->SCOM_Hardware.USARTx, USART_DMAReq_Rx | USART_DMAReq_Tx, ENABLE);			
		}
		
		USART_ITConfig(SCOMx->SCOM_Hardware.USARTx, USART_IT_IDLE, ENABLE);

    if((SCOMx->SCOM_Hardware.rx_DMAy_Channelx  != NULL) &(SCOMx->SCOM_Hardware.tx_DMAy_Channelx  != NULL))
		{
				if ( SCOMx->SCOM_Operating.enable_DMA == ENABLE )
				{   
						DMA_DeInit(SCOMx->SCOM_Hardware.rx_DMAy_Channelx);
						DMA_InitStructure.DMA_PeripheralBaseAddr 	= (u32)(&SCOMx->SCOM_Hardware.USARTx->DR);
					
					  if(SCOMx == SCOM1)			
			    	    DMA_InitStructure.DMA_MemoryBaseAddr 			= (u32)(SCOM1_rxDataBuffer.data);
						else if(SCOMx == SCOM2)
			    	    DMA_InitStructure.DMA_MemoryBaseAddr 			= (u32)(SCOM2_rxDataBuffer.data);	
						else if(SCOMx == SCOM3)
			    	    DMA_InitStructure.DMA_MemoryBaseAddr 			= (u32)(SCOM3_rxDataBuffer.data);	
						
  					DMA_InitStructure.DMA_DIR 								= DMA_DIR_PeripheralSRC;
						DMA_InitStructure.DMA_BufferSize 					= RX_BUFFER_MAX_SIZE;
						DMA_InitStructure.DMA_PeripheralInc 			= DMA_PeripheralInc_Disable;
						DMA_InitStructure.DMA_MemoryInc 					= DMA_MemoryInc_Enable;
						DMA_InitStructure.DMA_PeripheralDataSize 	= DMA_PeripheralDataSize_Byte;
						DMA_InitStructure.DMA_MemoryDataSize 			= DMA_MemoryDataSize_Byte;
						DMA_InitStructure.DMA_Mode 								= DMA_Mode_Normal;
						DMA_InitStructure.DMA_Priority 						= DMA_Priority_VeryHigh;
						DMA_InitStructure.DMA_M2M 								= DMA_M2M_Disable;
          
						DMA_Init(SCOMx->SCOM_Hardware.rx_DMAy_Channelx, &DMA_InitStructure);	
					 			
						DMA_SetCurrDataCounter(SCOMx->SCOM_Hardware.rx_DMAy_Channelx,RX_BUFFER_MAX_SIZE);

						DMA_DeInit(SCOMx->SCOM_Hardware.tx_DMAy_Channelx);
						
					  if(SCOMx == SCOM1)			
			    	    DMA_InitStructure.DMA_MemoryBaseAddr 			= (u32)(SCOM1_txDataBuffer.data);
						else if(SCOMx == SCOM2)
			    	    DMA_InitStructure.DMA_MemoryBaseAddr 			= (u32)(SCOM2_txDataBuffer.data);	
						else if(SCOMx == SCOM3)
			    	    DMA_InitStructure.DMA_MemoryBaseAddr 			= (u32)(SCOM3_txDataBuffer.data);	
						
						DMA_InitStructure.DMA_DIR 								= DMA_DIR_PeripheralDST;
						DMA_InitStructure.DMA_BufferSize 					= TX_BUFFER_MAX_SIZE;
						DMA_Init(SCOMx->SCOM_Hardware.tx_DMAy_Channelx, &DMA_InitStructure);
						
						DMA_ITConfig(SCOMx->SCOM_Hardware.tx_DMAy_Channelx,DMA_IT_TC,ENABLE);						 
						DMA_SetCurrDataCounter(SCOMx->SCOM_Hardware.tx_DMAy_Channelx,0);
				}
	  }

		NVIC_InitStructure.NVIC_IRQChannel                        = SCOMx->SCOM_Hardware.USARTx_IRQn; 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority      = SCOMx_InitStruct->SCOM_USART_PreemptionPriority;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority             = SCOMx_InitStruct->SCOM_USART_SubPriority;
		NVIC_InitStructure.NVIC_IRQChannelCmd                     = ENABLE; 
		NVIC_Init(&NVIC_InitStructure); 
		
		/*------------NVIC configure--------*/

		if ( SCOMx->SCOM_Operating.enable_DMA == ENABLE )
		{   
				NVIC_InitStructure.NVIC_IRQChannel 										= SCOMx->SCOM_Hardware.tx_DMAy_Channelx_IRQn;
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= SCOMx_InitStruct->SCOM_DMA_PreemptionPriority;
				NVIC_InitStructure.NVIC_IRQChannelSubPriority 				= SCOMx_InitStruct->SCOM_DMA_SubPriority;
				NVIC_InitStructure.NVIC_IRQChannelCmd 								= ENABLE;
				NVIC_Init(&NVIC_InitStructure);		
		}

    if((SCOMx->SCOM_Hardware.rx_DMAy_Channelx  != NULL) &(SCOMx->SCOM_Hardware.tx_DMAy_Channelx  != NULL))
		{
	      if(SCOMx->SCOM_Operating.enable_DMA == ENABLE)
			  {
			      DMA_Cmd(SCOMx->SCOM_Hardware.rx_DMAy_Channelx, ENABLE);		
			      DMA_Cmd(SCOMx->SCOM_Hardware.tx_DMAy_Channelx, ENABLE);			
			  }
			  else 
			  {
			      DMA_Cmd(SCOMx->SCOM_Hardware.rx_DMAy_Channelx, DISABLE);		
			      DMA_Cmd(SCOMx->SCOM_Hardware.tx_DMAy_Channelx, DISABLE);			
			  }
	  }		

		USART_Cmd(SCOMx->SCOM_Hardware.USARTx, ENABLE);	
		USART_ClearFlag(SCOMx->SCOM_Hardware.USARTx,USART_FLAG_TC);

		return SUCCESS;
}
/******************************************************************************************
  * @brief  ��ʼ��SCOM                                                                    *
                                                            *
******************************************************************************************/
ErrorStatus MY_SCOM_Init(SCOM_TypeDef_Struct* SCOMx)
{
    SCOM_InitTypeDef_Struct  SCOMx_InitStruct;
    
    SCOM_StructInit(&SCOMx_InitStruct);  //װ��
    SCOM_Init(SCOMx, &SCOMx_InitStruct); //��ʼ��
    return SUCCESS;
}
/******************************************************************************************
  * @brief  �򿪴���.                                                                     *
  * @param  SCOMx: ָ����Ҫ�򿪵Ĵ��ڣ�x ������1 to 3.                                    *
  * @retval ERROR or SUCCESS.                                                             *
******************************************************************************************/
ErrorStatus SCOM_Open(SCOM_TypeDef_Struct* SCOMx)
{
   if(SCOMx == NULL) 
		  return ERROR;
	 
	 USART_Cmd(SCOMx->SCOM_Hardware.USARTx,ENABLE);
	
   if((SCOMx->SCOM_Hardware.rx_DMAy_Channelx  != NULL) &(SCOMx->SCOM_Hardware.tx_DMAy_Channelx  != NULL)
	              &&(SCOMx->SCOM_Operating.enable_DMA !=DISABLE))
	 {
			   DMA_Cmd(SCOMx->SCOM_Hardware.rx_DMAy_Channelx, ENABLE);
		 		 DMA_Cmd(SCOMx->SCOM_Hardware.tx_DMAy_Channelx, ENABLE);	
	 }

	 return SUCCESS;
}


/******************************************************************************************
  * @brief  �رմ���.                                                                     *
  * @param  SCOMx: ָ����Ҫ�򿪵Ĵ��ڣ�x ������1 to SCOM_NUM_USED.                        *
  * @retval ERROR or SUCCESS.                                                             *
******************************************************************************************/
ErrorStatus SCOM_Off(SCOM_TypeDef_Struct* SCOMx)
{
    if(SCOMx == NULL) return ERROR;
		USART_Cmd(SCOMx->SCOM_Hardware.USARTx,DISABLE);
		
		if(SCOMx->SCOM_Operating.enable_DMA ==ENABLE)
		{
			DMA_Cmd(SCOMx->SCOM_Hardware.rx_DMAy_Channelx, DISABLE);
		  DMA_Cmd(SCOMx->SCOM_Hardware.tx_DMAy_Channelx, DISABLE);				
		}
	  return SUCCESS;
}

/*****************************************************************************************
  * @brief   �Ӵ��ڶ�ȡ����.                                                             *
  * @param   SCOMx:  ��ȡ���ݵĴ��ڣ�x ������1 to 3.                                     *
  * @param   pdata: ָ��SCOM_READ_DATA_Struct���͵����ݽṹ�����ڴ洢ȡ�صĴ�������      *	
  *              Fresh                       �������ݸ��±�־                            *
	*              len                         ���ڶ������ݵ���Ч����                      *
  *              data[len]                   ���ڶ�������                                *
  * @retval  ERROR or SUCCESS.                                                           *
*****************************************************************************************/
ErrorStatus SCOM_ReadData(SCOM_TypeDef_Struct*SCOMx, SCOM_READ_DATA_Struct* pdata)
{	     
		if((SCOMx == NULL)|| (pdata == NULL)) 
				return ERROR;
				
		pdata->Fresh = SET;			

		if(SCOMx == SCOM1)
		{				  
				if(SCOM1_rxData.Fresh == SET)
				{
						__SCOM_Disable_IRQ();
						pdata->Fresh = SET;
						pdata->len =  SCOM1_rxDataBuffer.len;
						memcpy(pdata->data, SCOM1_rxData.data, pdata->len);
						SCOM1_rxData.Fresh = RESET;
						__SCOM_Restore_IRQ();
				}
				else
				    pdata->Fresh = RESET; 	
		}
    else if(SCOMx == SCOM2)
		{				  
				if(SCOM2_rxData.Fresh == SET)
				{
						__SCOM_Disable_IRQ();
						pdata->Fresh = SET;
						pdata->len =  SCOM2_rxDataBuffer.len;
						memcpy(pdata->data, SCOM2_rxData.data, pdata->len);
						SCOM2_rxData.Fresh = RESET;
						__SCOM_Restore_IRQ();
				}
				else
				    pdata->Fresh = RESET; 				
		}
    else if(SCOMx == SCOM3)
		{				  
				if(SCOM3_rxData.Fresh == SET)
				{
						__SCOM_Disable_IRQ();
						pdata->Fresh = SET;
						pdata->len =  SCOM3_rxDataBuffer.len;
						memcpy(pdata->data, SCOM3_rxData.data, pdata->len);
						SCOM3_rxData.Fresh = RESET;
						__SCOM_Restore_IRQ();
				}
				else
				    pdata->Fresh = RESET; 				
		}
    else 
			  return ERROR;

			return SUCCESS;
}


/*****************************************************************************************
  * @brief   ��ָ���Ĵ���д�����ݣ����ڷ��������־SETʱ������д�����ݷ���               *
  * @param   SCOMx: д�����ݵĴ��ڣ�x ������1 to 3.                                      *
  * @param   pdata: ָ�� SCOM_WRITE_DATA_Struct ���͵Ĵ���д������.                      *                                                *
  * @retval  ERROR or SUCCESS.                                                           *
*****************************************************************************************/
ErrorStatus SCOM_WriteData(SCOM_TypeDef_Struct* SCOMx, SCOM_WRITE_DATA_Struct* pdata)
{
		if((SCOMx == NULL) || (pdata == NULL)||(pdata->len == 0)) 
			  return ERROR;

    if(SCOMx == SCOM1)
		{
		    if (SCOM1->SCOM_Operating.USART_txAllowFlag == SET)	   //��������
				{
				    SCOM1_txDataBuffer.len = pdata ->len;
				    memcpy(SCOM1_txDataBuffer.data,pdata->data, pdata->len);
					
					  if(SCOM1->SCOM_Operating.enable_DMA == ENABLE)   //ʹ��DMA
						{		
								DMA_Cmd(SCOM1->SCOM_Hardware.tx_DMAy_Channelx, DISABLE);
								DMA_SetCurrDataCounter(SCOM1->SCOM_Hardware.tx_DMAy_Channelx, (uint16_t)SCOM1_txDataBuffer.len);
								DMA_Cmd(SCOM1->SCOM_Hardware.tx_DMAy_Channelx, ENABLE);
						}
            else      //��DMA
						{			
						    SCOM_USART_SendData(SCOM1);								
						}
						    
						SCOM1->SCOM_Operating.USART_txAllowFlag = RESET;		  //����Ϊ������дSCOM					
				}							
		}			
    else if(SCOMx == SCOM2)
		{
		    if (SCOM2->SCOM_Operating.USART_txAllowFlag == SET)	
				{
				    SCOM2_txDataBuffer.len = pdata ->len;
				    memcpy(SCOM2_txDataBuffer.data,pdata->data, pdata->len);
					
					  if(SCOM2->SCOM_Operating.enable_DMA == ENABLE)   //ʹ��DMA
						{		
								DMA_Cmd(SCOM2->SCOM_Hardware.tx_DMAy_Channelx, DISABLE);
								DMA_SetCurrDataCounter(SCOM2->SCOM_Hardware.tx_DMAy_Channelx, (uint16_t)SCOM2_txDataBuffer.len);
								DMA_Cmd(SCOM2->SCOM_Hardware.tx_DMAy_Channelx, ENABLE);
						}
            else      //��DMA
						{			
						    SCOM_USART_SendData(SCOM2);								
						}
						    
						SCOM2->SCOM_Operating.USART_txAllowFlag = RESET;							
				}							
		}			
    else if(SCOMx == SCOM3)
		{
		    if (SCOM3->SCOM_Operating.USART_txAllowFlag == SET)	
				{
				    SCOM3_txDataBuffer.len = pdata ->len;
				    memcpy(SCOM3_txDataBuffer.data,pdata->data, pdata->len);
					
					  if(SCOM3->SCOM_Operating.enable_DMA == ENABLE)   //ʹ��DMA
						{		
								DMA_Cmd(SCOM3->SCOM_Hardware.tx_DMAy_Channelx, DISABLE);
								DMA_SetCurrDataCounter(SCOM3->SCOM_Hardware.tx_DMAy_Channelx, (uint16_t)SCOM3_txDataBuffer.len);
								DMA_Cmd(SCOM3->SCOM_Hardware.tx_DMAy_Channelx, ENABLE);
						}
            else      //��DMA
						{			
						    SCOM_USART_SendData(SCOM3);								
						}
						    
						SCOM3->SCOM_Operating.USART_txAllowFlag = RESET;							
				}							
		}				
    else 
			  return ERROR;

		return SUCCESS;
}


/****************************************************************************************
  * @brief   �����жϾ���ִ�еķ�����(Receive interrupt and send interrupt)           *
  * @param   SCOMx:�ж����ݵĴ��ڣ�x ������1 to SCOM_NUM_USED.                          *
  * @retval  ERROR or SUCCESS.                                                          *
****************************************************************************************/
ErrorStatus SCOM_IRQHandler(SCOM_TypeDef_Struct* SCOMx)
{
		static	uint8_t SCOM1_ByteNum  = 0;
		static	uint8_t SCOM2_ByteNum  = 0;
		static	uint8_t SCOM3_ByteNum  = 0;
	  uint16_t        clear;
	
	  if (SCOMx == NULL )  return ERROR;

	  // USARTx's rx interrupt services
	  if(USART_GetFlagStatus(SCOMx->SCOM_Hardware.USARTx,USART_IT_RXNE) == SET)
		{
				if(SCOMx->SCOM_Operating.enable_DMA != ENABLE )
				{
					  if(SCOMx == SCOM1)
						{	
								SCOM1_txDataBuffer.data[SCOM1_ByteNum] = USART_ReceiveData(SCOMx->SCOM_Hardware.USARTx);
								USART_ClearFlag(SCOMx->SCOM_Hardware.USARTx,USART_IT_RXNE);   
								SCOM1_ByteNum++;
						}
						else if(SCOMx == SCOM2)
						{	
								SCOM2_txDataBuffer.data[SCOM2_ByteNum] = USART_ReceiveData(SCOMx->SCOM_Hardware.USARTx);
								USART_ClearFlag(SCOMx->SCOM_Hardware.USARTx,USART_IT_RXNE);   /* TCIE,TE,RE */
								SCOM2_ByteNum++;
						}
						else if(SCOMx == SCOM3)
						{	
								SCOM3_txDataBuffer.data[SCOM3_ByteNum] = USART_ReceiveData(SCOMx->SCOM_Hardware.USARTx);
								USART_ClearFlag(SCOMx->SCOM_Hardware.USARTx,USART_IT_RXNE);   /* TCIE,TE,RE */
								SCOM3_ByteNum++;
						}
				 }
		}
				// USARTx's tx interrupt services
		if(USART_GetFlagStatus(SCOMx->SCOM_Hardware.USARTx,USART_FLAG_TC) == SET)
		{
			  if(SCOMx->SCOM_Operating.enable_DMA != ENABLE )
				{
				    USART_ClearFlag(SCOMx->SCOM_Hardware.USARTx,USART_FLAG_TC);    
				    SCOM_USART_SendData(SCOMx);
				}
		}

		//�����ж�
    if(USART_GetFlagStatus(SCOMx->SCOM_Hardware.USARTx,USART_FLAG_IDLE) == SET)	
		{ 
				if(SCOMx->SCOM_Operating.enable_DMA == ENABLE)
				{
						DMA_Cmd(SCOMx->SCOM_Hardware.rx_DMAy_Channelx,DISABLE);

						if(SCOMx == SCOM1)
						{
								SCOM1_ByteNum = RX_BUFFER_MAX_SIZE - DMA_GetCurrDataCounter(SCOM1->SCOM_Hardware.rx_DMAy_Channelx);
						    SCOM1->SCOM_Hardware.rx_DMAy_Channelx->CMAR =(u32)(SCOM1_rxDataBuffer.data);  
						    DMA_SetCurrDataCounter(SCOM1->SCOM_Hardware.rx_DMAy_Channelx,RX_BUFFER_MAX_SIZE);
						    DMA_Cmd(SCOM1->SCOM_Hardware.rx_DMAy_Channelx,ENABLE);						
						}					
						else if(SCOMx == SCOM2)
						{
								SCOM2_ByteNum = RX_BUFFER_MAX_SIZE - DMA_GetCurrDataCounter(SCOM2->SCOM_Hardware.rx_DMAy_Channelx);
						    SCOM2->SCOM_Hardware.rx_DMAy_Channelx->CMAR =(u32)(&SCOM2_rxDataBuffer.data[0]);  
						    DMA_SetCurrDataCounter(SCOM2->SCOM_Hardware.rx_DMAy_Channelx,RX_BUFFER_MAX_SIZE);
						    DMA_Cmd(SCOM2->SCOM_Hardware.rx_DMAy_Channelx,ENABLE);									
						}
						else if(SCOMx == SCOM3)
						{
								SCOM3_ByteNum = RX_BUFFER_MAX_SIZE - DMA_GetCurrDataCounter(SCOM3->SCOM_Hardware.rx_DMAy_Channelx);
						    SCOM3->SCOM_Hardware.rx_DMAy_Channelx->CMAR =(u32)(SCOM3_rxDataBuffer.data);  
						    DMA_SetCurrDataCounter(SCOM3->SCOM_Hardware.rx_DMAy_Channelx,RX_BUFFER_MAX_SIZE);
						    DMA_Cmd(SCOM3->SCOM_Hardware.rx_DMAy_Channelx,ENABLE);								
						}
        }
						
			  if(SCOMx == SCOM1)
				{
					  SCOM1_rxDataBuffer.len = SCOM1_ByteNum;						
						SCOM1_rxData.Fresh = SET;
						SCOM1_rxData.len =  SCOM1_rxDataBuffer.len;
						memcpy(SCOM1_rxData.data, SCOM1_rxDataBuffer.data, SCOM1_rxDataBuffer.len);
					  SCOM1_ByteNum = 0 ;	
        }					
				else if(SCOMx == SCOM2)
				{
					  SCOM2_rxDataBuffer.len = SCOM2_ByteNum;                				
						SCOM2_rxData.Fresh = SET;
						SCOM2_rxData.len =  SCOM2_rxDataBuffer.len;
						memcpy(SCOM2_rxData.data, SCOM2_rxDataBuffer.data, SCOM2_rxDataBuffer.len);
					  SCOM2_ByteNum = 0 ;	
        }
				else if(SCOMx == SCOM3)
				{     
					  SCOM3_rxDataBuffer.len = SCOM3_ByteNum;                						
						SCOM3_rxData.Fresh = SET;
						SCOM3_rxData.len =  SCOM3_rxDataBuffer.len;
						memcpy(SCOM3_rxData.data, SCOM3_rxDataBuffer.data, SCOM3_rxDataBuffer.len);
					  SCOM3_ByteNum = 0 ;
        }
				else 
					  return ERROR;
			
				//��  �����жϱ�־
				clear = SCOMx->SCOM_Hardware.USARTx->SR;
				clear = SCOMx->SCOM_Hardware.USARTx->DR;
				clear = clear;
    }					
    return SUCCESS;		
}


/****************************************************************************************
  * @brief  ���� ����DMA�жϾ���ִ�еķ�����                                          *
  * @param  SCOMx:�ж����ݵĴ��ڣ�x ������1 to 3.                                       *
  * @retval ERROR or SUCCESS.                                                           *
****************************************************************************************/
ErrorStatus	SCOM_TX_DMA_IRQHandler(SCOM_TypeDef_Struct *SCOMx)
{
    if(SCOMx == NULL)  
		{
			  return ERROR;
		}
	  if(SCOMx->SCOM_Hardware.tx_DMAy_Channelx == DMA1_Channel2)
		{
				if(DMA_GetITStatus(DMA1_IT_TC2)==SET)
				{
						DMA_ClearFlag(DMA1_FLAG_TC2);  
						DMA_Cmd(SCOMx->SCOM_Hardware.tx_DMAy_Channelx, DISABLE);
						SCOMx->SCOM_Operating.USART_txAllowFlag = SET;
				}	
		}
	  else if(SCOMx->SCOM_Hardware.tx_DMAy_Channelx == DMA1_Channel4)
		{
				if(DMA_GetITStatus(DMA1_IT_TC4)==SET)
				{
						DMA_ClearFlag(DMA1_FLAG_TC4);   
						DMA_Cmd(SCOMx->SCOM_Hardware.tx_DMAy_Channelx, DISABLE);
						SCOMx->SCOM_Operating.USART_txAllowFlag = SET;
				}				
		}
	  else if(SCOMx->SCOM_Hardware.tx_DMAy_Channelx == DMA1_Channel7)
		{
				if(DMA_GetITStatus(DMA1_IT_TC7)==SET)
				{
						DMA_ClearFlag(DMA1_FLAG_TC7);   
						DMA_Cmd(SCOMx->SCOM_Hardware.tx_DMAy_Channelx, DISABLE);
						SCOMx->SCOM_Operating.USART_txAllowFlag = SET;
				}				
		}		
		else
		{
			return ERROR;
		}	

		return SUCCESS;
}



/********* (C) COPYRIGHT 2020 HANGZHOU NORMAL UNIVERSITY DONGWEN *****END OF FILE****/
