/**	@file opdevsdk_hardware_all_device_info.h
 *	@note 2012-2019 HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 *	@brief �豸��ϸ��Ϣͷ�ļ�
 *
 *	@author		baozhonghui
 *	@date		2020/09/11
 *
 *	@note ��ʷ��¼��
 *	@note 2020/09/11 V1.0.0 baozhonghui �½��ļ�
 *
 *	@warning
 */



#ifndef __OPDEVSDK_HARDWARE_ALL_DEVICE_INFO_H__
#define __OPDEVSDK_HARDWARE_ALL_DEVICE_INFO_H__

/************************************************************************
 Included Header
 ************************************************************************/
 #include "opdevsdk_hardware_basic_device_info.h"
#include "opdevsdk_hardware.h"
#ifdef __cplusplus
extern "C" {
#endif


/************************************************************************
 Macros
 ************************************************************************/

/************************************************************************
 Type Definition
 ************************************************************************/

#pragma pack (4)                        //�������ڴ��а���4�ֽڶ���
	typedef struct {
		unsigned char	 major; 			//���汾��
		unsigned char	 minor; 			//�ΰ汾��
		unsigned char	 revision;			//�޶���
		unsigned char	 res[1];
	} OPDEVSDK_ST_CPLD_VERSION;

	typedef struct {
		unsigned char	 year;				//�� Ĭ��ǰ��20,����ֵΪ19��ʾ2019��
		unsigned char	 month; 			//��
		unsigned char	 day;				//��
		unsigned char	 res[5];
	} OPDEVSDK_ST_CPLD_DATA;

	typedef struct {
		unsigned char	 major; 			//���汾��
		unsigned char	 minor; 			//�ΰ汾��
		unsigned char	 revision;			//�޶���
		unsigned char	 res[1];
	} OPDEVSDK_ST_CPLD_BOARD;

	typedef struct {
		unsigned char	 volume;			//��SOC����DDR������ 0-0MB,1-8MB,2-16MB,3-32MB,4-64MB,5-128MB,6-256MB,7-512MB,8-1GB,9-2GB,10-4GB,11-8GB
		unsigned char	 num;				//��SOC����DDR����   0-��,1-1Ƭ����,2-2Ƭ����,4-4Ƭ����,6-6Ƭ����,8-8Ƭ����
		unsigned char	 res[6];
	} OPDEVSDK_ST_CPLD_DDR;

	typedef struct {
		unsigned char	 spk_func;			//spk���� 0-��,1-SPK1�Խ�,2-SPK1�Խ�+SPK2�㲥����+SPK3�㲥����
		unsigned char	 mic_func;			//mic���� 0-��,1-MIC1�Խ�
		unsigned char	 aec;				//�Ƿ�Ӳ�������� 0-��,1-��
		unsigned char	 res[5];
	} OPDEVSDK_ST_CPLD_AUDIO;

	typedef struct {
		unsigned char	 type;				//����ͷ���� 0-��,1-�ɼ���,2-����,3-��Ĥ,4-TOF,5-�ṹ��,6-�ȳ���
		unsigned char	 chip;				/*����ͷоƬ
											  0-��,1-OS02K10 200W,2-OS02D10 200W,3-IMX307 200W,4-OS05A20 500W,5-MN34422 200W,6-OPN8008
											*/
		unsigned char	 rotation;			//����ͷ��ת�Ƕ� 0-0,1-90��,2-180��,3-270�� ��ת����Ϊ˳ʱ�뷽��
		unsigned char	 cam_lens;			/*��ͷ����
											  0-��Ч
											  1-STF28S5F
											  2-STF04Y5F
											  3-STP37S1F
											  4-STF04P6F
											  5-STF28S5F_3MPIR
											  6-STF04Y5F_3MPIR
											  7-STF02S1F_2MPIR
											  8-ACS-STF15SY1F-5MP
											*/
		unsigned char	 res[8];
	} OPDEVSDK_ST_CPLD_SENSOR;

	typedef struct {
		unsigned char	 resolution;		/*��ʾ���ֱ���
											  0-��,
											  1-240*320,
											  2-320*480,
											  3-480*272,
											  4-480*800,
											  5-640*480,
											  6-600*1024,
											  7-1024*600,
											  8-800*1280,
											  9-1280*800,
											  10-1366*768,
											  11-1920*1080
											*/
		unsigned char	 rotation;			//��ʾ����ת�Ƕ� 0-0��,1-90��,2-180��,3-270�� ��ת����Ϊ˳ʱ�뷽��
		unsigned char	 touchscreen;		//������ 0-��,1-�� ����ͼ������ԭ������Ϊ���Ͻ�(x0,y0)
        unsigned char    size;              //ʵ�ʳߴ� * 10�����֧��25.5��(��Ӧ255)
        unsigned char    res[4];
	} OPDEVSDK_ST_CPLD_LCD;

	typedef struct {
		unsigned char	 rf1356;			//13.56M RFоƬ 0-��,1-��
		unsigned char	 rf125k;			//125K RFоƬ   0-��,1-��
		unsigned char	 wifi_module;		//WIFIģ��	  0-��,1-��
		unsigned char	 wifi_probe;		//WIFI̽��	  0-��,1-��
		unsigned char	 bluetooth; 		//����оƬ		0-��,1-��
		unsigned char	 mcm;				//�ƶ�ͨ��ģ��(mobile communication module) 0-��,1-��
		unsigned char	 sub1g; 			//Sub1G RFоƬ  0-��,1-��
		unsigned char	 zigbee;			//ZigBeeоƬ	  0-��,1-��
		unsigned char	 gps;				//��λģ��		0-��,1-��
		unsigned char	 res[7];
	} OPDEVSDK_ST_CPLD_WIRELESS;

	typedef struct {
		unsigned char	 out_num;			//����IO������ӿڵ�����(�����ܶ����ƽ����,xxx��ֵ��ʾ����)
		unsigned char	 in_num;			//����IO������ӿڵ�����(��������,�Ŵ�,���Ű�ť,xxx��ֵ��ʾ����)
		unsigned char	 relay_num; 		//�̵����������(����,����)
		unsigned char	 res[5];
	} OPDEVSDK_ST_CPLD_EXIO;

	typedef struct {
		/* 0x000 */ unsigned int	 magic; 			//ħ���� HKVS
		/* 0x004 */ unsigned int	 checksum;			//�ṹ��CRCУ���,Ԥ���ݲ���
		/* 0x008 */ OPDEVSDK_ST_CPLD_VERSION		 version;			//�ṹ��汾��Ϣ
		/* 0x00C */ OPDEVSDK_ST_CPLD_DATA			 date;				//�ṹ����������

		/* 0x014 */ unsigned int	 pcb;				//���ӵ�pcb��
		/* 0x018 */ OPDEVSDK_ST_CPLD_BOARD 		 board_attr;		//�����ͺ� Ӳ���İ汾1.0.A 1.1.B�Ķ���

		/* 0x01C */ unsigned char	 res1[4];

		/* 0x020 */ OPDEVSDK_ST_CPLD_DDR			 ddr_attr;			//�ڴ���Ϣ
		/* 0x028 */ OPDEVSDK_ST_CPLD_AUDIO 		 audio_attr;		//��Ƶ��Ϣ
		/* 0x030 */ unsigned int	 sensor_num;		//sensor����	 ���֧��4��
		/* 0x034 */ OPDEVSDK_ST_CPLD_SENSOR		 sensor_attr[4];	//sensor��Ϣ
		/* 0x064 */ OPDEVSDK_ST_CPLD_LCD			 main_lcd;			//������Ϣ
		/* 0x06C */ OPDEVSDK_ST_CPLD_LCD			 secondary_lcd; 	//������Ϣ
		/* 0x074 */ unsigned int	 external_interface;//�����ʾ���Ľӿ� 0-��,1-HDMI,2-VGA,3-HDMI+VGA
		/* 0x078 */ unsigned char	 res2[24];

		/* 0x090 */ unsigned int	 se_type;			//����оƬ���� 0-��,1-CPU����֤,2-Desfire��֤,3-CPU����֤+Desfire��֤
		/* 0x094 */ OPDEVSDK_ST_CPLD_WIRELESS		 wireless_attr; 	//����������Ϣ
		/* 0x0A4 */ OPDEVSDK_ST_CPLD_EXIO			 exio_attr; 		//���������������IO��Ϣ
		/* 0x0AC */ unsigned char	 net_num;			//����������� 0-10
		/* 0x0AD */ unsigned char	 usb_num;			//USB���� 	 0-10
		/* 0x0AE */ unsigned char	 rs485_num; 		//RS485����	 0-10
		/* 0x0AF */ unsigned char	 rs232_num; 		//RS232����	 0-10
		/* 0x0B0 */ unsigned char	 wiegand_num;		//Τ������	   0-10
		/* 0x0B1 */ unsigned char	 res3[15];

		/* 0x0C0 */ unsigned char	 board_temp;		//�����¶ȴ����� 0-��,1-��
		/* 0x0C1 */ unsigned char	 thermopile_temp;	//�ȵ�Ѳ���	  0-��,1-��
		/* 0x0C2 */ unsigned char	 ambient_temp;		//�����¶ȴ����� 0-��,1-��
		/* 0x0C3 */ unsigned char	 env_humidity;		//����ʪ�ȴ����� 0-��,1-��
		/* 0x0C4 */ unsigned char	 pm2p5; 			//PM2.5������	0-��,1-��
		/* 0x0C5 */ unsigned char	 res4[27];

		/* 0x0E0 */ unsigned char	 poe;				//POE		   0-��,1-��
		/* 0x0E1 */ unsigned char	 touchkey_num;		//����оƬ�ϵİ������� 0-16
		/* 0x0E2 */ unsigned char	 fp_interface;		//ָ�ƽӿ�	   0-��,1-SPI,2-8080,3-DVP,4-MIPI,5-USB,6-UART,7-RS485,8-RS232
		/* 0x0E3 */ unsigned char	 tamper;			//�Ƿ�֧�ַ��� 0-��,1-��
		/* 0x0E4 */ unsigned char	 tf;				//TF�� 		0-��,1-��
		/* 0x0E5 */ unsigned char	 beep;				//������ 	  0-��,1-��
		/* 0x0E6 */ unsigned char	 qr_code;			//��ά��(Quick Response Code)ģ��	 0-��,1-��
		/* 0x0E7 */ unsigned char	 res5[25];

		/* 0x100 */ unsigned char	 res6[256];
	} OPDEVSDK_ST_CPLD;
#pragma pack ()

typedef struct {
        /*�ṹ��ͷ ��16�ֽ�*/
        unsigned int    magic_number;                   //0 ����  ��Чֵ0x484b5753
        unsigned int    para_checksum;                  //4 �ṹ��У���
        unsigned int    para_length;                    //8 �ṹ����  �����ȴ�'encryptVer'��ʼ����
        unsigned int    encrypt_ver;                    //12 ���ܰ汾:���ڿ��ƴ˽ṹ�ĸ��� ��ǰ��0x00020000(V20)

        /*�豸������Ϣ  ��256�ֽ�*/
        unsigned char   language[16];                   //16 ����λ��Ӧ�����ԣ�1��ʾ֧�֣�0��ʾ��֧�֣����Զ������
                                                                //bit0��Ӣ�� bit1���������� bit2���������� bit3������ bit4�������� bit5��ӡ���� bit6���ɹ��� bit7��Խ�� bit8�������� bit9��̩��
                                                                //bit10�����ɱ� bit11��ӡ���� bit12���ϼ����� bit13�������� bit14���Ჴ���� bit15�������� bit16���ڿ����� bit17����Ɲ����� bit18������������ bit19������
                                                                //bit20������������ bit21�����޵����� bit22�������� bit23����̩�������� bit24���������� bit25��������˹�� bit26���������� bit27���������� bit28������ά���� bit29����������
                                                                //bit30��ϣ������ bit31��ϣ���� bit32������ bit33��������� bit34��������� bit35�������� bit36������ά���� bit37��Ų���� bit38���ݿ��� bit39��˹�工����
                                                                //bit40������ bit41�������� bit42����˹�� bit43���������� bit44����ɳ������ bit45������� bit46���������� bit47���������� bit48���������� bit49������������
                                                                //bit50�������� bit51�������� bit52���������� bit53���������� bit54�������������� bit55���������� bit56��������� bit57���������
        unsigned int    device_update_type;             //32 �豸�������ͣ��Ž���850-999���Խ���1000-1200��������У��ʱ��
        unsigned int    device_sdk_type;                //36 �豸�������ͣ��Ž���850-899 10501-11000 �Խ���602-700 11001-11500 ,���ظ�SDKʹ��
        unsigned int    device_sadp_type;               //40 �豸SADP����,�Ž�:Ŀǰά��:0xd0000-0xdffff �Խ���0xe000-0xe3ff
        unsigned int    mcu_device_update_type;         //44 mcu���豸���ͣ�����mcu����У�飬��Χ��device_update_typeһ��
        unsigned char   dev_model[64];                  //48 ��Ʒ�Զ����ͺ� �ַ���
        unsigned int    oem_code;                       //112 0-��Ч��1-������2-���� ��Ԥ����ǰδʵ��ʹ��
        unsigned char   prod_date[8];                   //116 �豸�������� �����գ�4λ���+2λ�·�+2λ�գ�
        unsigned char   prod_no[16];                    //124 �豸���кţ�����+��ĸ  ���䵽16 ��Ŀǰ����9λ
        unsigned char   random_code[6];                 //140 өʯ�����
        unsigned char   platform_type;                  //146 Ӳ��ƽ̨��������AI2,AI3��ƽ̨���ţ����ܹ��߸��ݸ��ֶδӷ������ϻ�ȡ��Ӧƽ̨�ļ�����Դ
        unsigned char   res1[125];                      //147 �豸������ϢԤ���ֶ�

        /*�㷨У����Ϣ ��128�ֽ�*/
        unsigned int    encrypt_alg_dev_class;          //272 �����о�Ժ�㷨У���ֶΣ�Ĭ�Ϻ�deviceUpdateType���
        unsigned char   encrypt_algorithm;              //276 �Ƿ�֧���о�Ժ�㷨��ȷ�ϣ����ܣ�0��֧�� 1֧�֣����ܹ�����Ҫͨ�����ֶν����о�Ժ�㷨��������
        unsigned char   self_algorithm;                 //277 �Ƿ�֧��ҵ���㷨���ܣ�0��֧�� 1֧�֣����ܹ�����Ҫͨ�����ֶν����㷨��������
        unsigned char   self_algo_auth[32];             //278 ҵ���㷨��֤��Կ,����ָ���㷨���ڲ�ֱ��ͨ������ֶ���֤��Ӧ�������֪��Ŀǰʵ��ʹ��16�ֽ�Ԥ��16�ֽ�
        unsigned char   crypto;                         //310 �豸�Ƿ���й����� 1���ǣ�0���� ����ֹ�豸�����ټ��ܵ������
        unsigned char   res2[89];                       //311 �㷨У����ϢԤ���ֶ�

        /*DSP������� ��128�ֽ�*/
        unsigned int    dsp_mem;                        //400 DSPʹ�õ��ڴ��С����λMB��BSP���ڷ���DSP�ڴ�
        unsigned char   encode_chans;                   //404 ����·����SDK/ISAPIЭ���У����ص�ͨ��������ʹ�õ��Ǹ�ֵ
        unsigned char   decode_chans;                   //405 ����·��
        unsigned char   vo_nums;                        //406 ֧��vo����: 0,1,2
        unsigned char   res3[121];                      //407 DSP�������Ԥ���ֶ�

        /*Ӳ����Ϣ�����ڶ���CPLD���޷���������ȷ�ϵ�Ӳ����Ϣ����ΪCPLDӲ����Ϣ�Ĳ��� ��128�ֽ�*/
        unsigned int    display_lcd_type;               //528 ��ʾ�����ͣ�0 - ��Ŀ��(213&211)/������(214&215)/��̩(233)�� 1 - �Ӱ�ͨ(313)���������ϣ����߸��ݲ�ͬ����ʹ�ò�ͬ����Ļ���ͣ�bsp����Ӧ�����ã�1���ֽھ͹��ˣ�0����0xff��ʾ��Чֵ��
        unsigned char   net_num;                        //532 ������ ���4·
        unsigned char   mac_addr[4][6];                 //533 �豸mac��ַ
        unsigned char   id_set_enable;                  //557 ���֤����ʹ��λ�����ƽ����ʹ��λ�� 0-ʧ�� 1-ʹ�ܣ� ����������ݶ�����ˢ����Чʱ������ʹ�ܸñ�־λ��������Ӧ��rfcfgReg��gsnonReg��cwgspReg��modgspReg�Ĵ���ֵ��Ӧ�ÿ��Ի�ȡ��ֵ�����ø����������Ƕ�������������
        unsigned char   rfcfg_reg;                      //558 ���֤�������Ĵ���26 ��0x00~0x3F��
        unsigned char   gsnon_reg;                      //559 ���֤�������Ĵ���27 ��0x00~0x3F��
        unsigned char   cwgsp_reg;                      //560 ���֤�������Ĵ���28 ��0x00~0x3F��
        unsigned char   modgsp_reg;                     //561 ���֤�������Ĵ���29 ��0x00~0x3F��
        unsigned char   res4[94];                       //562 Ӳ����ϢԤ���ֶ�

        /* Ԥ�� */
        unsigned char   res5[368];                      //656 ��Ԥ���ֽڣ���������Ԥ������ʱʹ�ø�Ԥ���ռ乲1024���ֽ�
} OPDEVSDK_ST_BOOT_PARAMS;


/**
 * @fn opdevsdk_all_device_info_get_boot_param
 * @brief ��ȡ������Ϣ
 * @param[out] pstruBootParam
 * @return OPDEVSDK_EN_FACE_ERR_CODE
 */
int opdevsdk_all_device_info_get_boot_param(OPDEVSDK_ST_BOOT_PARAMS *pstruBootParam);


/**
 * @fn opdevsdk_all_device_info_get_cpld_info
 * @brief ��ȡcpld��Ϣ
 * @param[out] pstruCpldInfo
 * @return OPDEVSDK_EN_FACE_ERR_CODE
 */
int opdevsdk_all_device_info_get_cpld_info(OPDEVSDK_ST_CPLD *pstruCpldInfo);


#ifdef __cplusplus
}
#endif
#endif // __OPDEVSDK_ALL_DEVICE_INFO_H__
