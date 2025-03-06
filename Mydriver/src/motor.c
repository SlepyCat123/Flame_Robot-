
#include "motor.h"
#include "SysTickDelay.h"
#define eps 0.0001

/**********************************************************************************************************/
float left_speed,right_speed;//0-99;
float Shoot;//发射轮的速度存放
/**********************************************************************************************************/
/**********************************************************************************************************/
//define

#define M_L_SPEED             	(30)	  	// 中速左电机PWM值
#define M_R_SPEED             	(30)	  	// 中速右电机PWM值

#define H_L_SPEED             (30)	  	// 高速左电机PWM值
#define H_R_SPEED             (30)	  	// 高速右电机PWM值

#define GoRight_H_L_SPEED             (40)	  	// 右转的左轮速度
#define GoRight_H_R_SPEED             (40)	    // 右转的右轮速度
#define GoLeft_H_L_SPEED              (40)	    // 左转的左轮速度
#define GoLeft_H_R_SPEED              (40)	  	// 左转的右轮速度

#define SHOOT_SPEED          (80)	  	// 摩擦轮电机
/**********************************************************************************************************/
ErrorStatus motor1_Init(void)
{
    ErrorStatus      err;
    GPIO_InitTypeDef gpioInit;
    
    err = SUCCESS;
    
    GPIO_StructInit(&gpioInit); 	
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
    
            gpioInit.GPIO_Pin = MOTOR1_IN1_GPIO_PIN;
            GPIO_Init(MOTOR1_IN1_GPIO, &gpioInit);
            gpioInit.GPIO_Pin = MOTOR1_IN2_GPIO_PIN;
            GPIO_Init(MOTOR1_IN2_GPIO, &gpioInit);
            GPIO_ResetBits(MOTOR1_IN1_GPIO, MOTOR1_IN1_GPIO_PIN);
            GPIO_ResetBits(MOTOR1_IN2_GPIO, MOTOR1_IN2_GPIO_PIN);

            PWM_Init();   
    return err;
}
ErrorStatus motor2_Init(void)
{
    ErrorStatus      err;
    GPIO_InitTypeDef gpioInit;
    
    err = SUCCESS;
    
    GPIO_StructInit(&gpioInit); 	
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
    
            gpioInit.GPIO_Pin = MOTOR2_IN1_GPIO_PIN;
            GPIO_Init(MOTOR2_IN1_GPIO, &gpioInit);
            gpioInit.GPIO_Pin = MOTOR2_IN2_GPIO_PIN;
            GPIO_Init(MOTOR2_IN2_GPIO, &gpioInit);
            GPIO_ResetBits(MOTOR2_IN1_GPIO, MOTOR2_IN1_GPIO_PIN);
            GPIO_ResetBits(MOTOR2_IN2_GPIO, MOTOR2_IN2_GPIO_PIN);

            PWM_Init();   
    return err;
}
ErrorStatus motor3_Init(void)
{
    ErrorStatus      err;
    GPIO_InitTypeDef gpioInit;
    
    err = SUCCESS;
    
    GPIO_StructInit(&gpioInit); 	
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
    
            gpioInit.GPIO_Pin = MOTOR3_IN1_GPIO_PIN;
            GPIO_Init(MOTOR3_IN1_GPIO, &gpioInit);
            gpioInit.GPIO_Pin = MOTOR3_IN2_GPIO_PIN;
            GPIO_Init(MOTOR3_IN2_GPIO, &gpioInit);
            GPIO_ResetBits(MOTOR3_IN1_GPIO, MOTOR3_IN1_GPIO_PIN);
            GPIO_ResetBits(MOTOR3_IN2_GPIO, MOTOR3_IN2_GPIO_PIN);

            PWM_Init();   
    return err;
}
ErrorStatus motor4_Init(void)
{
    ErrorStatus      err;
    GPIO_InitTypeDef gpioInit;
    
    err = SUCCESS;
    
    GPIO_StructInit(&gpioInit); 	
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
    
            gpioInit.GPIO_Pin = MOTOR4_IN1_GPIO_PIN;
            GPIO_Init(MOTOR4_IN1_GPIO, &gpioInit);
            gpioInit.GPIO_Pin = MOTOR4_IN2_GPIO_PIN;
            GPIO_Init(MOTOR4_IN2_GPIO, &gpioInit);
            GPIO_ResetBits(MOTOR4_IN1_GPIO, MOTOR4_IN1_GPIO_PIN);
            GPIO_ResetBits(MOTOR4_IN2_GPIO, MOTOR4_IN2_GPIO_PIN);
            PWM_Init();   
    return err;
}

