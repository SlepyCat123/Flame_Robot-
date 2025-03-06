
#include "stm32f10x_PWM.h"
#include <math.h>

#define PWM_MAXDUTY                   (100.0f)
#define PWM_MINDUTY                   (0.0f)

uint16_t                     Arr;



 void PWM1_Init()
{
    GPIO_InitTypeDef             GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef      TIM_TimeBaseStructure;
	TIM_OCInitTypeDef            TIM_OCInitStructure;
	uint16_t                     Psc;
	uint16_t                     Pulse;	

	Psc   = ceil(72000000/PWM_FREQ_DEFAULT/65535.0f);
	Arr   = (uint16_t)(72000000/PWM_FREQ_DEFAULT/Psc);//72000000/8000
    Pulse = PWM_DUTY_DEFAULT;

	GPIO_StructInit(&GPIO_InitStructure); 	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
		
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period            = Arr - 1;
	TIM_TimeBaseStructure.TIM_Prescaler         = Psc - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision     = 0;
	TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up;
		
	TIM_OCStructInit(&TIM_OCInitStructure);	
	TIM_OCInitStructure.TIM_OCMode              = PWM_OCMODE_DEFAULT;
	TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse               = Pulse;
	TIM_OCInitStructure.TIM_OCPolarity          = PWM_POLARITY_DEFAULT;		

            GPIO_InitStructure.GPIO_Pin = PWM1_GPIO_PIN;
            GPIO_Init(PWM1_GPIO,&GPIO_InitStructure);						 
			 
			TIM_TimeBaseInit(PWM1_TIM,&TIM_TimeBaseStructure);
			TIM_ARRPreloadConfig(PWM1_TIM, ENABLE);
            TIM_OC1Init(PWM1_TIM, &TIM_OCInitStructure);	 
	        //1
 }
  void PWM2_Init()
{
    GPIO_InitTypeDef             GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef      TIM_TimeBaseStructure;
	TIM_OCInitTypeDef            TIM_OCInitStructure;
	uint16_t                     Psc;
	uint16_t                     Pulse;	

	Psc   = ceil(72000000/PWM_FREQ_DEFAULT/65535.0f);
	Arr   = (uint16_t)(72000000/PWM_FREQ_DEFAULT/Psc);
    Pulse = PWM_DUTY_DEFAULT;

	GPIO_StructInit(&GPIO_InitStructure); 	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
		
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period            = Arr - 1;
	TIM_TimeBaseStructure.TIM_Prescaler         = Psc - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision     = 0;
	TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up;
		
	TIM_OCStructInit(&TIM_OCInitStructure);	
	TIM_OCInitStructure.TIM_OCMode              = PWM_OCMODE_DEFAULT;
	TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse               = Pulse;
	TIM_OCInitStructure.TIM_OCPolarity          = PWM_POLARITY_DEFAULT;		

    GPIO_InitStructure.GPIO_Pin = PWM2_GPIO_PIN;						
    GPIO_Init(PWM2_GPIO,&GPIO_InitStructure);						 
     
    TIM_TimeBaseInit(PWM2_TIM,&TIM_TimeBaseStructure);
    TIM_ARRPreloadConfig(PWM2_TIM, ENABLE);
    TIM_OC2Init(PWM2_TIM, &TIM_OCInitStructure); 
    //2
 }

  void PWM3_Init()
{
    GPIO_InitTypeDef             GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef      TIM_TimeBaseStructure;
	TIM_OCInitTypeDef            TIM_OCInitStructure;
	uint16_t                     Psc;
	uint16_t                     Pulse;	

	Psc   = ceil(72000000/PWM_FREQ_DEFAULT/65535.0f);
	Arr   = (uint16_t)(72000000/PWM_FREQ_DEFAULT/Psc);
    Pulse = PWM_DUTY_DEFAULT;

	GPIO_StructInit(&GPIO_InitStructure); 	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
		
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period            = Arr - 1;
	TIM_TimeBaseStructure.TIM_Prescaler         = Psc - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision     = 0;
	TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up;
		
	TIM_OCStructInit(&TIM_OCInitStructure);	
	TIM_OCInitStructure.TIM_OCMode              = PWM_OCMODE_DEFAULT;
	TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse               = Pulse;
	TIM_OCInitStructure.TIM_OCPolarity          = PWM_POLARITY_DEFAULT;		

    GPIO_InitStructure.GPIO_Pin = PWM3_GPIO_PIN;						
    GPIO_Init(PWM3_GPIO,&GPIO_InitStructure);						 
     
    TIM_TimeBaseInit(PWM3_TIM,&TIM_TimeBaseStructure);
    TIM_ARRPreloadConfig(PWM3_TIM, ENABLE);
    TIM_OC3Init(PWM3_TIM, &TIM_OCInitStructure);
 }
 
   void PWM4_Init()
{
    GPIO_InitTypeDef             GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef      TIM_TimeBaseStructure;
	TIM_OCInitTypeDef            TIM_OCInitStructure;
	uint16_t                     Psc;
	uint16_t                     Pulse;	

	Psc   = ceil(72000000/PWM_FREQ_DEFAULT/65535.0f);
	Arr   = (uint16_t)(72000000/PWM_FREQ_DEFAULT/Psc);
    Pulse = PWM_DUTY_DEFAULT;

	GPIO_StructInit(&GPIO_InitStructure); 	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
		
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period            = Arr - 1;
	TIM_TimeBaseStructure.TIM_Prescaler         = Psc - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision     = 0;
	TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up;
		
	TIM_OCStructInit(&TIM_OCInitStructure);	
	TIM_OCInitStructure.TIM_OCMode              = PWM_OCMODE_DEFAULT;
	TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse               = Pulse;
	TIM_OCInitStructure.TIM_OCPolarity          = PWM_POLARITY_DEFAULT;		

    GPIO_InitStructure.GPIO_Pin = PWM4_GPIO_PIN;						
    GPIO_Init(PWM4_GPIO,&GPIO_InitStructure);						 
     
    TIM_TimeBaseInit(PWM4_TIM,&TIM_TimeBaseStructure);
    TIM_ARRPreloadConfig(PWM4_TIM, ENABLE);	
    TIM_OC4Init(PWM4_TIM, &TIM_OCInitStructure);	 
    //4
 }

