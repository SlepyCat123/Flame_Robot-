/*  ******************************************************************************
  * @file    stm32f10x_MapSCOMandSBUS.h
  * @author  W. DONG
  * @version V1.0.0
  * @date    25/01/2020
  * @brief   串口25byte的8bit数据与SBUS 16byte的11bit 数据转换 数据结构与函数声明.
  ********************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __STM32F10X_MAPSCOMANDSBUS_H
#define __STM32F10X_MAPSCOMANDSBUS_H	

/* Includes ------------------------------------------------------------------*/	 
#include <stm32f10x.h>

/** @addtogroup My_Driver
  * @{
  */
	

/**
  * @}
  */ 
/* SBUS数据帧组成*/

typedef struct _SBUSData_Struct              
{  
    uint8_t                  ChannelData[3];
    uint16_t                 Channel_shuipin;
    uint16_t                 Channel_chuizhi;
    uint8_t           	      FlagByte;
} SBUSData_Struct;


/**
  * @}
  */
	
/** @defgroup MapSCOMandSBUS_Exported_Functions Prototypes
  * @{
  */


/*****************************************************************
  * @brief   将 SCOM数据匹配为SBUS数据                            *
  * @param   SCOMdata： 串口数据指针，要求数组长度25byte         *
 	*         SCOMdata[0]                  首字节： 0x0F           *
  *         SCOMdata[24]                 尾字节： 0x00           *
  *         SCOMdata[23]                 标志字节： 默认0x00     *
  *         SCOMdata[1]-SCOMdata[22]     用户数据                *	
  * @param   SBUSdata： SBUS数据存储指针，类型 SBUSData_Struct   *	
  * @retval  ERROR or SUCCESS.                                                *
*****************************************************************/
ErrorStatus Map_SCOMtoSBUS(SBUSData_Struct *SBUSdata,uint8_t *SCOMdata);


/*****************************************************************
  * @brief   将SBUS数据匹配为 SCOM数据                           *
  * @param   SBUSdata： SBUS数据存储指针，类型 SBUSData_Struct   *	
  *            16byte  11bit数据 	                               *
  * @param   SCOMdata： 串口数据指针，要求数组长度25byte         *
 	*         SCOMdata[0]                  首字节： 0x0F           *
  *         SCOMdata[24]                 尾字节： 0x00           *
  *         SCOMdata[23]                 标志字节： 默认0x00     *
  *         SCOMdata[1]-SCOMdata[22]     用户数据                *	
  * @retval  ERROR or SUCCESS.                                   *
*****************************************************************/
ErrorStatus Map_SBUStoSCOM(uint8_t *SCOMdata,SBUSData_Struct *SBUSdata);


/**
  * @}
  */

#endif     /*__STM32F10X_MapSCOMandSBUS_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/********* (C) COPYRIGHT 2020 HANGZHOU NORMAL UNIVERSITY   *****END OF FILE****/