ErrorStatus shoot_Init(void)
{
    ErrorStatus      err;
    GPIO_InitTypeDef gpioInit;
    
    err = SUCCESS;
    
    GPIO_StructInit(&gpioInit); 	
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
    
            gpioInit.GPIO_Pin = SHOOT_IN1_GPIO_PIN;
            GPIO_Init(SHOOT_IN1_GPIO, &gpioInit);
            gpioInit.GPIO_Pin = SHOOT_IN2_GPIO_PIN;
            GPIO_Init(SHOOT_IN2_GPIO, &gpioInit);
            GPIO_ResetBits(SHOOT_IN1_GPIO, SHOOT_IN1_GPIO_PIN);
            GPIO_ResetBits(SHOOT_IN2_GPIO, SHOOT_IN2_GPIO_PIN);
  
    return err;
}


ErrorStatus motor_Init(void)
{
    ErrorStatus      err;
   motor1_Init();
   motor2_Init();
   shoot_Init();    
    return err;
}

ErrorStatus motor_Control(motor_Enum motorx,int para, float speed)
{
    ErrorStatus err;
    
    err = SUCCESS;
    if(speed < -100.0f)
    {
        speed = -100.0f;
    }
    if(speed > 100.0f)
    {
        speed = 100.0f;
    }
    
    if( eps > speed  )
    {
     if(motorx==MOTOR1)
     {  
     GPIO_ResetBits(MOTOR1_IN1_GPIO, MOTOR1_IN1_GPIO_PIN);
     GPIO_ResetBits(MOTOR1_IN2_GPIO, MOTOR1_IN2_GPIO_PIN);
     }
     else if(motorx==MOTOR2)
     {
     GPIO_ResetBits(MOTOR2_IN1_GPIO, MOTOR2_IN1_GPIO_PIN);
     GPIO_ResetBits(MOTOR2_IN2_GPIO, MOTOR2_IN2_GPIO_PIN);
     }
     else if(motorx==MOTOR3)
     {
     GPIO_ResetBits(MOTOR3_IN1_GPIO, MOTOR3_IN1_GPIO_PIN);
     GPIO_ResetBits(MOTOR3_IN2_GPIO, MOTOR3_IN2_GPIO_PIN);
     }
     else if(motorx==MOTOR4)
     {
     GPIO_ResetBits(MOTOR4_IN1_GPIO, MOTOR4_IN1_GPIO_PIN);
     GPIO_ResetBits(MOTOR4_IN2_GPIO, MOTOR4_IN2_GPIO_PIN);
     }
    }
    else
    {
     if(para == 1)
     {   
         if(motorx==MOTOR1)
         {  
         GPIO_SetBits(MOTOR1_IN1_GPIO, MOTOR1_IN1_GPIO_PIN);
         GPIO_ResetBits(MOTOR1_IN2_GPIO, MOTOR1_IN2_GPIO_PIN);
         PWM_Duty_Setting(MOTOR1_PWM, speed);
         }
         else if(motorx==MOTOR2)
         {
         GPIO_SetBits(MOTOR2_IN1_GPIO, MOTOR2_IN1_GPIO_PIN);
         GPIO_ResetBits(MOTOR2_IN2_GPIO, MOTOR2_IN2_GPIO_PIN);						 			
         PWM_Duty_Setting(MOTOR2_PWM, speed);
         }
         else if(motorx==MOTOR3)
         {
         GPIO_SetBits(MOTOR3_IN1_GPIO, MOTOR3_IN1_GPIO_PIN);
         GPIO_ResetBits(MOTOR3_IN2_GPIO, MOTOR3_IN2_GPIO_PIN);
         PWM_Duty_Setting(MOTOR3_PWM, speed);
         }
         else if(motorx==MOTOR2)
         {
         GPIO_SetBits(MOTOR4_IN1_GPIO, MOTOR4_IN1_GPIO_PIN);
         GPIO_ResetBits(MOTOR4_IN2_GPIO, MOTOR4_IN2_GPIO_PIN);
         PWM_Duty_Setting(MOTOR4_PWM, speed);
          }
     }
     if(para == 2)
     {
         if(motorx==MOTOR1)
         {  
         GPIO_ResetBits(MOTOR1_IN1_GPIO, MOTOR1_IN1_GPIO_PIN);
         GPIO_SetBits(MOTOR1_IN2_GPIO, MOTOR1_IN2_GPIO_PIN);
         PWM_Duty_Setting(MOTOR1_PWM, speed);
         }
         else if(motorx==MOTOR2)
         {
         GPIO_ResetBits(MOTOR2_IN1_GPIO, MOTOR2_IN1_GPIO_PIN);
         GPIO_SetBits(MOTOR2_IN2_GPIO, MOTOR2_IN2_GPIO_PIN);
//         TIM_SetCompare2(PWM2_TIM, 72000000/8000/100.0f*50+0.5);	 
         PWM_Duty_Setting(MOTOR2_PWM, speed);
         }
         else if(motorx==MOTOR3)
         {
         GPIO_ResetBits(MOTOR3_IN1_GPIO, MOTOR3_IN1_GPIO_PIN);
         GPIO_SetBits(MOTOR3_IN2_GPIO, MOTOR3_IN2_GPIO_PIN);
         PWM_Duty_Setting(MOTOR3_PWM, speed);
         }
         else if(motorx==MOTOR2)
         {
         GPIO_ResetBits(MOTOR4_IN1_GPIO, MOTOR4_IN1_GPIO_PIN);
         GPIO_SetBits(MOTOR4_IN2_GPIO, MOTOR4_IN2_GPIO_PIN);
         PWM_Duty_Setting(MOTOR4_PWM, speed);
          }
    }
} 
    return err;
}