void PWM_Init()
{
 PWM1_Init();
 PWM2_Init();
 PWM3_Init();
 PWM4_Init();
    
 }
//  void PWM_Init()
//{
//    GPIO_InitTypeDef             GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef      TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef            TIM_OCInitStructure;
//	uint16_t                     Psc;
//	uint16_t                     Pulse;	

//	Psc   = ceil(72000000/PWM_FREQ_DEFAULT/65535.0f);
//	Arr   = (uint16_t)(72000000/PWM_FREQ_DEFAULT/Psc);
//    Pulse = PWM_DUTY_DEFAULT;

//	GPIO_StructInit(&GPIO_InitStructure); 	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
//		
//	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//	TIM_TimeBaseStructure.TIM_Period            = Arr - 1;
//	TIM_TimeBaseStructure.TIM_Prescaler         = Psc - 1;
//	TIM_TimeBaseStructure.TIM_ClockDivision     = 0;
//	TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up;
//		
//	TIM_OCStructInit(&TIM_OCInitStructure);	
//	TIM_OCInitStructure.TIM_OCMode              = PWM_OCMODE_DEFAULT;
//	TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_Pulse               = Pulse;
//	TIM_OCInitStructure.TIM_OCPolarity          = PWM_POLARITY_DEFAULT;		

