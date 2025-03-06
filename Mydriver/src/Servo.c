#include "Servo.h"
#include "SysTickDelay.h"
#include <math.h>
#include "mydef.h"
#include "stm32f10x_MapSCOMandSBUS.h" 
#include "motor.h"
int servo_pulse[6] = {75,75,75,65,75,75} , i ,Servo_Fresh;
extern SBUSData_Struct SBUSdata;
int PTZ_transverse[9] ={35,45,55,65,75,85,95,105,115};//����ͷ��̨ˮƽѰ��Ŀ��켣
//0  ����̨ˮƽ��� ��100�����ң�60
//1  ����̨��ֱ��� 125-�� 25ǰ
//2  ����ͷˮƽ��� ��125�����ң�25
//3  ����ͷ��ֱ��� �ϣ�25 �����£�125 65ˮƽ
    
//25��0.5ms��--0�㣻75��1.5ms��--90�㣻125��2.5ms��--180�����Ĳ���
int TIM4_count;
#define PWM_CNT               2000     

/**********************************************************************************************************
*�� �� ��: servo_Init(void)
*����˵��: �������ʼ��
*��    �Σ���
*�� �� ֵ: ��
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
*�� �� ��: TIM4_Int_Init(u16 arr,u16 psc)
*����˵��: TIM4��ʼ�����жϳ�ʼ�������ڿ��ƶ��
*��    �Σ�u16 arr,u16 psc
*�� �� ֵ: ��
**********************************************************************************************************/	
void TIM4_Int_Init(u16 arr,u16 psc) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //��ʱ�� TIM2 ʹ��	
	//��ʱ�� TIM2 ��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM ���ϼ���
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);  //�ڳ�ʼ�� TIM2
	TIM_ARRPreloadConfig(TIM4, DISABLE);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE );  //����������ж�
	
	//�ж����ȼ� NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM2 �ж�
	//NVIC_SetVectorTable(NVIC_VectTab_FLASH,0x0000);
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ� 0 ��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ� 2 ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //IRQ ͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ�� NVIC �Ĵ���
	TIM_Cmd(TIM4, ENABLE);  //ʹ�� TIM2
}
/**********************************************************************************************************
*�� �� ��: TIM4_IRQHandler(void) 
*����˵��: TIM4�жϣ����ƶ��PWM
*��    �Σ���
*�� �� ֵ: ��
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
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update); //���TIM2����жϱ�־	  
} 
/**********************************************************************************************************
*�� �� ��: TIM4_IRQHandler(void) 
*����˵��: ����ͷˮƽ�������PTZ_transverse������ת
*��    �Σ���
*�� �� ֵ: x
**********************************************************************************************************/	 
int Turn_PTZ_transverse(int x)    //����ͷˮƽ�������PTZ_transverse������ת������x
{
    servo_pulse[2] =PTZ_transverse[x];
    x++;
    if (x>8)  x = 0; 
    return x;
}
/**********************************************************************************************************
*�� �� ��: servo_test()
*����˵��: ���Ը������
*��    �Σ���
*�� �� ֵ: ��
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
*�� �� ��: servo_caculate()
*����˵��: �ж�openMV�ķ���ֵ,�����Ʒ�����̨λ�ã�����
*��    �Σ���
*�� �� ֵ: ��
**********************************************************************************************************/	 
void servo_caculate(void)
{
    Servo_Fresh = 0 ;
    //�ж�openMV�ķ���ֵ
    if( (SBUSdata.Channel_shuipin > 20) && (SBUSdata.Channel_chuizhi > 20) && (SBUSdata.Channel_shuipin <= 125) && (SBUSdata.Channel_chuizhi <=  125))
    {
        Servo_Fresh=1;
        GO_Brake();
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,DISABLE);
    }
    
    if (Servo_Fresh==1)
    {
        servo_pulse[0] =SBUSdata.Channel_shuipin;//ˮƽ
        delay_ms(50);
        servo_pulse[1] =SBUSdata.Channel_chuizhi;//��ֱ
        delay_ms(50);
        //����̨����
        GPIO_SetBits(SHOOT_IN1_GPIO, SHOOT_IN1_GPIO_PIN);
        GPIO_SetBits(SHOOT_IN2_GPIO, SHOOT_IN2_GPIO_PIN);
        delay_ms(150);
        delay_ms(1000);
        delay_ms(1000);
        delay_ms(1000);
        delay_ms(1000);
        delay_ms(1000);
//        GPIO_ResetBits(SHOOT_IN1_GPIO, SHOOT_IN1_GPIO_PIN);   //�������ֶ����ã����ط�����
//        GPIO_ResetBits(SHOOT_IN2_GPIO, SHOOT_IN2_GPIO_PIN);
        Servo_Fresh=0;//����
        SBUSdata.Channel_shuipin=0;
        SBUSdata.Channel_chuizhi=0;
        servo_pulse[0] =75;
        servo_pulse[1] =75;
    }
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
}
