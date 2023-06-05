#include "HPR_Types.h"

/*��Ŀ����*/
#define MATERIAL_PICWIN_LIST_NO (1) //ͼƬ���ؼ�֧�����ͼƬ����
#define WIN_LIST_NO (1)            //���Ĵ��ڸ���,UI�Զ���֧��4��ͼƬ����,4�����ִ���,1��Ԥ������,1��ʱ�Ӵ���,1�����а�ť����,1�����Ű�ť����,1����ά�봰��,1����֤�ɹ�����,1����֤ʧ�ܴ���,1��״̬������

#define PAGE_LIST_NO (1)
#define PLAY_SPAN_LIST_NO (2)
#define MATERIAL_NAME_LEN (32)

typedef enum _PUBLISH_PROGRAM_TYPE_E
{
    PUBLISH_PROGRAM_TYPE_NORMAL = 0,      /*DEF*/
    PUBLISH_PROGRAM_TYPE_SCREENSAVER = 1, //����
    PUBLISH_PROGRAM_TYPE_CHARACTER = 2,   //��ӭ��
    PUBLISH_PROGRAM_TYPE_UI_DIY = 3,      //UI�������Զ���
    PUBLISH_PROGRAM_TYPE_IDLESCREEN = 4,  //��������
    PUBLISH_PROGRAM_TYPE_MAX = PUBLISH_PROGRAM_TYPE_IDLESCREEN
} PUBLISH_PROGRAM_TYPE_E;

/* �Ӵ������ͣ���֤����ʹ�ã� */
typedef enum _PUBLISH_SUBWIN_TYPE_E
{
    PUBLISH_SUBWIN_TYPE_DEF = 0,                       /*DEF*/
    PUBLISH_SUBWIN_TYPE_TEMPERATURE = 1,               //�¶�
    PUBLISH_SUBWIN_TYPE_FACEPIC = 2,                   //����ͼƬ
    PUBLISH_SUBWIN_TYPE_NAME = 3,                      //����
    PUBLISH_SUBWIN_TYPE_EMPLOYEENO = 4,                //����
    PUBLISH_SUBWIN_TYPE_GROUP = 5,                     //��֯/����
    PUBLISH_SUBWIN_TYPE_TIPS = 6,                      //��ʾ��Ϣ
    PUBLISH_SUBWIN_TYPE_MAX = PUBLISH_SUBWIN_TYPE_TIPS //�Ӵ����б�����������֤����ʹ�ã�
} PUBLISH_SUBWIN_TYPE_E;

/* ״̬����״̬���ͣ�״̬��ʹ�ã� */
typedef enum _PUBLISH_SUBSTATUS_TYPE_E
{
    PUBLISH_SUBSTATUS_TYPE_DEF = 0,                            /*DEF*/
    PUBLISH_SUBSTATUS_TYPE_DIAL = 1,                           //����״̬��3G4G�ȣ�
    PUBLISH_SUBSTATUS_TYPE_WIFI = 2,                           //WIFI״̬
    PUBLISH_SUBSTATUS_TYPE_EZVIZ = 3,                          //өʯ״̬
    PUBLISH_SUBSTATUS_TYPE_WIREDNETWORK = 4,                   //��������״̬
    PUBLISH_SUBSTATUS_TYPE_DEPLOY = 5,                         //����״̬
    PUBLISH_SUBSTATUS_TYPE_TEMPERATURE = 6,                    //����״̬
    PUBLISH_SUBSTATUS_TYPE_MAX = PUBLISH_SUBSTATUS_TYPE_TEMPERATURE //״̬����״̬��������״̬��ʹ�ã�
} PUBLISH_SUBSTATUS_TYPE_E;

typedef struct _RESOLUTION_INFO
{
    HPR_UINT8 byResolutionName; // 1920*1080,1080*1920
    HPR_UINT8 byRes[3];
    HPR_UINT32 dwImageWidth;
    HPR_UINT32 dwImageHeight;
} RESOLUTION_INFO_T;

typedef struct _POSITION_INFO
{
    /* 16 bytes */
    HPR_UINT32 positionX;
    HPR_UINT32 positionY;
    HPR_UINT32 height;
    HPR_UINT32 width;
} POSITION_INFO;

typedef struct _WIN_MATERIAL_INFO
{
    /* 8 bytes */
    HPR_UINT8 materialType;        // MATERIAL_TYPE_E
    HPR_UINT8 staticMaterialType;  // MATERIAL_STATIC_TYPE_E
    HPR_UINT8 dynamicMaterialType; // MATERIAL_DYNAMIC_TYPE_E
    HPR_UINT8 otherMaterialType;   // MATERIAL_OTHER_TYPE_E
    HPR_UINT8 res[4];
} WIN_MATERIAL_INFO;

typedef struct _PLAY_DURATION
{
    HPR_UINT8 durationType; // materialTime,selfDefine
    HPR_UINT8 byRes[3];
    HPR_UINT32 duration; //�زı�����ʱ�������ز�Ϊ��Ƶʱ��Ч
} PLAY_DURATION;

