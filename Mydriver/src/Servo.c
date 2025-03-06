#include "Servo.h"
#include "SysTickDelay.h"
#include <math.h>
#include "mydef.h"
#include "stm32f10x_MapSCOMandSBUS.h" 
#include "motor.h"
int servo_pulse[6] = {75,75,75,65,75,75} , i ,Servo_Fresh;
extern SBUSData_Struct SBUSdata;
int PTZ_transverse[9] ={35,45,55,65,75,85,95,105,115};//摄像头云台水平寻找目标轨迹
//0  发射台水平舵机 左：100——右：60
//1  发射台垂直舵机 125-后 25前
//2  摄像头水平舵机 左：125——右：25
//3  摄像头垂直电机 上：25 ——下：125 65水平
    
//25（0.5ms）--0°；75（1.5ms）--90°；125（2.5ms）--180°舵机的参数
int TIM4_count;
#define PWM_CNT               2000     

/**********************************************************************************************************
*函 数 名: servo_Init(void)
*功能说明: 各舵机初始化
*形    参：无
*返 回 值: 无
**********************************************************************************************************/		
void servo_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM4_Int_Init(20,71);//20us
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  servo_1_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = servo_2_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = servo_3_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = servo_4_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = servo_5_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = servo_6_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

//void servo_set(u8 index, u8 level) {
//	switch(index) {
//		case 0:gpioE_pin_set(0, level);break;
//		case 1:gpioE_pin_set(1, level);break;
//		case 2:gpioE_pin_set(2, level);break;
//		case 3:gpioE_pin_set(3, level);break;
//		case 4:gpioE_pin_set(4, level);break;
//		case 5:gpioE_pin_set(5, level);break;
//		case 6:gpioE_pin_set(6, level);break;
//		case 7:gpioE_pin_set(7, level);break;
//		default:break;
//	}
//}
void gpioE_pin_set(unsigned char pin, unsigned char level) {
	if(level) {
		GPIO_SetBits(GPIOE,1 << pin);
	} else {
		GPIO_ResetBits(GPIOE,1 << pin);
	}
}
/**********************************************************************************************************
*函 数 名: TIM4_Int_Init(u16 arr,u16 psc)
*功能说明: TIM4初始化，中断初始化，用于控制舵机
*形    参：u16 arr,u16 psc
*返 回 值: 无
**********************************************************************************************************/	
void TIM4_Int_Init(u16 arr,u16 psc) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //①时钟 TIM2 使能	
	//定时器 TIM2 初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM 向上计数
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);  //②初始化 TIM2
	TIM_ARRPreloadConfig(TIM4, DISABLE);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE );  //③允许更新中断
	
	//中断优先级 NVIC 设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM2 中断
	//NVIC_SetVectorTable(NVIC_VectTab_FLASH,0x0000);
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //先占优先级 0 级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级 2 级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //IRQ 通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化 NVIC 寄存器
	TIM_Cmd(TIM4, ENABLE);  //使能 TIM2
}
/**********************************************************************************************************
*函 数 名: TIM4_IRQHandler(void) 
*功能说明: TIM4中断，控制舵机PWM
*形    参：无
*返 回 值: 无
**********************************************************************************************************/	
void TIM4_IRQHandler(void) 
{
    TIM4_count++;
	if(TIM4_count==PWM_CNT) TIM4_count=0;
    if(TIM4_count<servo_pulse[0]){PEout( 0)=1;} else{PEout( 0)=0;} 
    if(TIM4_count<servo_pulse[1]){PEout( 1)=1;} else{PEout( 1)=0;}  
    if(TIM4_count<servo_pulse[2]){PEout( 2)=1;} else{PEout( 2)=0;}  
    if(TIM4_count<servo_pulse[3]){PEout( 3)=1;} else{PEout( 3)=0;}  
    if(TIM4_count<servo_pulse[4]){PEout( 4)=1;} else{PEout( 4)=0;}  
    if(TIM4_count<servo_pulse[5]){PEout( 5)=1;} else{PEout( 5)=0;}  
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update); //清除TIM2溢出中断标志	  
} 
/**********************************************************************************************************
*函 数 名: TIM4_IRQHandler(void) 
*功能说明: 摄像头水平舵机按照PTZ_transverse数组旋转
*形    参：无
*返 回 值: x
**********************************************************************************************************/	 
int Turn_PTZ_transverse(int x)    //摄像头水平舵机按照PTZ_transverse数组旋转，返回x
{
    servo_pulse[2] =PTZ_transverse[x];
    x++;
    if (x>8)  x = 0; 
    return x;
}
/**********************************************************************************************************
*函 数 名: servo_test()
*功能说明: 测试各个舵机
*形    参：无
*返 回 值: 无
**********************************************************************************************************/	 
void servo_test(void)    
{
    if (servo_pulse[0]>20 && servo_pulse[1]>20 && servo_pulse[2]>20 && servo_pulse[3]>20)
    {
        servo_pulse[0]-= 1;
        servo_pulse[1]-= 1;
        servo_pulse[2]-= 1;
        servo_pulse[3]-= 1;
        delay_ms(10);
    }
    else  
    {
        servo_pulse[0] = 70;
        servo_pulse[1] = 70;
        servo_pulse[2] = 70;
        servo_pulse[3] = 70;
        delay_ms(10); 
    }
}
/**********************************************************************************************************
*函 数 名: servo_caculate()
*功能说明: 判断openMV的返回值,并控制发射云台位置，后发射
*形    参：无
*返 回 值: 无
**********************************************************************************************************/	 
void servo_caculate(void)
{
    Servo_Fresh = 0 ;
    //判断openMV的返回值
    if( (SBUSdata.Channel_shuipin > 20) && (SBUSdata.Channel_chuizhi > 20) && (SBUSdata.Channel_shuipin <= 125) && (SBUSdata.Channel_chuizhi <=  125))
    {
        Servo_Fresh=1;
        GO_Brake();
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,DISABLE);
    }
    
    if (Servo_Fresh==1)
    {
        servo_pulse[0] =SBUSdata.Channel_shuipin;//水平
        delay_ms(50);
        servo_pulse[1] =SBUSdata.Channel_chuizhi;//垂直
        delay_ms(50);
        //发射台启动
        GPIO_SetBits(SHOOT_IN1_GPIO, SHOOT_IN1_GPIO_PIN);
        GPIO_SetBits(SHOOT_IN2_GPIO, SHOOT_IN2_GPIO_PIN);
        delay_ms(150);
        delay_ms(1000);
        delay_ms(1000);
        delay_ms(1000);
        delay_ms(1000);
        delay_ms(1000);
//        GPIO_ResetBits(SHOOT_IN1_GPIO, SHOOT_IN1_GPIO_PIN);   //测试需手动放置，不关发射电机
//        GPIO_ResetBits(SHOOT_IN2_GPIO, SHOOT_IN2_GPIO_PIN);
        Servo_Fresh=0;//回正
        SBUSdata.Channel_shuipin=0;
        SBUSdata.Channel_chuizhi=0;
        servo_pulse[0] =75;
        servo_pulse[1] =75;
    }
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
}