//            GPIO_InitStructure.GPIO_Pin = PWM1_GPIO_PIN;
//            GPIO_Init(PWM1_GPIO,&GPIO_InitStructure);						 
//			 
//			TIM_TimeBaseInit(PWM1_TIM,&TIM_TimeBaseStructure);
//			TIM_ARRPreloadConfig(PWM1_TIM, ENABLE);
//            TIM_OC1Init(PWM1_TIM, &TIM_OCInitStructure);	 
//	        //1
//            GPIO_InitStructure.GPIO_Pin = PWM2_GPIO_PIN;						
//			GPIO_Init(PWM2_GPIO,&GPIO_InitStructure);						 
//			 
//			TIM_TimeBaseInit(PWM2_TIM,&TIM_TimeBaseStructure);
//			TIM_ARRPreloadConfig(PWM2_TIM, ENABLE);
//            TIM_OC2Init(PWM2_TIM, &TIM_OCInitStructure); 
//	        //2
//            GPIO_InitStructure.GPIO_Pin = PWM3_GPIO_PIN;						
//			GPIO_Init(PWM3_GPIO,&GPIO_InitStructure);						 
//			 
//			TIM_TimeBaseInit(PWM3_TIM,&TIM_TimeBaseStructure);
//			TIM_ARRPreloadConfig(PWM3_TIM, ENABLE);
//			TIM_OC3Init(PWM3_TIM, &TIM_OCInitStructure);	 
//	        //3
//            GPIO_InitStructure.GPIO_Pin = PWM4_GPIO_PIN;						
//			GPIO_Init(PWM4_GPIO,&GPIO_InitStructure);						 
//			 
//			TIM_TimeBaseInit(PWM4_TIM,&TIM_TimeBaseStructure);
//			TIM_ARRPreloadConfig(PWM4_TIM, ENABLE);	
//			TIM_OC4Init(PWM4_TIM, &TIM_OCInitStructure);	 
//            //4
//}


void PWM_On(PWM_CHN_enum PWM_CHNx)
{
    if (PWM_CHNx == PWM1)
    {
			TIM_Cmd(PWM1_TIM, ENABLE);
			TIM_CCxCmd(PWM1_TIM, PWM1_TIM_CHANNEL, TIM_CCx_Enable); 			
    }
    else if (PWM_CHNx == PWM2)
    {
			TIM_Cmd(PWM2_TIM, ENABLE);
			TIM_CCxCmd(PWM2_TIM, PWM2_TIM_CHANNEL, TIM_CCx_Enable); 			
    }		
    else if (PWM_CHNx == PWM3)
    {
			TIM_Cmd(PWM3_TIM, ENABLE);
			TIM_CCxCmd(PWM3_TIM, PWM3_TIM_CHANNEL, TIM_CCx_Enable); 			
    }		
    else if (PWM_CHNx == PWM4)
    {
			TIM_Cmd(PWM4_TIM, ENABLE);
			TIM_CCxCmd(PWM4_TIM, PWM4_TIM_CHANNEL, TIM_CCx_Enable); 			
    }		    
}

/**
  * @brief  Disables the specified Advance PWM peripheral.
  * @param PWMx: where x can be 15, 16 to select the PWMx peripheral.
  *        And at this time, the PWM_NUM_MAX and PWM_NUM_USED which is defined at stm32f10x_pwm.h
  *        must equal to x or be greater than x.
  * @retval : ERROR or SUCCESS.
  */
void PWM_Off(PWM_CHN_enum PWM_CHNx)
{			
    if (PWM_CHNx == PWM1)
    {
			TIM_Cmd(PWM1_TIM, ENABLE);
			TIM_CCxCmd(PWM1_TIM, PWM1_TIM_CHANNEL, TIM_CCx_Disable); 			
    }
    else if (PWM_CHNx == PWM2)
    {
			TIM_Cmd(PWM2_TIM, ENABLE);
			TIM_CCxCmd(PWM2_TIM, PWM2_TIM_CHANNEL, TIM_CCx_Disable); 			
    }		
    else if (PWM_CHNx == PWM3)
    {
			TIM_Cmd(PWM3_TIM, ENABLE);
			TIM_CCxCmd(PWM3_TIM, PWM3_TIM_CHANNEL, TIM_CCx_Disable); 			
    }		
    else if (PWM_CHNx == PWM4)
    {
			TIM_Cmd(PWM4_TIM, ENABLE);
			TIM_CCxCmd(PWM4_TIM, PWM4_TIM_CHANNEL, TIM_CCx_Disable); 			
    }	
}

