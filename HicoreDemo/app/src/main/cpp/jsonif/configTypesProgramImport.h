#include "HPR_Types.h"

/*节目配置*/
#define MATERIAL_PICWIN_LIST_NO (1) //图片广告控件支持最多图片张数
#define WIN_LIST_NO (1)            //最多的窗口个数,UI自定义支持4个图片窗口,4个文字窗口,1个预览窗口,1个时钟窗口,1个呼叫按钮窗口,1个开门按钮窗口,1个二维码窗口,1个认证成功窗口,1个认证失败窗口,1个状态栏窗口

#define PAGE_LIST_NO (1)
#define PLAY_SPAN_LIST_NO (2)
#define MATERIAL_NAME_LEN (32)

typedef enum _PUBLISH_PROGRAM_TYPE_E
{
    PUBLISH_PROGRAM_TYPE_NORMAL = 0,      /*DEF*/
    PUBLISH_PROGRAM_TYPE_SCREENSAVER = 1, //屏保
    PUBLISH_PROGRAM_TYPE_CHARACTER = 2,   //欢迎词
    PUBLISH_PROGRAM_TYPE_UI_DIY = 3,      //UI主界面自定义
    PUBLISH_PROGRAM_TYPE_IDLESCREEN = 4,  //待机画面
    PUBLISH_PROGRAM_TYPE_MAX = PUBLISH_PROGRAM_TYPE_IDLESCREEN
} PUBLISH_PROGRAM_TYPE_E;

/* 子窗口类型（认证窗口使用） */
typedef enum _PUBLISH_SUBWIN_TYPE_E
{
    PUBLISH_SUBWIN_TYPE_DEF = 0,                       /*DEF*/
    PUBLISH_SUBWIN_TYPE_TEMPERATURE = 1,               //温度
    PUBLISH_SUBWIN_TYPE_FACEPIC = 2,                   //人脸图片
    PUBLISH_SUBWIN_TYPE_NAME = 3,                      //姓名
    PUBLISH_SUBWIN_TYPE_EMPLOYEENO = 4,                //工号
    PUBLISH_SUBWIN_TYPE_GROUP = 5,                     //组织/部门
    PUBLISH_SUBWIN_TYPE_TIPS = 6,                      //提示信息
    PUBLISH_SUBWIN_TYPE_MAX = PUBLISH_SUBWIN_TYPE_TIPS //子窗口列表最大个数（认证窗口使用）
} PUBLISH_SUBWIN_TYPE_E;

/* 状态栏子状态类型（状态栏使用） */
typedef enum _PUBLISH_SUBSTATUS_TYPE_E
{
    PUBLISH_SUBSTATUS_TYPE_DEF = 0,                            /*DEF*/
    PUBLISH_SUBSTATUS_TYPE_DIAL = 1,                           //拨号状态（3G4G等）
    PUBLISH_SUBSTATUS_TYPE_WIFI = 2,                           //WIFI状态
    PUBLISH_SUBSTATUS_TYPE_EZVIZ = 3,                          //萤石状态
    PUBLISH_SUBSTATUS_TYPE_WIREDNETWORK = 4,                   //有线网络状态
    PUBLISH_SUBSTATUS_TYPE_DEPLOY = 5,                         //布防状态
    PUBLISH_SUBSTATUS_TYPE_TEMPERATURE = 6,                    //测温状态
    PUBLISH_SUBSTATUS_TYPE_MAX = PUBLISH_SUBSTATUS_TYPE_TEMPERATURE //状态栏子状态最大个数（状态栏使用）
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
    HPR_UINT32 duration; //素材本身播放时长，当素材为视频时有效
} PLAY_DURATION;

typedef struct _CHARACTERS_EFFECT
{
    HPR_UINT32 fontSize;       //字体大小
    HPR_UINT32 fontColor;      //字体颜色
    HPR_UINT32 backColor;      //背景颜色
    HPR_UINT8 scrollDirection; //文字滚动方向 left,right,up,down
    HPR_UINT8 byRes[3];
    HPR_UINT32 backTransparent; //背景透明度
    HPR_UINT32 scrollSpeed;     //文字滚动速度
    HPR_UINT32 backgroundPic;   //背景图，为图片素材的ID
} CHARACTERS_EFFECT;

