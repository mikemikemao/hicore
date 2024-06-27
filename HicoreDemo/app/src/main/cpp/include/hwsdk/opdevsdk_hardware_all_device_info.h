/**	@file opdevsdk_hardware_all_device_info.h
 *	@note 2012-2019 HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 *	@brief 设备详细信息头文件
 *
 *	@author		baozhonghui
 *	@date		2020/09/11
 *
 *	@note 历史记录：
 *	@note 2020/09/11 V1.0.0 baozhonghui 新建文件
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

#pragma pack (4)                        //设置在内存中按照4字节对齐
	typedef struct {
		unsigned char	 major; 			//主版本号
		unsigned char	 minor; 			//次版本号
		unsigned char	 revision;			//修订号
		unsigned char	 res[1];
	} OPDEVSDK_ST_CPLD_VERSION;

	typedef struct {
		unsigned char	 year;				//年 默认前置20,如数值为19表示2019年
		unsigned char	 month; 			//月
		unsigned char	 day;				//日
		unsigned char	 res[5];
	} OPDEVSDK_ST_CPLD_DATA;

	typedef struct {
		unsigned char	 major; 			//主版本号
		unsigned char	 minor; 			//次版本号
		unsigned char	 revision;			//修订号
		unsigned char	 res[1];
	} OPDEVSDK_ST_CPLD_BOARD;

	typedef struct {
		unsigned char	 volume;			//主SOC外置DDR总容量 0-0MB,1-8MB,2-16MB,3-32MB,4-64MB,5-128MB,6-256MB,7-512MB,8-1GB,9-2GB,10-4GB,11-8GB
		unsigned char	 num;				//主SOC外置DDR数量   0-无,1-1片外置,2-2片外置,4-4片外置,6-6片外置,8-8片外置
		unsigned char	 res[6];
	} OPDEVSDK_ST_CPLD_DDR;

	typedef struct {
		unsigned char	 spk_func;			//spk功能 0-无,1-SPK1对讲,2-SPK1对讲+SPK2广播高音+SPK3广播低音
		unsigned char	 mic_func;			//mic功能 0-无,1-MIC1对讲
		unsigned char	 aec;				//是否硬件消回音 0-无,1-是
		unsigned char	 res[5];
	} OPDEVSDK_ST_CPLD_AUDIO;

	typedef struct {
		unsigned char	 type;				//摄像头类型 0-无,1-可见光,2-红外,3-虹膜,4-TOF,5-结构光,6-热成像
		unsigned char	 chip;				/*摄像头芯片
											  0-无,1-OS02K10 200W,2-OS02D10 200W,3-IMX307 200W,4-OS05A20 500W,5-MN34422 200W,6-OPN8008
											*/
		unsigned char	 rotation;			//摄像头旋转角度 0-0,1-90°,2-180°,3-270° 旋转方向为顺时针方向
		unsigned char	 cam_lens;			/*镜头类型
											  0-无效
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
		unsigned char	 resolution;		/*显示屏分辨率
											  0-无,
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
		unsigned char	 rotation;			//显示屏旋转角度 0-0°,1-90°,2-180°,3-270° 旋转方向为顺时针方向
		unsigned char	 touchscreen;		//触摸屏 0-无,1-有 正视图触摸屏原点坐标为左上角(x0,y0)
        unsigned char    size;              //实际尺寸 * 10，最大支持25.5寸(对应255)
        unsigned char    res[4];
	} OPDEVSDK_ST_CPLD_LCD;

	typedef struct {
		unsigned char	 rf1356;			//13.56M RF芯片 0-无,1-有
		unsigned char	 rf125k;			//125K RF芯片   0-无,1-有
		unsigned char	 wifi_module;		//WIFI模组	  0-无,1-有
		unsigned char	 wifi_probe;		//WIFI探针	  0-无,1-有
		unsigned char	 bluetooth; 		//蓝牙芯片		0-无,1-有
		unsigned char	 mcm;				//移动通信模组(mobile communication module) 0-无,1-有
		unsigned char	 sub1g; 			//Sub1G RF芯片  0-无,1-有
		unsigned char	 zigbee;			//ZigBee芯片	  0-无,1-有
		unsigned char	 gps;				//定位模块		0-无,1-有
		unsigned char	 res[7];
	} OPDEVSDK_ST_CPLD_WIRELESS;

	typedef struct {
		unsigned char	 out_num;			//整机IO类输出接口的总数(三极管对外电平控制,xxx数值表示个数)
		unsigned char	 in_num;			//整机IO类输入接口的总数(报警输入,门磁,开门按钮,xxx数值表示个数)
		unsigned char	 relay_num; 		//继电器输出总数(报警,门锁)
		unsigned char	 res[5];
	} OPDEVSDK_ST_CPLD_EXIO;

	typedef struct {
		/* 0x000 */ unsigned int	 magic; 			//魔幻数 HKVS
		/* 0x004 */ unsigned int	 checksum;			//结构体CRC校验和,预留暂不用
		/* 0x008 */ OPDEVSDK_ST_CPLD_VERSION		 version;			//结构体版本信息
		/* 0x00C */ OPDEVSDK_ST_CPLD_DATA			 date;				//结构体制作日期

		/* 0x014 */ unsigned int	 pcb;				//板子的pcb号
		/* 0x018 */ OPDEVSDK_ST_CPLD_BOARD 		 board_attr;		//主板型号 硬件的版本1.0.A 1.1.B的定义

		/* 0x01C */ unsigned char	 res1[4];

		/* 0x020 */ OPDEVSDK_ST_CPLD_DDR			 ddr_attr;			//内存信息
		/* 0x028 */ OPDEVSDK_ST_CPLD_AUDIO 		 audio_attr;		//音频信息
		/* 0x030 */ unsigned int	 sensor_num;		//sensor个数	 最大支持4个
		/* 0x034 */ OPDEVSDK_ST_CPLD_SENSOR		 sensor_attr[4];	//sensor信息
		/* 0x064 */ OPDEVSDK_ST_CPLD_LCD			 main_lcd;			//主屏信息
		/* 0x06C */ OPDEVSDK_ST_CPLD_LCD			 secondary_lcd; 	//副屏信息
		/* 0x074 */ unsigned int	 external_interface;//外接显示器的接口 0-无,1-HDMI,2-VGA,3-HDMI+VGA
		/* 0x078 */ unsigned char	 res2[24];

		/* 0x090 */ unsigned int	 se_type;			//加密芯片类型 0-无,1-CPU卡认证,2-Desfire认证,3-CPU卡认证+Desfire认证
		/* 0x094 */ OPDEVSDK_ST_CPLD_WIRELESS		 wireless_attr; 	//无线外设信息
		/* 0x0A4 */ OPDEVSDK_ST_CPLD_EXIO			 exio_attr; 		//整机对外输入输出IO信息
		/* 0x0AC */ unsigned char	 net_num;			//有线网络个数 0-10
		/* 0x0AD */ unsigned char	 usb_num;			//USB个数 	 0-10
		/* 0x0AE */ unsigned char	 rs485_num; 		//RS485个数	 0-10
		/* 0x0AF */ unsigned char	 rs232_num; 		//RS232个数	 0-10
		/* 0x0B0 */ unsigned char	 wiegand_num;		//韦根个数	   0-10
		/* 0x0B1 */ unsigned char	 res3[15];

		/* 0x0C0 */ unsigned char	 board_temp;		//主板温度传感器 0-无,1-有
		/* 0x0C1 */ unsigned char	 thermopile_temp;	//热电堆测温	  0-无,1-有
		/* 0x0C2 */ unsigned char	 ambient_temp;		//环境温度传感器 0-无,1-有
		/* 0x0C3 */ unsigned char	 env_humidity;		//环境湿度传感器 0-无,1-有
		/* 0x0C4 */ unsigned char	 pm2p5; 			//PM2.5传感器	0-无,1-有
		/* 0x0C5 */ unsigned char	 res4[27];

		/* 0x0E0 */ unsigned char	 poe;				//POE		   0-无,1-有
		/* 0x0E1 */ unsigned char	 touchkey_num;		//按键芯片上的按键个数 0-16
		/* 0x0E2 */ unsigned char	 fp_interface;		//指纹接口	   0-无,1-SPI,2-8080,3-DVP,4-MIPI,5-USB,6-UART,7-RS485,8-RS232
		/* 0x0E3 */ unsigned char	 tamper;			//是否支持防拆 0-无,1-有
		/* 0x0E4 */ unsigned char	 tf;				//TF卡 		0-无,1-有
		/* 0x0E5 */ unsigned char	 beep;				//蜂鸣器 	  0-无,1-有
		/* 0x0E6 */ unsigned char	 qr_code;			//二维码(Quick Response Code)模组	 0-无,1-有
		/* 0x0E7 */ unsigned char	 res5[25];

		/* 0x100 */ unsigned char	 res6[256];
	} OPDEVSDK_ST_CPLD;