void PWM_Duty_Setting(PWM_CHN_enum PWM_CHNx, float PWM_Duty)
{
    uint16_t pulse;	
	if(PWM_Duty > PWM_MAXDUTY) PWM_Duty   = PWM_MAXDUTY;
	if(PWM_Duty < PWM_MINDUTY) PWM_Duty   = PWM_MINDUTY;	
	
	pulse = (uint16_t)(PWM_Duty*Arr/100.0f+0.5);	
    
    if(PWM_CHNx == PWM1)
    TIM_SetCompare1(PWM1_TIM, pulse);	 						 			 
    else  if(PWM_CHNx == PWM2)
	TIM_SetCompare2(PWM2_TIM, pulse);	 
    else  if(PWM_CHNx == PWM3)
	TIM_SetCompare3(PWM3_TIM, pulse);	 
    else  if(PWM_CHNx == PWM4)
	TIM_SetCompare4(PWM4_TIM, pulse);	 
   	
}
//void PWM_Init(PWM_CHN_enum PWM_CHNx)
//{
//    GPIO_InitTypeDef             GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef      TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef            TIM_OCInitStructure;
//	uint16_t                     Psc;
//	uint16_t                     Pulse;	

//	Psc   = ceil(72000000/PWM_FREQ_DEFAULT/65535.0f);
//	Arr   = (uint16_t)(72000000/PWM_FREQ_DEFAULT/Psc);
//    Pulse = PWM_DUTY_DEFAULT;

//	GPIO_StructInit(&GPIO_InitStructure); 	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
//		
//	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//	TIM_TimeBaseStructure.TIM_Period            = Arr - 1;
//	TIM_TimeBaseStructure.TIM_Prescaler         = Psc - 1;
//	TIM_TimeBaseStructure.TIM_ClockDivision     = 0;
//	TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up;
//		
//	TIM_OCStructInit(&TIM_OCInitStructure);	
//	TIM_OCInitStructure.TIM_OCMode              = PWM_OCMODE_DEFAULT;
//	TIM_OCInitStructure.TIM_OutputState         = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_Pulse               = Pulse;
//	TIM_OCInitStructure.TIM_OCPolarity          = PWM_POLARITY_DEFAULT;		

