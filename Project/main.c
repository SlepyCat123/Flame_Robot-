/**********************************************************************************************************
* �� �ƣ����ܻ��������ˣ����裩
* �� �ߣ�������
* �� ����4.7
* �� �ڣ�2025.2.2
**********************************************************************************************************/
#include "motor.h"
#include "SysTickDelay.h"
#include "HCSR04.h"
#include "calculate.h"
#include "Servo.h"
#include "HB.h"
#include "stm32f10x_scom.h"	 
/**********************************************************************************************************/

/**********************************************************************************************************
*�� �� ��: 
*����˵��: 
*��    �Σ���
*�� �� ֵ: ��
**********************************************************************************************************/
void RCC_Configuration(void);
extern void USART3_Configuration(void);
extern int  servo_pulse[8] ,i;
extern float Front,Left,Right;
extern int  TIM4_count;

/**********************************************************************************************************/
u16 rcvcnt3;
u8  Re_update3,state_machine3,rcvdat3;
u8  rebuf3[RT_LEN3];
u8  trbuf3[RT_LEN3];
//����lCD������
/**********************************************************************************************************/
int main(void)
{	
    TIM4_count=0;
    SysTick_Initaize();
	RCC_Configuration();
    GPIO_lcd();
    myprintf_u8(2,2,100);
    
    MY_SCOM_Init(SCOM3);//���ڳ�ʼ��
    
    motor_Init();
    motor_On(MOTOR1);
    motor_On(MOTOR2);
    HCSR_timer_Init();
    servo_Init();
    
    HC_SR04_Init(HCSR_CH1);
    HC_SR04_Init(HCSR_CH2);
    HC_SR04_Init(HCSR_CH3);
    HC_SR04_Init(HCSR_CH4);
    
    GO_Stright();
    TIM_Cmd(TIM5, ENABLE);	
/**********************************************************************************************************/
//    GO_Stright();//ok
//    GO_Left();//ok
//    GO_Right();//ok
//    MT_BACK();//ok
/**********************************************************************************************************/
	  while(1)
      {
//        HCSR_calculate(Front,Left,Right);//ok
        HCSR_calculate(Front,Left,Right);
        HCSR_print( Front,  Left,  Right);//ok  
          
        Front=sonar(HCSR_CH1);//ok
        Left=sonar(HCSR_CH2);//ok
        Right=sonar(HCSR_CH3);//ok 

        delay_ms(10);
//        servo_test(); //ok
        servo_caculate();

//      ����
//        Turn_PTZ_transverse(0);
//        servo_pulse[3] =65;
            
//      TIM_Cmd(TIM4, ENABLE);          
//      for(i=0;i<6;i++) {
//	    servo_pulse[i] = 100;//ѭ����8�����λ���趨��100
//		}     
//      delay_ms(50);
//      TIM_Cmd(TIM4, DISABLE);     
      }
}
/********************************************************************************
���
����
�������
������ƶ��Ѱ��Ŀ��
�ж��Ƿ�Ѱ�ҵ�Ŀ��
�ҵ�Ŀ��͹رո����˶�
�������
�������
******************************************************************************/
void RCC_Configuration(void)
{
	ErrorStatus              HSEStartUpStatus;
	
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);

    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1);

    /* PCLK1 = HCLK/16 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {}

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSYSCLKSource() != 0x08)
    {}
  }
	// next two lines should move to initial code, and add low OS at Hardware!! 
 	  RCC_LSICmd(ENABLE);
  	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY)==RESET);
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);	
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);  
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
 		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		
}

