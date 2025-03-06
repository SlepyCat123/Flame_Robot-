/******************************************************************************
  * @file    stm32f10x_scom.h
  * @author  W. Dong
  * @version V1.0.1
  * @date    23/09/2022
  * @brief   串口通信数据结构与函数声明.
  *****************************************************************************/

#ifndef __STM32F10X_SCOM_H
#define __STM32F10X_SCOM_H	

/* Includes ------------------------------------------------------------------*/	 

#include "stm32f10x.h" 	
#include <string.h>

/** @addtogroup My_Driver
  * @{
  */
	
/** @defgroup An example of using SCOM functions
  * @{
  */
	 
/**
  * @}
  */ 
	
/** @addtogroup SCOM
  * @{
  */ 

/** @defgroup SCOM_Exported_Types 
  * @{
  */ 
#define RX_BUFFER_MAX_SIZE                       7
#define TX_BUFFER_MAX_SIZE                       7	

typedef  USART_InitTypeDef             SCOM_USART_Parm;  

typedef enum __SCOM_Comm_Mode_Enum
{  
   Comm_TX,                        /*发送模式*/
   Comm_RX,                        /*接收模式*/
   Comm_RTX                        /*收发模式*/
}SCOM_Comm_Mode_Enum;



/** 
  * @brief    SCOM SCOM_READ_DATA structure definition
  */	
typedef struct __SCOM_READ_DATA_Struct
{  
   FlagStatus   Fresh;                     /*接收数据更新标志*/
   uint8_t      len;                       /*串口读入数据的有效长度*/
   uint8_t      data[RX_BUFFER_MAX_SIZE];  /*串口读入数据*/
}SCOM_READ_DATA_Struct;


/** 
  * @brief    SCOM SCOM_WRITE_DATA structure definition
  */	

typedef struct __SCOM_WRITE_DATA_Struct
{  
   uint8_t      len;                         /*串口写入数据的有效长度*/
   uint8_t      data[TX_BUFFER_MAX_SIZE];    /*串口写入数据*/
}  SCOM_WRITE_DATA_Struct;

/** 
  * @brief  SCOM Register structure definition   
  */

typedef struct __SCOMRegister_TypeDef_Struct
{
		FunctionalState                enable_SCOM;         /*串口使能标志*/
		FunctionalState                enable_DMA;          /*DMA使能标志*/				
		SCOM_Comm_Mode_Enum            commMode;			      /*通信模式*/
		SCOM_USART_Parm                USART_Parm;			    /*只存储 串口初始化结构体 的参数 */
		FlagStatus                     USART_txAllowFlag;   /*串口发送允许标志*/
} SCOMRegister_TypeDef_Struct;

/** 
  * @brief  SCOM Hardware structure definition   
  */
typedef struct __SCOMHardware_TypeDef_Struct
{	
		/*USART Hardware*/ 
		USART_TypeDef*                USARTx;
		uint8_t                       USARTx_IRQn;		
		GPIO_TypeDef *                tx_GPIOx;
		uint16_t                      tx_GPIO_Pin;			
		GPIO_TypeDef *                rx_GPIOx;
		uint16_t                      rx_GPIO_Pin;
		/* DMA  Hardware */
		DMA_Channel_TypeDef *         rx_DMAy_Channelx;
		uint8_t                       rx_DMAy_Channelx_IRQn;	
		DMA_Channel_TypeDef *         tx_DMAy_Channelx;
		uint8_t                       tx_DMAy_Channelx_IRQn;	
} SCOMHardware_TypeDef_Struct;


/** 
  * @brief  SCOM Type structure definition 
  */
typedef struct __SCOM_TypeDef_Struct
{	
	 SCOMHardware_TypeDef_Struct   SCOM_Hardware;	
	 SCOMRegister_TypeDef_Struct   SCOM_Operating;
}SCOM_TypeDef_Struct;

/** 
  * @brief  SCOM Init structure definition 
  */
typedef struct __SCOM_InitTypeDef_Struct
{
		FunctionalState             enable_SCOM;
		FunctionalState             enable_DMA;	
		SCOM_Comm_Mode_Enum         commMode;			       	
		SCOM_USART_Parm             usartInitParm;		
		uint8_t	                    SCOM_USART_PreemptionPriority;
		uint8_t	                    SCOM_USART_SubPriority;			
		uint8_t	                    SCOM_DMA_PreemptionPriority;
		uint8_t	                    SCOM_DMA_SubPriority;						
}SCOM_InitTypeDef_Struct;

/** @defgroup SCOM_Exported_Macros
  * @{
  */

extern SCOM_READ_DATA_Struct      SCOM1_rxData;
extern SCOM_READ_DATA_Struct      SCOM2_rxData;
extern SCOM_READ_DATA_Struct      SCOM3_rxData;


extern SCOM_TypeDef_Struct SCOM1_BASE;
#define SCOM1                         (&SCOM1_BASE)      /* SCOM1 selected */
#define SCOM1_USART                   USART3           

extern SCOM_TypeDef_Struct SCOM2_BASE;
#define SCOM2                        (&SCOM2_BASE)      /* SCOM2 selected */
#define SCOM2_USART                   USART2    