//	switch(PWM_CHNx)
//	{
//        case PWM1:
//            GPIO_InitStructure.GPIO_Pin = PWM1_GPIO_PIN;
//            GPIO_Init(PWM1_GPIO,&GPIO_InitStructure);						 
//			 
//			TIM_TimeBaseInit(PWM1_TIM,&TIM_TimeBaseStructure);
//			TIM_ARRPreloadConfig(PWM1_TIM, ENABLE);
//				
//			switch(PWM1_TIM_CHANNEL)
//			{
//                case TIM_Channel_1:
//                    TIM_OC1Init(PWM1_TIM, &TIM_OCInitStructure);	 
//					break;
//				case TIM_Channel_2:
//                    TIM_OC2Init(PWM1_TIM, &TIM_OCInitStructure); 
//					break;
//				case TIM_Channel_3:
//					TIM_OC3Init(PWM1_TIM, &TIM_OCInitStructure);	 
//					break;
//				case TIM_Channel_4:
//					TIM_OC4Init(PWM1_TIM, &TIM_OCInitStructure);	 
//					break;
//				default:
//					break;							 			 
//			}									
//			break;		
//		case PWM2:
//            GPIO_InitStructure.GPIO_Pin = PWM2_GPIO_PIN;						
//			GPIO_Init(PWM2_GPIO,&GPIO_InitStructure);						 
//			 
//			TIM_TimeBaseInit(PWM2_TIM,&TIM_TimeBaseStructure);
//			TIM_ARRPreloadConfig(PWM2_TIM, ENABLE);
//				
//			switch(PWM2_TIM_CHANNEL)
//			{
//                case TIM_Channel_1:
//					TIM_OC1Init(PWM2_TIM, &TIM_OCInitStructure);	 
//					break;
//				case TIM_Channel_2:
//					TIM_OC2Init(PWM2_TIM, &TIM_OCInitStructure); 
//					break;
//				case TIM_Channel_3:
//					TIM_OC3Init(PWM2_TIM, &TIM_OCInitStructure);	 
//					break;
//				case TIM_Channel_4:
//					TIM_OC4Init(PWM2_TIM, &TIM_OCInitStructure);	 
//					break;
//				default:
//					break;							 			 
//			}			
//			break;		
//		case PWM3:
//            GPIO_InitStructure.GPIO_Pin = PWM3_GPIO_PIN;						
//			GPIO_Init(PWM3_GPIO,&GPIO_InitStructure);						 
//			 
//			TIM_TimeBaseInit(PWM3_TIM,&TIM_TimeBaseStructure);
//			TIM_ARRPreloadConfig(PWM3_TIM, ENABLE);
//				
//			switch(PWM3_TIM_CHANNEL)
//			{
//                case TIM_Channel_1:
//					TIM_OC1Init(PWM3_TIM, &TIM_OCInitStructure);	 
//					break;
//				case TIM_Channel_2:
//					TIM_OC2Init(PWM3_TIM, &TIM_OCInitStructure); 
//					break;
//				case TIM_Channel_3:
//					TIM_OC3Init(PWM3_TIM, &TIM_OCInitStructure);	 
//					break;
//				case TIM_Channel_4:
//					TIM_OC4Init(PWM3_TIM, &TIM_OCInitStructure);	 
//					break;
//				default:
//					break;							 			 
//			}			
//			break;		
//		case PWM4:
//            GPIO_InitStructure.GPIO_Pin = PWM4_GPIO_PIN;						
//			GPIO_Init(PWM4_GPIO,&GPIO_InitStructure);						 
//			 
//			TIM_TimeBaseInit(PWM4_TIM,&TIM_TimeBaseStructure);
//			TIM_ARRPreloadConfig(PWM4_TIM, ENABLE);
//				
//			switch(PWM4_TIM_CHANNEL)
//			{
//                case TIM_Channel_1:
//                    TIM_OC1Init(PWM4_TIM, &TIM_OCInitStructure);	 
//					break;
//				case TIM_Channel_2:
//					TIM_OC2Init(PWM4_TIM, &TIM_OCInitStructure); 
//					break;
//				case TIM_Channel_3:
//					TIM_OC3Init(PWM4_TIM, &TIM_OCInitStructure);	 
//					break;
//				case TIM_Channel_4:
//					TIM_OC4Init(PWM4_TIM, &TIM_OCInitStructure);	 
//					break;
//				default:
//					break;							 			 
//			}			
//			break;			
//		default:
//			break;
//	}	
//}


//void PWM_On(PWM_CHN_enum PWM_CHNx)
//{
//    switch(PWM_CHNx)
//	{
//        case PWM1:
//			TIM_Cmd(PWM1_TIM, ENABLE);
//			TIM_CCxCmd(PWM1_TIM, PWM1_TIM_CHANNEL, TIM_CCx_Enable); 			
//			break;				
//		 case PWM2:
//			TIM_Cmd(PWM2_TIM, ENABLE);
//			TIM_CCxCmd(PWM2_TIM, PWM2_TIM_CHANNEL, TIM_CCx_Enable); 	
//			break;				
//		 case PWM3:
//			TIM_Cmd(PWM3_TIM, ENABLE);
//			TIM_CCxCmd(PWM3_TIM, PWM3_TIM_CHANNEL, TIM_CCx_Enable); 
//			break;				
//		 case PWM4:
//			TIM_Cmd(PWM4_TIM, ENABLE);
//			TIM_CCxCmd(PWM4_TIM, PWM4_TIM_CHANNEL, TIM_CCx_Enable); 
//            break;				
//		 default:
//			break;	
//	}
//}

