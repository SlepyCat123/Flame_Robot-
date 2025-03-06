#ifndef __AI_H
#define __AI_H
#include "stm32f10x.h"
#include "stdio.h"


/**********************************************************************************************************/
void Motor_L_Init(u8 n);
void Motor_R_Init(u8 n);
void GO_Stright(void);
void GO_Brake(void);
void MT_FORWARD(void);
void MT_BACK(void);
void GO_Left(void);
void GO_Right(void);
void MT_Shoot(void);

#endif

