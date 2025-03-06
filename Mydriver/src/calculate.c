#include "calculate.h"
#include "SysTickDelay.h"
#include "motor.h"
/**********************************************************************************************************/
/**********************************************************************************************************
*�� �� ��: Turn_calculate(float Left,float Right)
*����˵��: ת����㣬�ж����Ҳ��ϰ����룬������ҹգ��ҽ����
*��    �Σ�float Left,float Right
*�� �� ֵ: ��
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
*�� �� ��: HCSR_calculate(float Front,float Left,float Right)
*����˵��: �����߼�����
*��    �Σ�float Front,float Left,float Right
*�� �� ֵ: ��
**********************************************************************************************************/
void HCSR_calculate(float Front,float Left,float Right)
{
if( ((Front<0.60)||(Left<0.50)||(Right<0.50)))
  {
      if( ((Front<0.02)||(Left<0.02)||(Right<0.02) ))//HCSR�������ݹ���
      {
       GO_Stright();
      }
	else if((Front<0.12)||(Left<0.10)||(Right<0.10))//�����ϰ�����������
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
     GO_Stright();//������
}
