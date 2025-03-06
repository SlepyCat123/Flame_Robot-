
#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <string.h>

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#include "stm32f10x_PWM.h"

typedef enum __motor_Enum
{
    MOTOR1,
    MOTOR2,
    MOTOR3,
    MOTOR4
}motor_Enum;

/* ----------------------------- PWM_Hardware_define ------------------------------- */		
		
#define MOTOR1_PWM          PWM1  //
#define MOTOR2_PWM          PWM2  //���ֵ��
#define MOTOR3_PWM          PWM3  //������
#define MOTOR4_PWM          PWM4  //��̨ˮƽ���
#define MOTOR5_PWM          PWM5  //��̨��ֱ���
#define MOTOR6_PWM          PWM6 
#define MOTOR7_PWM          PWM7 

#define MOTOR1_IN1_GPIO     GPIOC
#define MOTOR1_IN1_GPIO_PIN GPIO_Pin_2

#define MOTOR1_IN2_GPIO     GPIOC
#define MOTOR1_IN2_GPIO_PIN GPIO_Pin_3  

#define MOTOR2_IN1_GPIO     GPIOC
#define MOTOR2_IN1_GPIO_PIN GPIO_Pin_1 

#define MOTOR2_IN2_GPIO     GPIOC
#define MOTOR2_IN2_GPIO_PIN GPIO_Pin_0    
//#define MOTOR1_IN1_GPIO     GPIOF
//#define MOTOR1_IN1_GPIO_PIN GPIO_Pin_7

//#define MOTOR1_IN2_GPIO     GPIOF
//#define MOTOR1_IN2_GPIO_PIN GPIO_Pin_8

//#define MOTOR2_IN1_GPIO     GPIOF
//#define MOTOR2_IN1_GPIO_PIN GPIO_Pin_9

//#define MOTOR2_IN2_GPIO     GPIOF
//#define MOTOR2_IN2_GPIO_PIN GPIO_Pin_10  		
//		
#define MOTOR3_IN1_GPIO     GPIOC
#define MOTOR3_IN1_GPIO_PIN GPIO_Pin_2

#define MOTOR3_IN2_GPIO     GPIOC
#define MOTOR3_IN2_GPIO_PIN GPIO_Pin_3  

#define MOTOR4_IN1_GPIO     GPIOC
#define MOTOR4_IN1_GPIO_PIN GPIO_Pin_1 

#define MOTOR4_IN2_GPIO     GPIOC   
#define MOTOR4_IN2_GPIO_PIN GPIO_Pin_0 

#define SHOOT_IN1_GPIO     GPIOE   
#define SHOOT_IN1_GPIO_PIN GPIO_Pin_9 
#define SHOOT_IN2_GPIO     GPIOE   
#define SHOOT_IN2_GPIO_PIN GPIO_Pin_10

ErrorStatus motor1_Init(void);
ErrorStatus motor2_Init(void);
ErrorStatus motor3_Init(void);
ErrorStatus motor4_Init(void);
ErrorStatus shoot_Init(void);
    
ErrorStatus motor_Init(void);//��ʼ����Ҫ�ĵ��

ErrorStatus motor_Control(motor_Enum motorx,int para,float speed);//���Ƶ���˶���para 1:ǰ����-1������

ErrorStatus motor_On(motor_Enum motorx);

ErrorStatus motor_Off(motor_Enum motorx);

void GO_Stright(void);
void GO_Brake(void);
void MT_FORWARD(void);
void MT_BACK(void);
void GO_Left(void);
void GO_Right(void);
void MT_Shoot(void);


#endif
