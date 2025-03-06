#include "stm32f10x.h"
#include "SysTickDelay.h"
#include "HCSR04.h"
#include "HB.h"
#include "stm32f10x_MapSCOMandSBUS.h" 
#include "stm32f10x_scom.h"	 
#include "math.h"
float Front, Left, Right;

float HCSR_time=0;			//声明变量，用来计时
float HCSR_time_end=0;		//声明变量，存储回波信号时间

SBUSData_Struct SBUSdata;
extern SCOM_READ_DATA_Struct      SCOM3_rxData;
/**********************************************************************************************************
*函 数 名: HCSR_timer_Init
*功能说明: 超声波测距定时器初始化（TIM5）
*形    参：无
*返 回 值: 无
**********************************************************************************************************/
void HCSR_timer_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;			//定义结构体，配置定时器
    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);		//启用TIM5时钟
	TIM_InternalClockConfig(TIM5);								//设置TIM5使用内部时钟
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//设置1分频（不分频）
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//设置计数模式为向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 10 - 1;			   //设置最大计数值，达到最大值触发更新，计数10次是10-1,每10微秒触发一次
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;			//设置时钟预分频，72-1就是每 时钟频率(72Mhz)/72=1000000 个时钟周期计数器加1,每1微秒+1
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;		//重复计数器（高级定时器才有
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStructure);			//初始化
	
	TIM_ClearFlag(TIM5, TIM_FLAG_Update);			//清除更新中断标志位
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);		//开启更新中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);				//设置中断优先级分组
	//定义结构体，配置中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;				//指定中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//中断使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			//设置响应优先级
	NVIC_Init(&NVIC_InitStructure);	
    //	TIM_Cmd(TIM5, ENABLE);							//开启定时器
}
float front=0;
void HC_SR04_Init(HCSR04_enum HCSRx)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//启用GPIOB的外设时钟	
    //定义结构体 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//设置GPIO口为推挽输出
    GPIO_InitStructure.GPIO_Pin = HCSR_CH1_Trig_GPIO_PIN;	//设置GPIO口
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//设置GPIO口速度50Mhz
    GPIO_Init(HCSR_CH1_Trig_GPIO,&GPIO_InitStructure);		//初始化GPIO

   switch(HCSRx)
   {
       case HCSR_CH1:
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//设置GPIO口为推挽输出
        GPIO_InitStructure.GPIO_Pin = HCSR_CH1_Trig_GPIO_PIN;	//设置GPIO口
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//设置GPIO口速度50Mhz
        GPIO_Init(HCSR_CH1_Trig_GPIO,&GPIO_InitStructure);		//初始化GPIO
	
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;			//设置GPIO口为下拉输入模式
        GPIO_InitStructure.GPIO_Pin = HCSR_CH1_Echo_GPIO_PIN;	//设置GPIO口
        GPIO_Init(HCSR_CH1_Echo_GPIO,&GPIO_InitStructure);		//初始化GPIO
        GPIO_WriteBit(HCSR_CH1_Echo_GPIO,HCSR_CH1_Echo_GPIO_PIN,Bit_RESET);			//输出低电平
        delay_us(15);											//延时15微秒
       break;
       
       case HCSR_CH2:
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		
        GPIO_InitStructure.GPIO_Pin = HCSR_CH2_Trig_GPIO_PIN;	
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
        GPIO_Init(HCSR_CH2_Trig_GPIO,&GPIO_InitStructure);		
	
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;			
        GPIO_InitStructure.GPIO_Pin = HCSR_CH2_Echo_GPIO_PIN;	
        GPIO_Init(HCSR_CH2_Echo_GPIO,&GPIO_InitStructure);		
        GPIO_WriteBit(HCSR_CH2_Echo_GPIO,HCSR_CH2_Echo_GPIO_PIN,Bit_RESET);			
        delay_us(15);											
       break;
       
       case HCSR_CH3:
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		
        GPIO_InitStructure.GPIO_Pin = HCSR_CH3_Trig_GPIO_PIN;	
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
        GPIO_Init(HCSR_CH3_Trig_GPIO,&GPIO_InitStructure);		
	
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;			
        GPIO_InitStructure.GPIO_Pin = HCSR_CH3_Echo_GPIO_PIN;	
        GPIO_Init(HCSR_CH3_Echo_GPIO,&GPIO_InitStructure);		
        GPIO_WriteBit(HCSR_CH3_Echo_GPIO,HCSR_CH3_Trig_GPIO_PIN,Bit_RESET);			
        delay_us(15);											
       break;
       
       case HCSR_CH4:
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		
        GPIO_InitStructure.GPIO_Pin = HCSR_CH4_Trig_GPIO_PIN;	
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
        GPIO_Init(HCSR_CH4_Trig_GPIO,&GPIO_InitStructure);		
	
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;			
        GPIO_InitStructure.GPIO_Pin = HCSR_CH4_Echo_GPIO_PIN;	
        GPIO_Init(HCSR_CH4_Echo_GPIO,&GPIO_InitStructure);		
        GPIO_WriteBit(HCSR_CH4_Echo_GPIO,HCSR_CH4_Trig_GPIO_PIN,Bit_RESET);			
        delay_us(15);											
       break;
 	default:
			break;
    }
}
/**********************************************************************************************************
*函 数 名: sonar_mm(HCSR04_enum HCSRx)
*功能说明: 不同的HCSR口返回对应距离结果
*形    参：HCSRx（1,2,3,4）
*返 回 值: Distance_mm（测距结果）
**********************************************************************************************************/
uint16_t sonar_mm(HCSR04_enum HCSRx)									//测距并返回单位为毫米的距离结果
{
	uint32_t Distance;
    uint32_t Distance_mm = 0;
    
    if (HCSRx == HCSR_CH1)
    {    
             GPIO_WriteBit(HCSR_CH1_Trig_GPIO,HCSR_CH1_Trig_GPIO_PIN,Bit_SET);					//输出高电平
	         delay_us(20);										                                //延时15微秒
	         GPIO_WriteBit(HCSR_CH1_Trig_GPIO,HCSR_CH1_Trig_GPIO_PIN,Bit_RESET);				//输出低电平
	         while(GPIO_ReadInputDataBit(HCSR_CH1_Echo_GPIO,HCSR_CH1_Echo_GPIO_PIN)==0);		//等待低电平结束
	         HCSR_time=0;												                        //计时清零
	         while(GPIO_ReadInputDataBit(HCSR_CH1_Echo_GPIO,HCSR_CH1_Echo_GPIO_PIN)==1);		//等待高电平结束
	         HCSR_time_end=HCSR_time;										                    //记录结束时的时间
    }
     else if (HCSRx == HCSR_CH2)
     {
             GPIO_WriteBit(HCSR_CH2_Trig_GPIO,HCSR_CH2_Trig_GPIO_PIN,Bit_SET);						
	         delay_us(20);										            
	         GPIO_WriteBit(HCSR_CH2_Trig_GPIO,HCSR_CH2_Trig_GPIO_PIN,Bit_RESET);					
	         while(GPIO_ReadInputDataBit(HCSR_CH2_Echo_GPIO,HCSR_CH2_Echo_GPIO_PIN)==0);		
	         HCSR_time=0;												       
	         while(GPIO_ReadInputDataBit(HCSR_CH2_Echo_GPIO,HCSR_CH2_Echo_GPIO_PIN)==1);		
	         HCSR_time_end=HCSR_time;										            
     }
     else if (HCSRx == HCSR_CH3)
     {
             GPIO_WriteBit(HCSR_CH3_Trig_GPIO,HCSR_CH3_Trig_GPIO_PIN,Bit_SET);						
	         delay_us(20);										            
	         GPIO_WriteBit(HCSR_CH3_Trig_GPIO,HCSR_CH3_Trig_GPIO_PIN,Bit_RESET);				
	         while(GPIO_ReadInputDataBit(HCSR_CH3_Echo_GPIO,HCSR_CH3_Echo_GPIO_PIN)==0);		
	         HCSR_time=0;												       
	         while(GPIO_ReadInputDataBit(HCSR_CH3_Echo_GPIO,HCSR_CH3_Echo_GPIO_PIN)==1);		
	         HCSR_time_end=HCSR_time;										            
   
     }
     else if (HCSRx == HCSR_CH3)
     {
             GPIO_WriteBit(HCSR_CH4_Trig_GPIO,HCSR_CH4_Trig_GPIO_PIN,Bit_SET);						
	         delay_us(15);										           
	         GPIO_WriteBit(HCSR_CH4_Trig_GPIO,HCSR_CH4_Trig_GPIO_PIN,Bit_RESET);						
	         while(GPIO_ReadInputDataBit(HCSR_CH4_Echo_GPIO,HCSR_CH4_Echo_GPIO_PIN)==0);		
	         HCSR_time=0;												        
	         while(GPIO_ReadInputDataBit(HCSR_CH4_Echo_GPIO,HCSR_CH4_Echo_GPIO_PIN)==1);		
	         HCSR_time_end=HCSR_time;										           
     }
	if(HCSR_time_end/100<38)								//判断是否小于38毫秒，大于38毫秒的就是超时，直接调到下面返回0
	{
		Distance=(HCSR_time_end*346)/2;						//计算距离，25°C空气中的音速为346m/s
		Distance_mm=Distance/100;						    //因为上面的time_end的单位是10微秒，所以要得出单位为毫米的距离结果，还得除以100
	}
return Distance_mm;									//返回测距结果
}

