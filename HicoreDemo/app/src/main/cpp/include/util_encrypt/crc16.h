/******************************************************************************
  �� �� ��   : CRC16.h
  �� �� ��   : v1.0.0
  ��    ��   : yangwenwei
  ��������   : 2014��4��8��
  ����޸�   :
  ��������   : 
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��4��8��
    ��    ��   : yangwenwei
    �޸�����   : �����ļ�

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