typedef struct _PLAY_ITEM
{
    HPR_UINT32 itemId;         //播放序号
    HPR_UINT32 itemMaterialNo; //素材索引号
    PLAY_DURATION playDuration;
    CHARACTERS_EFFECT charaEffect;
    HPR_UINT32 scaleType; //素材缩放类型 MATERIAL_SCALE_TYPE_E
} PLAY_ITEM;

typedef struct CHARACTERS_ATTRIBUTE
{
    HPR_UINT32 dwFontSize;                  // 字体大小
    HPR_UINT32 dwFontColor;                 // 字体颜色
    HPR_UINT32 dwBackgroundType;            // 背景类型：颜色、图片 MATERIAL_BACKGROUND_TYPE_E
    HPR_UINT32 dwBackColor;                 // 背景颜色
    HPR_UINT32 dwBackTransparent;           // 背景透明度
    HPR_UINT32 dwAlignType;                 // 对齐方式：左对齐、右对齐、中间对齐
    HPR_UINT32 dwVerticaAlignType;          // 垂直对齐方式
    HPR_UINT8 abyCharacterContent[128 + 1]; // 文字内容，最大128字节
    HPR_UINT8 byFillEnabled;                // 背景色填充使能
    HPR_UINT8 byRes[2];                    // 保留字节
    HPR_UINT32 dwBackPicId;                 // 文字背景图为图片素材的ID
    HPR_UINT32 dwCharacterStyle;            // 字体效果：普通、加粗
} CHARACTERS_ATTRIBUTE;



typedef struct _WINDOWS_INFO
{
    HPR_UINT8 byWinId;
    HPR_UINT8 byLayerNo;             // 窗口层级
    HPR_UINT8 byEnabled;             // 使能（是否隐藏）
    HPR_UINT8 byRes[1];
    POSITION_INFO stWinPosition;     // 窗口所在位置
    WIN_MATERIAL_INFO stWinMaterial; // 窗口类型
    union myUnion
    {
        PLAY_ITEM playItemList[MATERIAL_PICWIN_LIST_NO]; // 播放
        CHARACTERS_ATTRIBUTE stCharaAttribute;           // 文字欢迎词广告
    } myUnion;
} WINDOWS_INFO;

typedef struct _PAGE_INFO
{
    /* 3904 bytes */
    HPR_UINT32 dwPageId;                         // 页面ID
    HPR_UINT8 byPlayDurationMode;                // 页面播放时间模式，分自定义和自动，自定义时，playDuration节点有效
    HPR_UINT8 byPlayDuration;                    // 播放时间，单位：秒
    HPR_UINT8 bySwitchDuration;                  // 切换时间，单位：秒
    HPR_UINT8 bySwitchEffect;                    // 切换效果，分为无，随机，盒状收缩，盒状展开，向上擦除，向下擦除等
    HPR_UINT32 dwBackgroundColor;                // 背景色
    HPR_UINT8 byBackgroundPic;                   // 背景图，为图片素材的ID
    HPR_UINT8 byCharacterMode;                   // 当前页面的文字模式:模式1、模式2、模式3
    HPR_UINT8 byRes2[2];
    WINDOWS_INFO winList[WIN_LIST_NO];           // Page下窗口个数,按最大来,自定义是窗口最多
} PAGE_INFO;

/* 节目 */
typedef struct PROGRAM_INFO
{
    /* 4092 bytes */
    HPR_UINT32 dwProgramId; //节目ID
    HPR_UINT32 dwtest; 
    HPR_UINT8 byProgramName[MATERIAL_NAME_LEN + 1];
    HPR_UINT8 byProgramType; //节目类型 PUBLISH_PROGRAM_TYPE_E
    HPR_UINT8 bySharePpe;    //共享属性，分公有和私有 MATERIAL_SHARE_PROPERTY_E
    HPR_UINT8 byMaterialDurationFlag;                  // 0-默认使用page的switchDuration，1-使用playItem的duration
    RESOLUTION_INFO_T stProResolutionInfo;
    PAGE_INFO pageList[PAGE_LIST_NO];
} PROGRAM_INFO;

typedef union uWinInfo
{
    PLAY_ITEM playItemList[MATERIAL_PICWIN_LIST_NO]; // 播放
    CHARACTERS_ATTRIBUTE stCharaAttribute;           // 文字欢迎词广告
} uWinInfo;

typedef struct DEVICECONFIG
{
    PROGRAM_INFO stProgramParam[2];
    // uWinInfo myUnion;
} DEVICECONFIG;