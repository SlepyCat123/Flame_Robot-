#ifndef __HB_H
#define __HB_H
#include <stm32f10x.h>

#define RT_LEN3               10

extern u16 rcvcnt3;
extern u8  Re_update3,state_machine3,rcvdat3;
extern u8  rebuf3[RT_LEN3];
extern u8  trbuf3[RT_LEN3];
void lcd_rst(void);
void lcd_light(void);
void lcd_clr_src(void);
void lcd_open_src(void);
void GPIO_lcd(void);
void transmit(u8 a);	//bps=9600--104us
u8 receive(void);
void lcd_rst(void);	//��λָ���ָ��ͺ�mcu �ȴ�30ms
void lcd_light(void);
void lcd_open_src(void);
void lcd_clr_src(void);	//��������
void scroll_up(void);	//��������
void scroll_right(void);	//��������
void scroll_speed(u8 speed);	//�����ƶ��ٶ�speed range 0 to 15
void ascii(u8 x,u8 y,u8 symbol);	//��ʾ8*8 ASCII�ַ�
void character(u8 x,u8 y,char a[]);	//��ʾ���꺺��
void shining(u8 a,u8 line,u8 row,u8 quotient,u8 residual,u8 z);
void data_string(u8 x,u8 y,char a[]);
//���ĺ�8*16ASCII�ַ�����ַ�����ʾ��8*16��˼��8��16�У�
void lcd_test(void);
void myprintf_int(u8 x,u8 y,int dt);
void myprintf_str(u8 x,u8 y,char* pa);
void myprintf_2h(u8 x,u8 y,u8 dt);
void myprintf_u8(u8 x,u8 y,u8 dt);

#define sLCDport   PCout(10)

#endif
