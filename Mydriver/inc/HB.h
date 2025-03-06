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
void lcd_rst(void);	//复位指令，该指令发送后mcu 等待30ms
void lcd_light(void);
void lcd_open_src(void);
void lcd_clr_src(void);	//整屏清屏
void scroll_up(void);	//整屏上移
void scroll_right(void);	//整屏左移
void scroll_speed(u8 speed);	//调整移动速度speed range 0 to 15
void ascii(u8 x,u8 y,u8 symbol);	//显示8*8 ASCII字符
void character(u8 x,u8 y,char a[]);	//显示国标汉字
void shining(u8 a,u8 line,u8 row,u8 quotient,u8 residual,u8 z);
void data_string(u8 x,u8 y,char a[]);
//中文和8*16ASCII字符混合字符串显示（8*16意思是8列16行）
void lcd_test(void);
void myprintf_int(u8 x,u8 y,int dt);
void myprintf_str(u8 x,u8 y,char* pa);
void myprintf_2h(u8 x,u8 y,u8 dt);
void myprintf_u8(u8 x,u8 y,u8 dt);

#define sLCDport   PCout(10)

#endif
