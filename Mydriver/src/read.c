#include "read.h"
#include "SysTickDelay.h"
//#include "pwm.h"
#include "timer.h"


extern u8  TIM2CH1_CAPTURE_STA;	//输入捕获状态		    				
extern u16 TIM2CH1_CAPTURE_VAL;	//输入捕获值
extern u8  TIM4CH1_CAPTURE_STA;	//输入捕获状态		    				
extern u16 TIM4CH1_CAPTURE_VAL;	//输入捕获值
extern u8  TIM5CH2_CAPTURE_STA;	//输入捕获状态		    				
extern u16 TIM5CH2_CAPTURE_VAL;	//输入捕获值
 
//PA4 测量车前方障碍距离
float read_qian()
{
	float temp;
	
	 GPIO_SetBits(GPIOA,GPIO_Pin_4);						 //PA.4 输出高
	 delay_us(20);
	 GPIO_ResetBits(GPIOA,GPIO_Pin_4);						 //PA.4 输出低
	 delay_ms(20);
		 
		if(TIM2CH1_CAPTURE_STA&0X80)//成功捕获到了一次高电平
		{
			temp=TIM2CH1_CAPTURE_STA&0X3F;
			temp*=65536;					//溢出时间总和
			temp+=TIM2CH1_CAPTURE_VAL;		//得到总的高电平时间
			temp=temp*170*0.0001;
			
 			TIM2CH1_CAPTURE_STA=0;			//开启下一次捕获
			return temp;
 		}
		else return 99;

}
float read_you()
{
	float temp1;
	
	 GPIO_SetBits(GPIOA,GPIO_Pin_3);						 //PA.3 输出高
	 delay_us(20);
	 GPIO_ResetBits(GPIOA,GPIO_Pin_3);						 //PA.3 输出低
	 delay_ms(20);
		 
		if(TIM4CH1_CAPTURE_STA&0X80)//成功捕获到了一次高电平
		{
			temp1=TIM4CH1_CAPTURE_STA&0X3F;
			temp1*=65536;					//溢出时间总和
			temp1+=TIM4CH1_CAPTURE_VAL;		//得到总的高电平时间
			temp1=temp1*170*0.0001;
			
 			TIM4CH1_CAPTURE_STA=0;			//开启下一次捕获
			return temp1;
 		}
		else return 99;

}

float read_zuo()
{
	float temp2;
	
	 GPIO_SetBits(GPIOA,GPIO_Pin_5);						 //PA.5 输出高
	 delay_us(20);
	 GPIO_ResetBits(GPIOA,GPIO_Pin_5);						 //PA.5 输出低
	 delay_ms(20);
		 
		if(TIM5CH2_CAPTURE_STA&0X80)//成功捕获到了一次高电平
		{
			temp2=TIM5CH2_CAPTURE_STA&0X3F;
			temp2*=65536;					//溢出时间总和
			temp2+=TIM5CH2_CAPTURE_VAL;		//得到总的高电平时间
			temp2=temp2*170*0.0001;
			
 			TIM5CH2_CAPTURE_STA=0;			//开启下一次捕获
			return temp2;
 		}
		else return 99;

}