float sonar(HCSR04_enum HCSRx)										//测距并返回单位为米的距离结果
{
    	float Distance_m = 0;
        float Distance_mm = 0;
    
        Distance_mm =sonar_mm(HCSRx);
		Distance_m = Distance_mm/1000;
	return Distance_m;
}
/**********************************************************************************************************
*函 数 名: TIM5_IRQHandler
*功能说明: TIM中断累加
*形    参：无
*返 回 值: 无
**********************************************************************************************************/
void TIM5_IRQHandler(void)			//更新中断函数，用来计时，每10微秒变量time加1
{									
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) == SET)		//获取TIM5定时器的更新中断标志位
	{
		HCSR_time++;
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);			//清除更新中断标志位
	}
}

/**********************************************************************************************************
*函 数 名: HCSR_print(float Front, float Left, float Right)
*功能说明: 输出三维测距结果，使用lcd输出
*形    参：无
*返 回 值: 无
**********************************************************************************************************/
void HCSR_print(float Front, float Left, float Right)
{
    int data;
    u8 m0,m1,m2;
    Map_SCOMtoSBUS(&SBUSdata,SCOM3_rxData.data);//获取SBUS
    
    myprintf_str(1,1,"HCSR measure");

    myprintf_str(1,2,"front");
	data=(int) (Front*100);
	m0=data/100+0x30;
	m1=(data%100)/10+0x30;
	m2=data%10+0x30;
	ascii(7,2,m0);
    myprintf_str(8,2,".");
	ascii(9,2,m1);
	ascii(10,2,m2);

    myprintf_str(1,3,"left ");
    data=(int) (Left*100);
	m0=data/100+0x30;
	m1=(data%100)/10+0x30;
	m2=data%10+0x30;
	ascii(7,3,m0);
    myprintf_str(8,3,".");
	ascii(9,3,m1);
	ascii(10,3,m2);

    myprintf_str(1,4,"right");
    data=(int) (Right*100);
	m0=data/100+0x30;
	m1=(data%100)/10+0x30;
	m2=data%10+0x30;
	ascii(7,4,m0);
    myprintf_str(8,4,".");
	ascii(9,4,m1);
	ascii(10,4,m2);
    if (SBUSdata.FlagByte == 1)
		{
            myprintf_str(1,6,"!");
            myprintf_int(5,6,(int)(SBUSdata.Channel_shuipin));
            myprintf_int(10,6,(int)(SBUSdata.Channel_chuizhi));
		}
}
 
/*==========================================================*/