extern SCOM_TypeDef_Struct SCOM3_BASE;
#define SCOM3                        (&SCOM3_BASE)      /* SCOM3 selected */
#define SCOM3_USART                   USART1   

#define ENABLE_SCOM_DEFAULT                      ENABLE
#define ENABLE_DMA_DEFAULT                       ENABLE
#define SCOM_COMMMODE_DEFAULT                    Comm_RTX

#define SCOM_USART_PREEMPTIONPRIORITY_DEFAULT    (3)
#define SCOM_USART_SUBPRIORITY_DEFAULT           (3)
#define SCOM_DMA_PREEMPTIONPRIORITY_DEFAULT      (0)
#define SCOM_DMA_SUBPRIORITY_DEFAULT             (0)

#define SCOM_BAUDRATE_DEFAULT                    (115200)
#define SCOM_WORDLENGTH_DEFAULT                  USART_WordLength_8b
#define SCOM_STOPBIT_DEFAULT                     USART_StopBits_1
#define SCOM_PARITY_DEFAULT                      USART_Parity_No
#define SCOM_HARDWAREFLOWCONTROL_DEFAULT         USART_HardwareFlowControl_None

/*******************************************************************************************     
  * @brief  用默认参数填充 SCOM_InitStruct.                                                *
  * @param  SCOM_InitStruct : 需要被初始化的 SCOM_InitTypeDef_structure 类型的数据结构     *
  * @retval  None                                                                          *
*******************************************************************************************/
void SCOM_StructInit(SCOM_InitTypeDef_Struct*   SCOMx_InitStruct);

/*******************************************************************************************
  * @brief  根据初始化后的SCOM_InitStruct 初始化串口 SCOMx                                 *
  * @param  SCOMx: 指向需要初始化的串口，x 可以是1 to 3                                    *
  * @param  SCOM_InitStruct : 已经被初始化的 SCOM_InitTypeDef_Struct 类型的数据结构        *
  * @retval ERROR or SUCCESS.                                                              *
*******************************************************************************************/
ErrorStatus SCOM_Init(SCOM_TypeDef_Struct* SCOMx, SCOM_InitTypeDef_Struct* SCOMx_InitStruct);

/******************************************************************************************
  * @brief  打开串口.                                                                     *
  * @param  SCOMx: 指向需要打开的串口，x 可以是1 to 3            .                        *
  * @retval ERROR or SUCCESS.                                                             *
******************************************************************************************/
ErrorStatus SCOM_Open(SCOM_TypeDef_Struct* SCOMx);

/******************************************************************************************
  * @brief  关闭串口.                                                                     *
  * @param  SCOMx: 指向需要打开的串口，x 可以是1 to 3                                     *
  * @retval ERROR or SUCCESS.                                                             *
******************************************************************************************/
ErrorStatus SCOM_Off(SCOM_TypeDef_Struct* SCOMx);

/*****************************************************************************************
  * @brief   从串口读取数据.                                                             *
  * @param   SCOMx:  读取数据的串口，x 可以是1 to 3.                                     *
  * @param   pdata: 指向SCOM_READ_DATA_Struct类型的数据结构，用于存储取回的串口数据      *	
  *              Fresh                       接收数据更新标志                            *
  *              len                         串口读入数据的有效长度                      *
  *              data[len]                   串口读入数据                                *
  * @retval  ERROR or SUCCESS.                                                           *
*****************************************************************************************/
ErrorStatus SCOM_ReadData(SCOM_TypeDef_Struct*SCOMx, SCOM_READ_DATA_Struct* pdata);

/*****************************************************************************************
  * @brief   向指定的串口写入数据 ，串口发送允许标志SET时，允许写入数据发送              *
  * @param   SCOMx: 写入数据的串口，x 可以是1 to 3.                                      *
  * @param   pdata: 指向 SCOM_WRITE_DATA_Struct 类型的串口写入数据.                      *                                                *
  * @retval  ERROR or SUCCESS.                                                           *
*****************************************************************************************/	
	
ErrorStatus SCOM_WriteData(SCOM_TypeDef_Struct* SCOMx, SCOM_WRITE_DATA_Struct* pdata);

/****************************************************************************************
  * @brief   串口中断具体执行的服务函数(Receive interrupt and send interrupt)           *
  * @param   SCOMx:中断数据的串口，x 可以是1 to 3.                                      *
  * @retval  ERROR or SUCCESS.                                                          *
****************************************************************************************/
ErrorStatus SCOM_IRQHandler(SCOM_TypeDef_Struct* SCOMx);

/****************************************************************************************
  * @brief  串口 发送DMA中断具体执行的服务函数                                          *
  * @param  SCOMx:中断数据的串口，x 可以是1 to 3.                                       *
  * @retval ERROR or SUCCESS.                                                           *
****************************************************************************************/
ErrorStatus	SCOM_TX_DMA_IRQHandler(SCOM_TypeDef_Struct *SCOMx);	
/******************************************************************************************
  * @brief  初始化SCOM                                                                    *
                                                            *
******************************************************************************************/
ErrorStatus MY_SCOM_Init(SCOM_TypeDef_Struct* SCOMx);


#endif                /*__STM32F10X_SCOM_H */



/********* (C) COPYRIGHT 2020 HANGZHOU NORMAL UNIVERSITY   *****END OF FILE****/
