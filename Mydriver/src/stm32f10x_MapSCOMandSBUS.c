	
#include "stm32f10x_MapSCOMandSBUS.h" 
#include <string.h>
/**-------------------- MapSCOMandSBUS_Exported_Functions ----------------**/

/*****************************************************************
  * @brief   将SCOM 数据匹配为 SBUS数据                            *
  * @param   SCOMdata：         *
            ChannelData[3]    1头FF 2指令 3判断
            ChannelSite[2]    位置坐标 1
  * @param   SBUSdata： SBUS数据存储指针，类型 SBUSData_Struct   *	
  * @retval  ERROR or SUCCESS.                                 
typedef struct _SBUSData_Struct              
{  
    uint8_t                  ChannelData[3];
    uint16_t                 Channel_shuipin;
    uint16_t                 Channel_chuizhi;
    uint8_t           	      FlagByte;
} SBUSData_Struct;


*****************************************************************/
ErrorStatus Map_SCOMtoSBUS(SBUSData_Struct *SBUSdata,uint8_t *SCOMdata)
{
    if((SCOMdata == NULL) && (SCOMdata[0] == 0xFF) && (SCOMdata[2] != 0x00))//头是0XFF
		{			
			  return ERROR;
		}
		SBUSdata->FlagByte        = 1;
		SBUSdata->ChannelData[0]  = SCOMdata[0] ;
		SBUSdata->ChannelData[1]  = SCOMdata[1] ;
		SBUSdata->ChannelData[2]  = SCOMdata[2] ;
		SBUSdata->Channel_shuipin  =(SCOMdata[4]>>8)|(SCOMdata[3]<<0);
		SBUSdata->Channel_chuizhi  =(SCOMdata[6]>>8)|(SCOMdata[5]<<0);
  
    return SUCCESS;		
}
///*****************************************************************
//  * @brief   将SBUS数据匹配为 SCOM数据                           *
//  * @param   SBUSdata： SBUS数据存储指针，类型 SBUSData_Struct   *	
//  *            16byte  11bit数据 	                               *
//  * @param   SCOMdata： 串口数据指针，要求数组长度25byte         *
// 	*         SCOMdata[0]                  首字节： 0x0F           *
//  *         SCOMdata[24]                 尾字节： 0x00           *
//  *         SCOMdata[23]                 标志字节： 默认0x00     *
//  *         SCOMdata[1]-SCOMdata[22]     用户数据                *	
//  * @retval  ERROR or SUCCESS.                                   *
//*****************************************************************/
//ErrorStatus Map_SBUStoSCOM(uint8_t *SCOMdata,SBUSData_Struct *SBUSdata)
//{
//    uint8_t                     ii;	
//	  uint16_t                    Tempdata[16];
//	
//    if(SBUSdata == NULL)
//		{
//        return ERROR;
//    }

//	  *(SCOMdata + 0) = 0x0F;	
//	  *(SCOMdata + 24) = 0x00;	
// 	  *(SCOMdata + 23) = SBUSdata->FlagByte; 

//		for(ii=0;ii<16;ii++)
//		{
//			 Tempdata[ii] = SBUSdata->Channel[ii] & 0x07FF;
//		}

//		*(SCOMdata + 1)  = Tempdata[0] & 0xFF;
//		*(SCOMdata + 2)  = (Tempdata[0]>>8)|(Tempdata[1]<<3);	
//		*(SCOMdata + 3)  = (Tempdata[1]>>5)|(Tempdata[2]<<6);	
//		*(SCOMdata + 4)  = (Tempdata[2]>>2);	
//		*(SCOMdata + 5)  = (Tempdata[2]>>10)|(Tempdata[3]<<1);
//		*(SCOMdata + 6)  = (Tempdata[3]>>7)|(Tempdata[4]<<4);
//		*(SCOMdata + 7)  = (Tempdata[4]>>4)|(Tempdata[5]<<7);	
//		*(SCOMdata + 8)  = (Tempdata[5]>>1);	
//		*(SCOMdata + 9)  = (Tempdata[5]>>9)|(Tempdata[6]<<2);
//		*(SCOMdata + 10) = (Tempdata[6]>>6)|(Tempdata[7]<<5);
//		*(SCOMdata + 11) = (Tempdata[7]>>3);
//		*(SCOMdata + 12) = Tempdata[8] &0xFF;		
//		*(SCOMdata + 13) = (Tempdata[8]>>8)|(Tempdata[9]<<3);		
//		*(SCOMdata + 14) = (Tempdata[9]>>5)|(Tempdata[10]<<6);
//		*(SCOMdata + 15) = (Tempdata[10]>>2);																																		
//		*(SCOMdata + 16) = (Tempdata[10]>>10)|(Tempdata[11]<<1);
//		*(SCOMdata + 17) = (Tempdata[11]>>7)|	(Tempdata[12]<<4);
//		*(SCOMdata + 18) = (Tempdata[12]>>4)|	(Tempdata[13]<<7);
//		*(SCOMdata + 19) = (Tempdata[13]>>1);	
//		*(SCOMdata + 20) = (Tempdata[13]>>9)|(Tempdata[14]<<2);	
//		*(SCOMdata + 21) = (Tempdata[14]>>6)|(Tempdata[15]<<5);	
//		*(SCOMdata + 22) = (Tempdata[15]>>3);		

//    return SUCCESS;
//}

//// /*********** (C) COPYRIGHT 2020 HANGZHOU NORMAL UNIVERSITY *****END OF FILE****/