#pragma pack ()

typedef struct {
        /*结构体头 共16字节*/
        unsigned int    magic_number;                   //0 幻数  有效值0x484b5753
        unsigned int    para_checksum;                  //4 结构体校验和
        unsigned int    para_length;                    //8 结构长度  ，长度从'encryptVer'开始计算
        unsigned int    encrypt_ver;                    //12 加密版本:用于控制此结构的更改 当前是0x00020000(V20)

        /*设备基本信息  共256字节*/
        unsigned char   language[16];                   //16 各个位对应的语言，1表示支持，0表示不支持，可以多种组合
                                                                //bit0：英语 bit1：简体中文 bit2：繁体中文 bit3：日语 bit4：朝鲜语 bit5：印度语 bit6：蒙古语 bit7：越南 bit8：马来文 bit9：泰国
                                                                //bit10：菲律宾 bit11：印尼文 bit12：孟加拉文 bit13：老挝文 bit14：尼泊尔文 bit15：丹麦文 bit16：乌克兰文 bit17：乌茲别克语 bit18：亚美尼亚语 bit19：俄语
                                                                //bit20：保加利亚文 bit21：克罗地亚文 bit22：冰岛语 bit23：加泰罗尼亚文 bit24：匈牙利语 bit25：吉尔吉斯语 bit26：土库曼语 bit27：土耳其文 bit28：塞尔维亚文 bit29：塞索托语
                                                                //bit30：希伯来语 bit31：希腊语 bit32：德语 bit33：意大利语 bit34：意第绪语 bit35：拉丁文 bit36：拉脱维亚语 bit37：挪威文 bit38：捷克语 bit39：斯洛伐克文
                                                                //bit40：法语 bit41：波兰语 bit42：波斯语 bit43：爱尔兰语 bit44：爱沙尼亚语 bit45：瑞典语 bit46：瓜拉尼语 bit47：立陶宛语 bit48：索马里语 bit49：罗马尼亚语
                                                                //bit50：芬兰语 bit51：荷兰语 bit52：葡萄牙语 bit53：西班牙语 bit54：阿尔巴尼亚文 bit55：阿拉伯文 bit56：马其顿文 bit57：马耳他文
        unsigned int    device_update_type;             //32 设备升级类型，门禁：850-999；对讲：1000-1200，升级包校验时用
        unsigned int    device_sdk_type;                //36 设备网络类型，门禁：850-899 10501-11000 对讲：602-700 11001-11500 ,返回给SDK使用
        unsigned int    device_sadp_type;               //40 设备SADP类型,门禁:目前维护:0xd0000-0xdffff 对讲：0xe000-0xe3ff
        unsigned int    mcu_device_update_type;         //44 mcu的设备类型，用于mcu升级校验，范围跟device_update_type一样
        unsigned char   dev_model[64];                  //48 产品自定义型号 字符串
        unsigned int    oem_code;                       //112 0-无效，1-海康，2-中性 ，预留当前未实际使用
        unsigned char   prod_date[8];                   //116 设备生产日期 年月日（4位年份+2位月份+2位日）
        unsigned char   prod_no[16];                    //124 设备序列号，数字+字母  扩充到16 ，目前仅用9位
        unsigned char   random_code[6];                 //140 萤石随机码
        unsigned char   platform_type;                  //146 硬件平台，类型有AI2,AI3等平台代号，加密工具根据该字段从服务器上获取相应平台的加密资源
        unsigned char   res1[125];                      //147 设备基本信息预留字段

        /*算法校验信息 共128字节*/
        unsigned int    encrypt_alg_dev_class;          //272 用于研究院算法校验字段，默认和deviceUpdateType相等
        unsigned char   encrypt_algorithm;              //276 是否支持研究院算法（确认）加密：0不支持 1支持，加密工具需要通过该字段进行研究院算法加密流程
        unsigned char   self_algorithm;                 //277 是否支持业务部算法加密：0不支持 1支持，加密工具需要通过该字段进行算法加密流程
        unsigned char   self_algo_auth[32];             //278 业务部算法认证秘钥,后续指纹算法库内部直接通过这个字段认证，应用无需感知，目前实际使用16字节预留16字节
        unsigned char   crypto;                         //310 设备是否进行过加密 1：是，0：否 ，防止设备出厂再加密的情况。
        unsigned char   res2[89];                       //311 算法校验信息预留字段

        /*DSP相关能力 共128字节*/
        unsigned int    dsp_mem;                        //400 DSP使用的内存大小，单位MB，BSP用于分配DSP内存
        unsigned char   encode_chans;                   //404 编码路数，SDK/ISAPI协议中，返回的通道个数，使用的是该值
        unsigned char   decode_chans;                   //405 解码路数
        unsigned char   vo_nums;                        //406 支持vo个数: 0,1,2
        unsigned char   res3[121];                      //407 DSP相关能力预留字段

        /*硬件信息，用于定义CPLD中无法描述或者确认的硬件信息，作为CPLD硬件信息的补充 共128字节*/
        unsigned int    display_lcd_type;               //528 显示屏类型：0 - 三目宝(213&211)/利尔达(214&215)/广泰(233)； 1 - 视安通(313)，虚拟物料，产线根据不同批次使用不同的屏幕类型，bsp做相应的设置（1个字节就够了，0或者0xff表示无效值）
        unsigned char   net_num;                        //532 网口数 最大4路
        unsigned char   mac_addr[4][6];                 //533 设备mac地址
        unsigned char   id_set_enable;                  //557 身份证设置使能位（调制解调器使能位） 0-失能 1-使能， 当整机的身份读卡器刷卡无效时，可能使能该标志位，设置相应的rfcfgReg，gsnonReg，cwgspReg，modgspReg寄存器值，应用可以获取该值，配置给读卡器，是读卡器正常工作
        unsigned char   rfcfg_reg;                      //558 身份证读卡器寄存器26 （0x00~0x3F）
        unsigned char   gsnon_reg;                      //559 身份证读卡器寄存器27 （0x00~0x3F）
        unsigned char   cwgsp_reg;                      //560 身份证读卡器寄存器28 （0x00~0x3F）
        unsigned char   modgsp_reg;                     //561 身份证读卡器寄存器29 （0x00~0x3F）
        unsigned char   res4[94];                       //562 硬件信息预留字段

        /* 预留 */
        unsigned char   res5[368];                      //656 ，预留字节，其他分类预留不够时使用该预留空间共1024个字节
} OPDEVSDK_ST_BOOT_PARAMS;


/**
 * @fn opdevsdk_all_device_info_get_boot_param
 * @brief 获取加密信息
 * @param[out] pstruBootParam
 * @return OPDEVSDK_EN_FACE_ERR_CODE
 */
int opdevsdk_all_device_info_get_boot_param(OPDEVSDK_ST_BOOT_PARAMS *pstruBootParam);


/**
 * @fn opdevsdk_all_device_info_get_cpld_info
 * @brief 获取cpld信息
 * @param[out] pstruCpldInfo
 * @return OPDEVSDK_EN_FACE_ERR_CODE
 */
int opdevsdk_all_device_info_get_cpld_info(OPDEVSDK_ST_CPLD *pstruCpldInfo);


#ifdef __cplusplus
}
#endif
#endif // __OPDEVSDK_ALL_DEVICE_INFO_H__