typedef struct _CHARACTERS_EFFECT
{
    HPR_UINT32 fontSize;       //�����С
    HPR_UINT32 fontColor;      //������ɫ
    HPR_UINT32 backColor;      //������ɫ
    HPR_UINT8 scrollDirection; //���ֹ������� left,right,up,down
    HPR_UINT8 byRes[3];
    HPR_UINT32 backTransparent; //����͸����
    HPR_UINT32 scrollSpeed;     //���ֹ����ٶ�
    HPR_UINT32 backgroundPic;   //����ͼ��ΪͼƬ�زĵ�ID
} CHARACTERS_EFFECT;

typedef struct _PLAY_ITEM
{
    HPR_UINT32 itemId;         //�������
    HPR_UINT32 itemMaterialNo; //�ز�������
    PLAY_DURATION playDuration;
    CHARACTERS_EFFECT charaEffect;
    HPR_UINT32 scaleType; //�ز��������� MATERIAL_SCALE_TYPE_E
} PLAY_ITEM;

typedef struct CHARACTERS_ATTRIBUTE
{
    HPR_UINT32 dwFontSize;                  // �����С
    HPR_UINT32 dwFontColor;                 // ������ɫ
    HPR_UINT32 dwBackgroundType;            // �������ͣ���ɫ��ͼƬ MATERIAL_BACKGROUND_TYPE_E
    HPR_UINT32 dwBackColor;                 // ������ɫ
    HPR_UINT32 dwBackTransparent;           // ����͸����
    HPR_UINT32 dwAlignType;                 // ���뷽ʽ������롢�Ҷ��롢�м����
    HPR_UINT32 dwVerticaAlignType;          // ��ֱ���뷽ʽ
    HPR_UINT8 abyCharacterContent[128 + 1]; // �������ݣ����128�ֽ�
    HPR_UINT8 byFillEnabled;                // ����ɫ���ʹ��
    HPR_UINT8 byRes[2];                    // �����ֽ�
    HPR_UINT32 dwBackPicId;                 // ���ֱ���ͼΪͼƬ�زĵ�ID
    HPR_UINT32 dwCharacterStyle;            // ����Ч������ͨ���Ӵ�
} CHARACTERS_ATTRIBUTE;



typedef struct _WINDOWS_INFO
{
    HPR_UINT8 byWinId;
    HPR_UINT8 byLayerNo;             // ���ڲ㼶
    HPR_UINT8 byEnabled;             // ʹ�ܣ��Ƿ����أ�
    HPR_UINT8 byRes[1];
    POSITION_INFO stWinPosition;     // ��������λ��
    WIN_MATERIAL_INFO stWinMaterial; // ��������
    union myUnion
    {
        PLAY_ITEM playItemList[MATERIAL_PICWIN_LIST_NO]; // ����
        CHARACTERS_ATTRIBUTE stCharaAttribute;           // ���ֻ�ӭ�ʹ��
    } myUnion;
} WINDOWS_INFO;

typedef struct _PAGE_INFO
{
    /* 3904 bytes */
    HPR_UINT32 dwPageId;                         // ҳ��ID
    HPR_UINT8 byPlayDurationMode;                // ҳ�沥��ʱ��ģʽ�����Զ�����Զ����Զ���ʱ��playDuration�ڵ���Ч
    HPR_UINT8 byPlayDuration;                    // ����ʱ�䣬��λ����
    HPR_UINT8 bySwitchDuration;                  // �л�ʱ�䣬��λ����
    HPR_UINT8 bySwitchEffect;                    // �л�Ч������Ϊ�ޣ��������״��������״չ�������ϲ��������²�����
    HPR_UINT32 dwBackgroundColor;                // ����ɫ
    HPR_UINT8 byBackgroundPic;                   // ����ͼ��ΪͼƬ�زĵ�ID
    HPR_UINT8 byCharacterMode;                   // ��ǰҳ�������ģʽ:ģʽ1��ģʽ2��ģʽ3
    HPR_UINT8 byRes2[2];
    WINDOWS_INFO winList[WIN_LIST_NO];           // Page�´��ڸ���,�������,�Զ����Ǵ������
} PAGE_INFO;

/* ��Ŀ */
typedef struct PROGRAM_INFO
{
    /* 4092 bytes */
    HPR_UINT32 dwProgramId; //��ĿID
    HPR_UINT32 dwtest; 
    HPR_UINT8 byProgramName[MATERIAL_NAME_LEN + 1];
    HPR_UINT8 byProgramType; //��Ŀ���� PUBLISH_PROGRAM_TYPE_E
    HPR_UINT8 bySharePpe;    //�������ԣ��ֹ��к�˽�� MATERIAL_SHARE_PROPERTY_E
    HPR_UINT8 byMaterialDurationFlag;                  // 0-Ĭ��ʹ��page��switchDuration��1-ʹ��playItem��duration
    RESOLUTION_INFO_T stProResolutionInfo;
    PAGE_INFO pageList[PAGE_LIST_NO];
} PROGRAM_INFO;

typedef union uWinInfo
{
    PLAY_ITEM playItemList[MATERIAL_PICWIN_LIST_NO]; // ����
    CHARACTERS_ATTRIBUTE stCharaAttribute;           // ���ֻ�ӭ�ʹ��
} uWinInfo;

typedef struct DEVICECONFIG
{
    PROGRAM_INFO stProgramParam[2];
    // uWinInfo myUnion;
} DEVICECONFIG;