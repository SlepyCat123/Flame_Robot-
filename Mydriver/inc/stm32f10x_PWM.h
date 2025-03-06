/********************************************************************************
  * @file  stm32f10x_pwm.h
  * @author  W.DONG
  * @version  V1.0.0
  * @date  25/10/2018
  * @brief  PWM 头文件
  ******************************************************************************/


#ifndef __STM32F10X_PWM_H
#define __STM32F10X_PWM_H

#include <string.h>
#include <stm32f10x.h>

typedef enum __PWM_CHN_enum
{ 
  PWM1,
  PWM2,
  PWM3,
  PWM4	
}PWM_CHN_enum;


/* ------------------------------ System_Clock_define ------------------------------- */
#define PWM_SYS_CLOCK                          72000000                   /* 系统时钟 */

		
/* ----------------------------- PWM_Hardware_define ------------------------------- */		
		
#define 	PWM1_TIM              	   TIM3
#define 	PWM1_TIM_CHANNEL           TIM_Channel_1
#define 	PWM1_GPIO                  GPIOA
#define 	PWM1_GPIO_PIN              GPIO_Pin_6

#define 	PWM2_TIM              	   TIM3
#define 	PWM2_TIM_CHANNEL           TIM_Channel_2
#define 	PWM2_GPIO                  GPIOA
#define 	PWM2_GPIO_PIN              GPIO_Pin_7
		
#define 	PWM3_TIM              	   TIM3
#define 	PWM3_TIM_CHANNEL           TIM_Channel_3
#define 	PWM3_GPIO                  GPIOB
#define 	PWM3_GPIO_PIN              GPIO_Pin_0

#define 	PWM4_TIM              	   TIM3
#define 	PWM4_TIM_CHANNEL           TIM_Channel_4
#define 	PWM4_GPIO                  GPIOB
#define 	PWM4_GPIO_PIN              GPIO_Pin_1		
		
		
/* ----------------------------- PWM_Parameter_define ------------------------------- */

#define PWM_POLARITY_DEFAULT                   TIM_OCPolarity_High
#define PWM_OCMODE_DEFAULT                     TIM_OCMode_PWM1

#define PWM_DUTY_DEFAULT                       1
#define PWM_FREQ_DEFAULT                       8000                      /* unit: Hz */



/*-----------------------------------------------------------------------------------------------
 + 实现功能：PWMx初始化
 + 形    参: PWM_CHNx ： 数据类型PWM_CHN_enum，选择需要初始化的PWM通道
 +           实参取值PWM_CHN1, PWM_CHN2, PWM_CHN3, PWM_CHN4，分别代表PWM 4个通道
 + 返回参数:无
-----------------------------------------------------------------------------------------------*/
void PWM1_Init(void);
void PWM2_Init(void);
void PWM3_Init(void);
void PWM4_Init(void);

void PWM_Init(void);
/*-----------------------------------------------------------------------------------------------
 + 实现功能：调整PWMx占空比
 + 形    参: PWM_CHNx ： 数据类型PWM_CHN_enum，选择需要初始化的PWM通道
 +           实参取值PWM_CHN1, PWM_CHN2, PWM_CHN3, PWM_CHN4，分别代表PWM 4个通道
 +           PWM_Duty：数据类型float，取值范围0-100
 + 返回参数:无
-----------------------------------------------------------------------------------------------*/
void PWM_Duty_Setting(PWM_CHN_enum PWM_CHNx, float PWM_Duty);

/*-----------------------------------------------------------------------------------------------
 + 实现功能：打开PWMx
 + 形    参: PWM_CHNx ： 数据类型PWM_CHN_enum，选择需要初始化的PWM通道
 +           实参取值PWM_CHN1, PWM_CHN2, PWM_CHN3, PWM_CHN4，分别代表PWM 4个通道
 + 返回参数:无
-----------------------------------------------------------------------------------------------*/
void PWM_On(PWM_CHN_enum PWM_CHNx);

/*-----------------------------------------------------------------------------------------------
 + 实现功能：关闭PWMx
 + 形    参: PWM_CHNx ： 数据类型PWM_CHN_enum，选择需要初始化的PWM通道
 +           实参取值PWM_CHN1, PWM_CHN2, PWM_CHN3, PWM_CHN4，分别代表PWM 4个通道
 + 返回参数:无
-----------------------------------------------------------------------------------------------*/
void PWM_Off(PWM_CHN_enum PWM_CHNx);



#endif /*__STM32F10X_PWM_H */

