#ifndef __TIMER_H
#define __TIMER_H

typedef enum __Timer_HCSR_enum
{ 
Timer_HCSR1,
Timer_HCSR2,    
Timer_HCSR3,
Timer_HCSR4
}Timer_HCSR_enum;

void Timer_Init(Timer_HCSR_enum HCSRx);

#endif
