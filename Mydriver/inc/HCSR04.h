#ifndef __HCSR04_H
#define __HCSR04_H
#include <stm32f10x.h>
#include "stm32f10x_gpio.h"

typedef enum __HCSR04_enum
{ 
HCSR_CH1,
HCSR_CH2,    
HCSR_CH3,
HCSR_CH4
}HCSR04_enum;

//#define 	HCSR_CH1_TIM              	   TIM2
//#define 	HCSR_CH1_TIM_CHANNEL           TIM_Channel_1
#define 	HCSR_CH1_Echo_GPIO             GPIOA
#define 	HCSR_CH1_Echo_GPIO_PIN         GPIO_Pin_0
#define 	HCSR_CH1_Trig_GPIO             GPIOF
#define 	HCSR_CH1_Trig_GPIO_PIN         GPIO_Pin_1

//#define 	HCSR_CH2_TIM              	   TIM2
//#define 	HCSR_CH2_TIM_CHANNEL           TIM_Channel_2
#define 	HCSR_CH2_Echo_GPIO             GPIOA
#define 	HCSR_CH2_Echo_GPIO_PIN         GPIO_Pin_1
#define 	HCSR_CH2_Trig_GPIO             GPIOF
#define 	HCSR_CH2_Trig_GPIO_PIN         GPIO_Pin_2

//#define 	HCSR_CH3_TIM              	   TIM4
//#define 	HCSR_CH3_TIM_CHANNEL           TIM_Channel_3
#define 	HCSR_CH3_Echo_GPIO             GPIOA
#define 	HCSR_CH3_Echo_GPIO_PIN         GPIO_Pin_2
#define 	HCSR_CH3_Trig_GPIO             GPIOF
#define 	HCSR_CH3_Trig_GPIO_PIN         GPIO_Pin_3

//#define 	HCSR_CH4_TIM              	   TIM4
//#define 	HCSR_CH4_TIM_CHANNEL           TIM_Channel_4
#define 	HCSR_CH4_Echo_GPIO             GPIOA
#define 	HCSR_CH4_Echo_GPIO_PIN         GPIO_Pin_3
#define 	HCSR_CH4_Trig_GPIO             GPIOF
#define 	HCSR_CH4_Trig_GPIO_PIN         GPIO_Pin_4

void HCSR_timer_Init(void);

void HC_SR04_Init(HCSR04_enum HCSRx);

uint16_t  sonar_mm(HCSR04_enum HCSRx);

float sonar(HCSR04_enum HCSRx);

void HCSR_print(float Front, float Left, float Right);//在lcd中打印出距离
#endif
