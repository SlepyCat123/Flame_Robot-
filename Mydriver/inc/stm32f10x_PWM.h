/********************************************************************************
  * @file  stm32f10x_pwm.h
  * @author  W.DONG
  * @version  V1.0.0
  * @date  25/10/2018
  * @brief  PWM ͷ�ļ�
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
#define PWM_SYS_CLOCK                          72000000                   /* ϵͳʱ�� */

		
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
 + ʵ�ֹ��ܣ�PWMx��ʼ��
 + ��    ��: PWM_CHNx �� ��������PWM_CHN_enum��ѡ����Ҫ��ʼ����PWMͨ��
 +           ʵ��ȡֵPWM_CHN1, PWM_CHN2, PWM_CHN3, PWM_CHN4���ֱ����PWM 4��ͨ��
 + ���ز���:��
-----------------------------------------------------------------------------------------------*/
void PWM1_Init(void);
void PWM2_Init(void);
void PWM3_Init(void);
void PWM4_Init(void);

void PWM_Init(void);
/*-----------------------------------------------------------------------------------------------
 + ʵ�ֹ��ܣ�����PWMxռ�ձ�
 + ��    ��: PWM_CHNx �� ��������PWM_CHN_enum��ѡ����Ҫ��ʼ����PWMͨ��
 +           ʵ��ȡֵPWM_CHN1, PWM_CHN2, PWM_CHN3, PWM_CHN4���ֱ����PWM 4��ͨ��
 +           PWM_Duty����������float��ȡֵ��Χ0-100
 + ���ز���:��
-----------------------------------------------------------------------------------------------*/
void PWM_Duty_Setting(PWM_CHN_enum PWM_CHNx, float PWM_Duty);

/*-----------------------------------------------------------------------------------------------
 + ʵ�ֹ��ܣ���PWMx
 + ��    ��: PWM_CHNx �� ��������PWM_CHN_enum��ѡ����Ҫ��ʼ����PWMͨ��
 +           ʵ��ȡֵPWM_CHN1, PWM_CHN2, PWM_CHN3, PWM_CHN4���ֱ����PWM 4��ͨ��
 + ���ز���:��
-----------------------------------------------------------------------------------------------*/
void PWM_On(PWM_CHN_enum PWM_CHNx);

/*-----------------------------------------------------------------------------------------------
 + ʵ�ֹ��ܣ��ر�PWMx
 + ��    ��: PWM_CHNx �� ��������PWM_CHN_enum��ѡ����Ҫ��ʼ����PWMͨ��
 +           ʵ��ȡֵPWM_CHN1, PWM_CHN2, PWM_CHN3, PWM_CHN4���ֱ����PWM 4��ͨ��
 + ���ز���:��
-----------------------------------------------------------------------------------------------*/
void PWM_Off(PWM_CHN_enum PWM_CHNx);



#endif /*__STM32F10X_PWM_H */

