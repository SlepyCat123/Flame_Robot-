/**********************************************************************************************************/
#include "stm32f10x.h"

#include <stdio.h>
#include <stdlib.h>

/**********************************************************************************************************/
extern  void delay_us(u32 nus);
extern  void delay_ms(u16 nms);

void disp_GB2313(u16 addr,u8 length,char *hzp);
void dw_0x82_write(u16 addr,u16 data);
void dw_putpixel(u16 addr,u16 x,u16 y,u8 cr);             						/* 前景色画点           */
void dw_line(u16 addr,u16 x0,u16 y0,u16 x1,u16 y1,u8 cr);			        		/* 前景色画线           */
void fill_rectangular(u16 addr,u16 x0,u16 y0,u16 x1,u16 y1,u8 cr); 				/* 矩形填色     		*/
/**********************************************************************************************************/
extern send_a_byte(u8);
/**********************************************************************************************************/

u16 dwc[]={0x0000,0x001f,0x07e0,0x801f,0xf800,
		   		 0xf81f,0x8010,0xc618,0x8410,0x0010,
		   		 0x03c0,0x87ff,0xfc10,0xfc1f,0xffe0,
		   		 0xffff,0x0410,0x0418,0xe408};
/* 0  黑   */
/* 1  蓝   */
/* 2       */
/* 3  青   */
/* 4  红   */
/* 5  品红 */
/* 6  紫   */
/* 7  灰   */
/* 8       */
/* 9  深蓝 */
/* 10 绿   */
/* 11      */
/* 12      */
/* 13      */
/* 14 黄   */
/* 15 白   */
/* 16 绿   */
/* 17 湖蓝 */
/* 18 赭   */
/* 19      */
/* 20      */

/**********************************************************************************************************
*函 数 名: void dw_putpixel(u16 x,u16 y,u8 cr)
*功能说明: 前景色画点
*形    参：
*返 回 值: 无
**********************************************************************************************************/
void dw_putpixel(u16 addr,u16 x,u16 y,u8 cr)
{
	send_a_byte(0x5A);  
	send_a_byte(0xA5);  

	send_a_byte(0x0D); // 数据长度
	send_a_byte(0x82); //写变量存储器地址命令	
	
	send_a_byte(addr/256);  
	send_a_byte(addr%256); 

	send_a_byte(0x00); //画点控制字
	send_a_byte(0x01); 

	send_a_byte(0x00); //数据包数目
	send_a_byte(0x01); 
		
	send_a_byte(x/256);  
	send_a_byte(x%256);  
	
	send_a_byte(y/256);  
	send_a_byte(y%256);  
	
	send_a_byte(dwc[cr]/256);  
	send_a_byte(dwc[cr]%256); 

}

/**********************************************************************************************************
*函 数 名: void dw_line(u16 addr,u16 x0,u16 y0,u16 x1,u16 y1,u8 cr)
*功能说明: 前景色画线
*形    参：
*返 回 值: 无
**********************************************************************************************************/
void dw_line(u16 addr,u16 x0,u16 y0,u16 x1,u16 y1,u8 cr)
{
	
	send_a_byte(0x5A);  
	send_a_byte(0xA5);  

	send_a_byte(0x11); // 数据长度
	send_a_byte(0x82); //写变量存储器地址命令	
	
	send_a_byte(addr/256);  
	send_a_byte(addr%256); 

	send_a_byte(0x00); //连线控制字
	send_a_byte(0x02); 

	send_a_byte(0x00); //数据包数目
	send_a_byte(0x01); 

	send_a_byte(dwc[cr]/256);  
	send_a_byte(dwc[cr]%256); 
		
	send_a_byte(x0/256);  
	send_a_byte(x0%256);  
	
	send_a_byte(y0/256);  
	send_a_byte(y0%256);
	  
	send_a_byte(x1/256);  
	send_a_byte(x1%256);  
	
	send_a_byte(y1/256);  
	send_a_byte(y1%256); 
}

/**********************************************************************************************************
*函 数 名: void fill_rectangular(u16 x0,u16 y0,u16 x1,u16 y1,u8 cr)
*功能说明: 矩形填色 
*形    参：
*返 回 值: 无
**********************************************************************************************************/
void fill_rectangular(u16 addr,u16 x0,u16 y0,u16 x1,u16 y1,u8 cr) /* 矩形填色     */
{
	send_a_byte(0x5A);  
	send_a_byte(0xA5);  

	send_a_byte(0x11); // 数据长度
	send_a_byte(0x82); //写变量存储器地址命令	
	
	send_a_byte(addr/256);  
	send_a_byte(addr%256); 

	send_a_byte(0x00); //矩形控制字
	send_a_byte(0x03); 

	send_a_byte(0x00); //数据包数目
	send_a_byte(0x01); 
				
	send_a_byte(x0/256);  
	send_a_byte(x0%256);  
	
	send_a_byte(y0/256);  
	send_a_byte(y0%256);  
	
	send_a_byte(x1/256);  
	send_a_byte(x1%256);  
	
	send_a_byte(y1/256);  
	send_a_byte(y1%256);  
	
	send_a_byte(dwc[cr]/256);  
	send_a_byte(dwc[cr]%256); 
}
/**********************************************************************************************************
*函 数 名: void dw_0x82_write(u16 addr,u16 data)
*功能说明: 前景色画线
*形    参：向变量存储器地址写数据
*返 回 值: 无
**********************************************************************************************************/
void dw_0x82_write(u16 addr,u16 data)
{
	send_a_byte(0x5A);//帧头
	send_a_byte(0xA5);//帧头
	send_a_byte(0x05);//数据长度
	send_a_byte(0x82);//写变量存储器指令
	send_a_byte(addr/256);//地址高位 
	send_a_byte(addr%256);//地址低位
	send_a_byte(data/256);
	send_a_byte(data%256);
}
/**********************************************************************************************************
*函 数 名: void disp_GB2313(u16 addr,u8 length,char *hzp)
*功能说明: 显示汉字
*形    参：
*返 回 值: 无
**********************************************************************************************************/
void disp_GB2313(u16 addr,u8 length,char *hzp) /*  显示汉字  display chinese */
{
	send_a_byte(0x5A);	//帧头
	send_a_byte(0xA5);	//帧头
	send_a_byte(3+length);//数据长度
	send_a_byte(0x82);	//写变量存储器指令
	send_a_byte(addr/256);//地址高位 
	send_a_byte(addr%256);//地址低位	
	while(*hzp)
	{
		send_a_byte(*hzp);  
		hzp++;
	}
}
/********************************************end of file*************************************************/

