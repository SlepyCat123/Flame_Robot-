#ifndef SERVO___H
#define SERVO___H

#include <stm32f10x.h>
#include "stm32f10x_gpio.h"
//¶æ»úÂö³åÊý×é
#define serve_GPIO    GPIOE;

#define servo_1_PIN   GPIO_Pin_0;
#define servo_2_PIN   GPIO_Pin_1;
#define servo_3_PIN   GPIO_Pin_2;
#define servo_4_PIN   GPIO_Pin_3;
#define servo_5_PIN   GPIO_Pin_4;
#define servo_6_PIN   GPIO_Pin_5;
//#define servo_7_PIN   GPIO_Pin_6;
//#define servo_8_PIN   GPIO_Pin_7;

void servo_Init(void);
void gpioE_pin_set(unsigned char pin, unsigned char level);
void TIM4_Int_Init(uint16_t arr,uint16_t psc) ;
void servo_test(void);   
int  Turn_PTZ_transverse(int x) ; 
void servo_caculate(void);
//void Turn_PTZ_transverse(float x);
//void Turn_PTZ_direction(float x)
//void Steering_init(void);

#endif



