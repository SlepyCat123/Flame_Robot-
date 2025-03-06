#include "calculate.h"
#include "SysTickDelay.h"
#include "motor.h"
/**********************************************************************************************************/
/**********************************************************************************************************
*函 数 名: Turn_calculate(float Left,float Right)
*功能说明: 转向计算，判断左右侧障碍距离，左近则右拐，右近左拐
*形    参：float Left,float Right
*返 回 值: 无
**********************************************************************************************************/
void Turn_calculate(float Left,float Right)
{
        if(Left < Right)
            {
             GO_Right();
             delay_ms(80);
            }
        else 
            {
             GO_Left ();
             delay_ms(500);
            }
}
/**********************************************************************************************************
*函 数 名: HCSR_calculate(float Front,float Left,float Right)
*功能说明: 避障逻辑计算
*形    参：float Front,float Left,float Right
*返 回 值: 无
**********************************************************************************************************/
void HCSR_calculate(float Front,float Left,float Right)
{
if( ((Front<0.60)||(Left<0.50)||(Right<0.50)))
  {
      if( ((Front<0.02)||(Left<0.02)||(Right<0.02) ))//HCSR故障数据过滤
      {
       GO_Stright();
      }
	else if((Front<0.12)||(Left<0.10)||(Right<0.10))//距离障碍过近，倒车
	{
    MT_BACK();    
    delay_ms(200);
    GO_Brake();
	delay_ms(50);
	}
    else if((Left<0.20)||(Right<0.20))
	{
        if (Front<0.15)
        {
            GO_Brake();
            delay_ms(50);
        }
        else
        {
         Turn_calculate( Left, Right);
        }     
	}
	else if(Left<0.35 || Right<0.40 )
	{
    Turn_calculate( Left, Right);
	}
	else
    GO_Stright();
	}		
     else     
     GO_Stright();//防卡死
}