///**
//  * @brief  Disables the specified Advance PWM peripheral.
//  * @param PWMx: where x can be 15, 16 to select the PWMx peripheral.
//  *        And at this time, the PWM_NUM_MAX and PWM_NUM_USED which is defined at stm32f10x_pwm.h
//  *        must equal to x or be greater than x.
//  * @retval : ERROR or SUCCESS.
//  */
//void PWM_Off(PWM_CHN_enum PWM_CHNx)
//{
//    switch(PWM_CHNx)
//	{
//        case PWM1:
//			TIM_CCxCmd(PWM1_TIM, PWM1_TIM_CHANNEL, TIM_CCx_Disable); 			
//			break;				
//		 case PWM2:
//			TIM_CCxCmd(PWM2_TIM, PWM2_TIM_CHANNEL, TIM_CCx_Disable); 	
//			break;				
//		 case PWM3:
//			TIM_CCxCmd(PWM3_TIM, PWM3_TIM_CHANNEL, TIM_CCx_Disable); 
//			break;				
//		 case PWM4:
//			TIM_CCxCmd(PWM4_TIM, PWM4_TIM_CHANNEL, TIM_CCx_Disable); 
//			break;				
//		 default:
//			break;	
//	}	
//}

//void PWM_Duty_Setting(PWM_CHN_enum PWM_CHNx, float PWM_Duty)
//{
//    uint16_t pulse;	
//	 
//	if(PWM_Duty > PWM_MAXDUTY) PWM_Duty   = PWM_MAXDUTY;
//	if(PWM_Duty < PWM_MINDUTY) PWM_Duty   = PWM_MINDUTY;	
//	
//	pulse = (uint16_t)(PWM_Duty*Arr/100.0f+0.5);	
//    
//    switch(PWM_CHNx)
//	{
//        case PWM1:
//            switch(PWM1_TIM_CHANNEL)
//			{
//                case TIM_Channel_1:
//                    TIM_SetCompare1(PWM1_TIM, pulse);	 
//				    break;
//				case TIM_Channel_2:
//				    TIM_SetCompare2(PWM1_TIM, pulse);	 
//				    break;
//				case TIM_Channel_3:
//				    TIM_SetCompare3(PWM1_TIM, pulse);	 
//				    break;
//				case TIM_Channel_4:
//				    TIM_SetCompare4(PWM1_TIM, pulse);	 
//				    break;
//				default:
//                    break;							 			 
//			}			 
//			break;
//	    case PWM2:
//            switch(PWM2_TIM_CHANNEL)
//			{
//                case TIM_Channel_1:
//                    TIM_SetCompare1(PWM2_TIM, pulse);	 
//				    break;
//				case TIM_Channel_2:
//				    TIM_SetCompare2(PWM2_TIM, pulse);	 
//				    break;
//				case TIM_Channel_3:
//				    TIM_SetCompare3(PWM2_TIM, pulse);	 
//				    break;
//				case TIM_Channel_4:
//				    TIM_SetCompare4(PWM2_TIM, pulse);	 
//				    break;
//				default:
//                    break;							 			 
//			}			 
//			break;
//	    case PWM3:
//			switch(PWM3_TIM_CHANNEL)
//			{
//                case TIM_Channel_1:
//                    TIM_SetCompare1(PWM3_TIM, pulse);	 
//				    break;
//				case TIM_Channel_2:
//				    TIM_SetCompare2(PWM3_TIM, pulse);	 
//				    break;
//				case TIM_Channel_3:
//				    TIM_SetCompare3(PWM3_TIM, pulse);	 
//				    break;
//				case TIM_Channel_4:
//				    TIM_SetCompare4(PWM3_TIM, pulse);	 
//				    break;
//				default:
//                    break;							 			 
//			}			 
//			break;
//	    case PWM4:
//			switch(PWM4_TIM_CHANNEL)
//			{
//                case TIM_Channel_1:
//                    TIM_SetCompare1(PWM4_TIM, pulse);	 
//				    break;
//				case TIM_Channel_2:
//				    TIM_SetCompare2(PWM4_TIM, pulse);	 
//				    break;
//				case TIM_Channel_3:
//				    TIM_SetCompare3(PWM4_TIM, pulse);	 
//				    break;
//				case TIM_Channel_4:
//				    TIM_SetCompare4(PWM4_TIM, pulse);	 
//				    break;
//                default:
//                    break;							 			 
//			}			 
//			break;			
//		default:
//			break;
//   }	
//}

