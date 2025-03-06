/**********************************************************************************************************/
#include "SysTickDelay.h"
/**********************************************************************************************************/
#define SYSTICK_COUNTFLAG           16
#define SYSTICK_ENABLE              0    /* Config-Bit to start or stop the SysTick Timer                         */
#define SYSTICK_CLKSOURCE           2    /* Clocksource has the offset 2 in SysTick Control and Status Register   */

static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;//ms延时倍乘数
/**********************************************************************************************************
*函 数 名: void SysTick_Initaize(void)
*功能说明: 系统时钟初始化
*形    参：无
*返 回 值: 无
**********************************************************************************************************/
//SYSTICK的时钟固定为HCLK时钟的1/8
//SYSCLK:系统时钟
void SysTick_Initaize(void)
	{                                                       
	SysTick->CTRL  &=		(~SYSTICK_CLKSOURCE);				//0xfffffffb;		//bit2清空,选择外部时钟  HCLK/8
	
	fac_us=(SystemCoreClock/1000000)/8;	 						//1us需计算的脉冲个数,其中(SystemFrequency/1000000)代表1US的脉冲个数,8是需要8分频		 
	fac_ms=(u16)fac_us*1000;           							//1ms需计算的脉冲个数
	}
/**********************************************************************************************************
*函 数 名: void delay_ms(u16 nms)
*功能说明: 延时n毫秒
*形    参：nms
*返 回 值: 无
**********************************************************************************************************/
//延时nms
//对72M条件下,nms<=1864 
void delay_ms(u16 nms)
	{	 		  	  
	u32 temp;	
	SysTick->LOAD=(u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL   =  (0x00);                     /* Load the SysTick Counter Value */         //清空计数器
	SysTick->CTRL =  (1<<SYSTICK_ENABLE); /* Enable SysTick and SysTick Timer */               //开始倒数  
	do
		{		temp=SysTick->CTRL;
		}
	while((temp&0x01)&&(!(temp&(1<<SYSTICK_COUNTFLAG))));//等待时间到达   
	SysTick->CTRL	&=  (~(1<<SYSTICK_ENABLE));    //关闭计数器
	SysTick->VAL   =  (0x00);                     /* Load the SysTick Counter Value */         //清空计数器
	}   
/**********************************************************************************************************
*函 数 名: void delay_us(u32 nus)
*功能说明: 延时n微秒
*形    参：nms
*返 回 值: 无
**********************************************************************************************************/	
//延时nus
//nus为要延时的us数.		    								   
void delay_us(u32 nus)
	{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //时间加载	  		 
	SysTick->VAL   =  (0x00);                     /* Load the SysTick Counter Value */         //清空计数器
	SysTick->CTRL = (1<<SYSTICK_ENABLE); 		/* Enable SysTick and SysTick Timer */         //开始倒数 	 
	do
		{
		temp=SysTick->CTRL;
		}
	while(temp&0x01&&!(temp&(1<<SYSTICK_COUNTFLAG)));//等待时间到达   

	SysTick->CTRL = 0x00;
	SysTick->VAL   =  (0x00);                     /* Load the SysTick Counter Value */         //清空计数器
	}














