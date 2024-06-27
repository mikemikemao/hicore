/******************************************************************************
  文 件 名   : CRC16.h
  版 本 号   : v1.0.0
  作    者   : yangwenwei
  生成日期   : 2014年4月8日
  最近修改   :
  功能描述   : 
  函数列表   :
  修改历史   :
  1.日    期   : 2014年4月8日
    作    者   : yangwenwei
    修改内容   : 创建文件

******************************************************************************/
#ifndef _CRC16_H_
#define _CRC16_H_

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned int u32;

unsigned short Cal_Crc16(unsigned char dat, unsigned short crctmp);
unsigned short Crc16_get(unsigned char *pbyData, u32 dwLen);

//unsigned short hik_crc16_get(unsigned char *pbyData ,u32 wLen);
//unsigned short hik_cal_crc16(unsigned char dat,unsigned short crctmp);
#endif /*_RFAPP_H_*/