ErrorStatus motor_On(motor_Enum motorx)
{
    ErrorStatus err;
    
    err = SUCCESS;
    
    switch(motorx)
    {
        case MOTOR1:
            PWM_On(MOTOR1_PWM);
            break;
        case MOTOR2:
            PWM_On(MOTOR2_PWM);
            break;
        case MOTOR3:
            PWM_On(MOTOR3_PWM);
            break;
        case MOTOR4:
            PWM_On(MOTOR4_PWM);
            break;
        default:
            err = ERROR;
            break;
    }
    
    return err;
}

ErrorStatus motor_Off(motor_Enum motorx)
{
    ErrorStatus err;
    
    err = SUCCESS;
    
    switch(motorx)
    {
        case MOTOR1:
            PWM_Off(MOTOR1_PWM);
            break;
        case MOTOR2:
            PWM_Off(MOTOR2_PWM);
            break;
        case MOTOR3:
            PWM_Off(MOTOR3_PWM);
            break;
        case MOTOR4:
            PWM_Off(MOTOR4_PWM);
            break;
        default:
            err = ERROR;
            break;
    }
    
    return err;
}
void GO_Stright()
{ 	left_speed = M_L_SPEED;
    right_speed = M_R_SPEED; 
    motor_Control(MOTOR1, 1 , left_speed);
        delay_ms(50);
    motor_Control(MOTOR2, 1 , right_speed);
    delay_ms(50);
}
void GO_Brake()
{
//    motor_Off(MOTOR1);
//    motor_Off(MOTOR2);
    motor_Control(MOTOR1, 1, 0);
    motor_Control(MOTOR2, 1, 0);
    delay_ms(50);
}
void MT_BACK()
{
    left_speed = M_L_SPEED;
    right_speed = M_R_SPEED; 
    motor_Control(MOTOR1, 2,left_speed);
    motor_Control(MOTOR2, 2,right_speed);
    delay_ms(50);
}    
void GO_Left()
{
//    GO_Brake();
//    delay_ms(50);
    left_speed= GoLeft_H_L_SPEED;
    right_speed= GoLeft_H_R_SPEED;
    motor_Control(MOTOR1,1 ,left_speed);
    motor_Control(MOTOR2,2,right_speed);
    delay_ms(50);
}  
void GO_Right()
{   
//    GO_Brake();
//    delay_ms(50);
    left_speed= GoLeft_H_L_SPEED;
    right_speed= GoLeft_H_R_SPEED;
    motor_Control(MOTOR1,2, left_speed);
    motor_Control(MOTOR2,1 , right_speed);
    delay_ms(50);
}
void MT_Shoot(void)
{
  int n =10;
  GO_Brake();
  delay_ms(50);
  Shoot = SHOOT_SPEED; 
  motor_Control(MOTOR3,1, Shoot);
  while(n--)
  {
    delay_ms(1000);
  }
  delay_ms(50);
  GO_Stright();
}
