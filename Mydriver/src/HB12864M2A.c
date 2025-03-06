/**********************************************************************************************************/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "mydef.h"
#include "HB.h"
#include "Serial.h"
extern  void delay_us(u32 nus);
extern  void delay_ms(u16 nms); 
/**********************************************************************************************************/

/**********************************************************************************************************
*函 数 名: void GPIO_lcd(void)
*功能说明: ，配置lcd对应引脚pc10，初始化lcd屏幕
*形    参：无
*返 回 值: 无
**********************************************************************************************************/
void GPIO_lcd(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能PORTC时钟  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      // 推挽输出
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	
	sLCDport=1;
	delay_ms(150);
	lcd_rst();  delay_ms(150);
	lcd_light();delay_ms(10);
	lcd_open_src();delay_ms(10);
	lcd_clr_src(); delay_ms(10);
}

/*********************************************************/
void transmit(u8 a)	//bps=9600--104us
{
	sLCDport=0;delay_us(104);
	sLCDport=((a&0x01)==0x01);delay_us(104);
	sLCDport=((a&0x02)==0x02);delay_us(104);
	sLCDport=((a&0x04)==0x04);delay_us(104);
	sLCDport=((a&0x08)==0x08);delay_us(104);
	sLCDport=((a&0x10)==0x10);delay_us(104);
	sLCDport=((a&0x20)==0x20);delay_us(104);
	sLCDport=((a&0x40)==0x40);delay_us(104);
	sLCDport=((a&0x80)==0x80);delay_us(104);
	sLCDport=1;delay_us(104);
}

/**********************************************************/
u8 receive()
{  
	return(0xcc);
}

/**********************************************************/
void lcd_rst()	//复位指令，该指令发送后mcu 等待30ms
{  
	transmit(0xef);
	while(receive()!=0XCC);     
}

/**********************************************************/
void lcd_light(void)
{  
	transmit(0xe5);
	while(receive()!=0XCC);
}

/**********************************************************/
void lcd_open_src(void)
{ 
	transmit(0xff); 
	transmit(0x00);
	while(receive()!=0XCC);
}

/**********************************************************/
void lcd_clr_src(void)	//整屏清屏
{  
	transmit(0xf4);
	while(receive()!=0XCC);
}

/**********************************************************/
void scroll_up(void)	//整屏上移
{
	transmit(0xf5);
	while(receive()!=0XCC);
}

/**********************************************************/
void scroll_right(void)	//整屏左移
{
	transmit(0xf8);
	while(receive()!=0XCC);
}

/**********************************************************/
void scroll_speed(u8 speed)	//调整移动速度speed range 0 to 15
{
	transmit(0xfc);
	transmit(speed);
	while(receive()!=0XCC);
}

/**********************************************************/
void ascii(u8 x,u8 y,u8 symbol)	//显示8*8 ASCII字符
{  
	transmit(0xf1);
	transmit(y);	//列位置0-F
	transmit(x);	//行位置0-F
	transmit(symbol);	//ASCII字符代码
	while(receive()!=0XCC);
}
/**********************************************************/
void character(u8 x,u8 y,char a[])	//显示国标汉字
{
	transmit(0xf0);
	transmit(y);	//行位置
	transmit(x);	//列位置
	transmit(a[0]);	//国标内码
	transmit(a[1]);	//国标内码
	delay_ms(20);
	while(receive()!=0XCC);
}

/**********************************************************/
void shining(u8 a,u8 line,u8 row,u8 quotient,u8 residual,u8 z)	//任意指定区域显示数据自动闪烁
{
	transmit(0xc8);
	transmit(a);	//a=1为启动闪烁，0为关闭闪烁
	transmit(line);	//行坐标0-127
	transmit(row);		//列坐标0-127
	transmit(quotient);	//水平长度=8*quotient+residual
	transmit(residual);
	transmit(z);		//垂直方向的行数
	while(receive()!=0XCC);
}

/**********************************************************/
void data_string(u8 x,u8 y,char a[])	//中文和8*16ASCII字符混合字符串显示（8*16意思是8列16行）
{
	u8 i;
	transmit(0xe9);
	transmit(y);	//行位置0-7
	transmit(x);	//列位置0-F
	for(i=0;i<11;i++)	//2*5+1 怎样确定外部字符串长度
	transmit(a[i]);
	transmit(0x00);
	while(receive()!=0XCC);
}

/**********************************************************/
void myprintf_u8(u8 x,u8 y,u8 dt)
{
	u8 m0,m1,m2;
	
	m0=dt/100+0x30;
	m1=(dt%100)/10+0x30;
	m2=dt%10+0x30;
	ascii(x+0,y,m0);
	ascii(x+1,y,m1);
	ascii(x+2,y,m2);
}

void myprintf_int(u8 x,u8 y,int dt)
{
	u8 m0,m1,m2;
	
	m0=dt/100+0x30;
	m1=(dt%100)/10+0x30;
	m2=dt%10+0x30;
	ascii(x+0,y,m0);
	ascii(x+1,y,m1);
	ascii(x+2,y,m2);
}
/**********************************************************/
void myprintf_2h(u8 x,u8 y,u8 dt)
{
	u8 m0,m1;
	
	m0=dt/16;
	if(m0>9) m0=m0+0x37;
	else     m0=m0+0x30;
	m1=dt%16;
	if(m1>9) m1=m1+0x37;
	else     m1=m1+0x30;
	ascii(x+0,y,m0);
	ascii(x+1,y,m1);
}
 
/**********************************************************/
void myprintf_str(u8 x,u8 y,char* pa)
{
	u8 m,k;
	k=0;
	while(1)
	{
		m=*pa;
		if(m==0) break;
		ascii(x+k,y,m);
		pa++;
		k++;
	}
}
/*==========================================================*/

void lcd_test(void)
{
	u8 m;
	GPIO_lcd();
	while(1)
	{
		character(0,0,"显");//显示国标汉字
		character(1,0,"示");//显示国标汉字
		character(2,0,"国");//显示国标汉字
		character(3,0,"标");//显示国标汉字
		character(4,0,"汉");//显示国标汉字
		character(5,0,"字");//显示国标汉字
		character(0,1,"显");//显示国标汉字
		character(1,1,"示");//显示国标汉字
		character(2,2,"国");//显示国标汉字
		character(3,2,"标");//显示国标汉字
		character(4,3,"汉");//显示国标汉字
		character(5,3,"字");//显示国标汉字
		delay_ms(1500);
		lcd_clr_src(); delay_ms(10);
		m=0xa0;
		myprintf_2h(3,0,m+0);
		myprintf_2h(3,1,m+1);
		myprintf_2h(3,2,m+2);
		myprintf_2h(3,3,m+3);
		myprintf_2h(3,4,m+4);
		myprintf_2h(3,5,m+5);
		myprintf_2h(3,6,m+6);
		myprintf_2h(3,7,m+7);
		delay_ms(1500);
		lcd_clr_src(); delay_ms(10);
		myprintf_str(0,1,"qwerty");
		myprintf_str(2,3,"asdfghjk");
		myprintf_str(4,5,"zxcvbnm");
		//data_string(3,3,"显示123\n");
		delay_ms(1500);
		lcd_clr_src(); delay_ms(10);
	}
}
