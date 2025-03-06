#include "stm32f10x.h"                 
#include "Timer.h"                  

TIM_ICInitTypeDef  TIM2_ICInitStructure;
TIM_ICInitTypeDef  TIM4_ICInitStructure;
TIM_ICInitTypeDef  TIM5_ICInitStructure;

void Timer_Init(Timer_HCSR_enum HCSRx)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;	                    //定义结构体，配置中断优先级
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		//启用TIM2时钟

	TIM_InternalClockConfig(TIM2);								//设置TIM2使用内部时钟
			//定义结构体，配置定时器
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//设置1分频（不分频）
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//设置计数模式为向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 10 - 1;			    //设置最大计数值，达到最大值触发更新事件，因为从0开始计数，所以计数10次是10-1,每10微秒触发一次
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;			//设置时钟预分频，72-1就是每 时钟频率(72Mhz)/72=1000000 个时钟周期计数器加1,每1微秒+1
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;		//重复计数器（高级定时器才有，所以设置0）
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);			//初始化TIM2定时器
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);			//清除更新中断标志位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);		//开启更新中断
		//初始化TIM2输入捕获参数
    switch(HCSRx)
    {
        case Timer_HCSR1:
             TIM2_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
            break;
        case Timer_HCSR2:
             TIM2_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	选择输入端 IC1映射到TI1上
            break;
        case Timer_HCSR3:
             TIM2_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	选择输入端 IC1映射到TI1上
            break;
        case Timer_HCSR4:
             TIM2_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC1S=01 	选择输入端 IC1映射到TI1上
            break;
     default:
        
     break;   
    }    
  	TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//设置中断优先级分组
					
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;				//指定中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//中断使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			//设置响应优先级
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);							//开启定时器
}


/*--------------------------
void Timer_HCSR1_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;	                    //定义结构体，配置中断优先级
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		//启用TIM3时钟
																// https://blog.zeruns.tech
	TIM_InternalClockConfig(TIM2);								//设置TIM3使用内部时钟
			//定义结构体，配置定时器
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//设置1分频（不分频）
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//设置计数模式为向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 10 - 1;			//设置最大计数值，达到最大值触发更新事件，因为从0开始计数，所以计数10次是10-1,每10微秒触发一次
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;			//设置时钟预分频，72-1就是每 时钟频率(72Mhz)/72=1000000 个时钟周期计数器加1,每1微秒+1
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;		//重复计数器（高级定时器才有，所以设置0）
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);			//初始化TIM3定时器
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);			//清除更新中断标志位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);		//开启更新中断
		//初始化TIM2输入捕获参数
    TIM2_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//设置中断优先级分组
					
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;				//指定中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//中断使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			//设置响应优先级
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);							//开启定时器
}

u8  TIM2CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM2CH1_CAPTURE_VAL;	//输入捕获值

void TIM2_IRQHandler(void)			//更新中断函数
{
 	if((TIM2CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM2CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM2CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM2CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM2CH1_CAPTURE_VAL=0XFFFF;
				}else TIM2CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			if(TIM2CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM2CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次上升沿
				TIM2CH1_CAPTURE_VAL=TIM_GetCapture1(TIM2);
		   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM2CH1_CAPTURE_STA=0;			//清空
				TIM2CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);
				TIM2CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   	TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
}

--------------------------*/

/*--------------------------
void Timer_HCSR1_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;	                    //定义结构体，配置中断优先级
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		//启用TIM3时钟
																// https://blog.zeruns.tech
	TIM_InternalClockConfig(TIM2);								//设置TIM3使用内部时钟
			//定义结构体，配置定时器
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//设置1分频（不分频）
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//设置计数模式为向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 10 - 1;			//设置最大计数值，达到最大值触发更新事件，因为从0开始计数，所以计数10次是10-1,每10微秒触发一次
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;			//设置时钟预分频，72-1就是每 时钟频率(72Mhz)/72=1000000 个时钟周期计数器加1,每1微秒+1
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;		//重复计数器（高级定时器才有，所以设置0）
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);			//初始化TIM3定时器
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);			//清除更新中断标志位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);		//开启更新中断
		//初始化TIM2输入捕获参数
    TIM2_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//设置中断优先级分组
					
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;				//指定中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//中断使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			//设置响应优先级
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);							//开启定时器
}

u8  TIM2CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM2CH1_CAPTURE_VAL;	//输入捕获值

void TIM2_IRQHandler(void)			//更新中断函数
{
 	if((TIM2CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM2CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM2CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM2CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM2CH1_CAPTURE_VAL=0XFFFF;
				}else TIM2CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			if(TIM2CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM2CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次上升沿
				TIM2CH1_CAPTURE_VAL=TIM_GetCapture1(TIM2);
		   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM2CH1_CAPTURE_STA=0;			//清空
				TIM2CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);
				TIM2CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   	TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
}

--------------------------*/


