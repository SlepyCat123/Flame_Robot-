/********************************************************************************
  * @file    stm32f10x_scom_it.c
  * @author  W. Dong
  * @version V1.0.0
  * @date    15/April/2014
  * @brief   This file provides all the SCOM channel init functions.
  *******************************************************************************/
	
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_scom.h"

void USART1_IRQHandler(void) 
{
	if(SCOM1->SCOM_Hardware.USARTx_IRQn == 37)
	{
	     SCOM_IRQHandler(SCOM1);
	}
	if(SCOM2->SCOM_Hardware.USARTx_IRQn == 37)
	{
	     SCOM_IRQHandler(SCOM2);
	}
	if(SCOM3->SCOM_Hardware.USARTx_IRQn == 37)
	{
	     SCOM_IRQHandler(SCOM3);
	}	
}

/**
  * @brief  USART2 interrupt service routine
  * @param  None.
  * @retval None.
  */
void USART2_IRQHandler(void) 
{
	if(SCOM1->SCOM_Hardware.USARTx_IRQn == 38)
	{
	     SCOM_IRQHandler(SCOM1);
	}
	if(SCOM2->SCOM_Hardware.USARTx_IRQn == 38)
	{
	     SCOM_IRQHandler(SCOM2);
	}
	if(SCOM3->SCOM_Hardware.USARTx_IRQn == 38)
	{
	     SCOM_IRQHandler(SCOM3);
	}
}

/**
  * @brief  USART3 interrupt service routine
  * @param  None.
  * @retval None.
  */
void USART3_IRQHandler(void) 
{
	if(SCOM1->SCOM_Hardware.USARTx_IRQn == 39)
	{
	     SCOM_IRQHandler(SCOM1);
	}
	if(SCOM2->SCOM_Hardware.USARTx_IRQn == 39)
	{
	     SCOM_IRQHandler(SCOM2);
	}
	if(SCOM3->SCOM_Hardware.USARTx_IRQn == 39)
	{
	     SCOM_IRQHandler(SCOM3);
	}
}
/**
  * @brief  DMA1_Channel2 interrupt SendData service routine
  * @param  None.
  * @retval None.
  */
void DMA1_Channel2_IRQHandler(void)
{
    if(SCOM1->SCOM_Hardware.tx_DMAy_Channelx_IRQn == 12)
		{			
	      SCOM_TX_DMA_IRQHandler(SCOM1);
		}
    if(SCOM2->SCOM_Hardware.tx_DMAy_Channelx_IRQn == 12)
		{			
	      SCOM_TX_DMA_IRQHandler(SCOM2);
		}
    if(SCOM3->SCOM_Hardware.tx_DMAy_Channelx_IRQn == 12)
		{			
	      SCOM_TX_DMA_IRQHandler(SCOM3);
		}	
}
/**
  * @brief  DMA1_Channel4 interrupt SendData  service routine
  * @param  None.
  * @retval None.
  */
void DMA1_Channel4_IRQHandler(void)
{
    if(SCOM1->SCOM_Hardware.tx_DMAy_Channelx_IRQn == 14)
		{			
	      SCOM_TX_DMA_IRQHandler(SCOM1);
		}
    if(SCOM2->SCOM_Hardware.tx_DMAy_Channelx_IRQn == 14)
		{			
	      SCOM_TX_DMA_IRQHandler(SCOM2);
		}
    if(SCOM3->SCOM_Hardware.tx_DMAy_Channelx_IRQn == 14)
		{			
	      SCOM_TX_DMA_IRQHandler(SCOM3);
		}	
}
/**
  * @brief  DMA1_Channel7 interrupt SendData service routine
  * @param  None.
  * @retval None.
  */
void DMA1_Channel7_IRQHandler(void)
{
    if(SCOM1->SCOM_Hardware.tx_DMAy_Channelx_IRQn == 17)
		{			
	      SCOM_TX_DMA_IRQHandler(SCOM1);
		}
    if(SCOM2->SCOM_Hardware.tx_DMAy_Channelx_IRQn == 17)
		{			
	      SCOM_TX_DMA_IRQHandler(SCOM2);
		}
    if(SCOM3->SCOM_Hardware.tx_DMAy_Channelx_IRQn == 17)
		{			
	      SCOM_TX_DMA_IRQHandler(SCOM3);
		}	
}
/**
  * @}
  */

/********* (C) COPYRIGHT 2020 HANGZHOU NORMAL UNIVERSITY   *****END OF FILE****/
