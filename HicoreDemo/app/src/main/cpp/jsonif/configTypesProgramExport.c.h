static JSIF_CFG_T stJson_RESOLUTION_INFO[] =
{
    {"byResolutionName",         1,         JMNOR(JSTM(struct _RESOLUTION_INFO, byResolutionName))},
    {"dwImageWidth",         1,         JMNOR(JSTM(struct _RESOLUTION_INFO, dwImageWidth))},
    {"dwImageHeight",         1,         JMNOR(JSTM(struct _RESOLUTION_INFO, dwImageHeight))},
};

static JSIF_CFG_T stJson_POSITION_INFO[] =
{
    {"positionX",         1,         JMNOR(JSTM(struct _POSITION_INFO, positionX))},
    {"positionY",         1,         JMNOR(JSTM(struct _POSITION_INFO, positionY))},
    {"height",         1,         JMNOR(JSTM(struct _POSITION_INFO, height))},
    {"width",         1,         JMNOR(JSTM(struct _POSITION_INFO, width))},
};

static JSIF_CFG_T stJson_WIN_MATERIAL_INFO[] =
{
    {"materialType",         1,         JMNOR(JSTM(struct _WIN_MATERIAL_INFO, materialType))},
    {"staticMaterialType",         1,         JMNOR(JSTM(struct _WIN_MATERIAL_INFO, staticMaterialType))},
    {"dynamicMaterialType",         1,         JMNOR(JSTM(struct _WIN_MATERIAL_INFO, dynamicMaterialType))},
    {"otherMaterialType",         1,         JMNOR(JSTM(struct _WIN_MATERIAL_INFO, otherMaterialType))},
    {"res",         1,         JMARR(JSTM(struct _WIN_MATERIAL_INFO, res))},
    {"",         2,         JMNOR(JSTM(struct _WIN_MATERIAL_INFO, res[0]))},
};

static JSIF_CFG_T stJsonCHARACTERS_ATTRIBUTE[] =
{
    {"dwFontSize",         1,         JMNOR(JSTM(struct CHARACTERS_ATTRIBUTE, dwFontSize))},
    {"dwFontColor",         1,         JMNOR(JSTM(struct CHARACTERS_ATTRIBUTE, dwFontColor))},
    {"dwBackgroundType",         1,         JMNOR(JSTM(struct CHARACTERS_ATTRIBUTE, dwBackgroundType))},
    {"dwBackColor",         1,         JMNOR(JSTM(struct CHARACTERS_ATTRIBUTE, dwBackColor))},
    {"dwBackTransparent",         1,         JMNOR(JSTM(struct CHARACTERS_ATTRIBUTE, dwBackTransparent))},
    {"dwAlignType",         1,         JMNOR(JSTM(struct CHARACTERS_ATTRIBUTE, dwAlignType))},
    {"dwVerticaAlignType",         1,         JMNOR(JSTM(struct CHARACTERS_ATTRIBUTE, dwVerticaAlignType))},
    {"abyCharacterContent",         1,         JMARR(JSTM(struct CHARACTERS_ATTRIBUTE, abyCharacterContent))},
    {"",         2,         JMNOR(JSTM(struct CHARACTERS_ATTRIBUTE, abyCharacterContent[0]))},
    {"byFillEnabled",         1,         JMNOR(JSTM(struct CHARACTERS_ATTRIBUTE, byFillEnabled))},
    {"dwBackPicId",         1,         JMNOR(JSTM(struct CHARACTERS_ATTRIBUTE, dwBackPicId))},
    {"dwCharacterStyle",         1,         JMNOR(JSTM(struct CHARACTERS_ATTRIBUTE, dwCharacterStyle))},
};

static JSIF_CFG_T stJsonmyUnion[] =
{
    {"stCharaAttribute",         1,         JMCFG(stJsonCHARACTERS_ATTRIBUTE, JSTM(union myUnion, stCharaAttribute))},
};

static JSIF_CFG_T stJson_WINDOWS_INFO[] =
{
    {"byWinId",         1,         JMNOR(JSTM(struct _WINDOWS_INFO, byWinId))},
    {"byLayerNo",         1,         JMNOR(JSTM(struct _WINDOWS_INFO, byLayerNo))},
    {"byEnabled",         1,         JMNOR(JSTM(struct _WINDOWS_INFO, byEnabled))},
    {"stWinPosition",         1,         JMCFG(stJson_POSITION_INFO, JSTM(struct _WINDOWS_INFO, stWinPosition))},
    {"stWinMaterial",         1,         JMCFG(stJson_WIN_MATERIAL_INFO, JSTM(struct _WINDOWS_INFO, stWinMaterial))},
    {"myUnion",         1,         JMCFG(stJsonmyUnion, JSTM(struct _WINDOWS_INFO, myUnion))},
};

static JSIF_CFG_T stJson_PAGE_INFO[] =
{
    {"dwPageId",         1,         JMNOR(JSTM(struct _PAGE_INFO, dwPageId))},
    {"byPlayDurationMode",         1,         JMNOR(JSTM(struct _PAGE_INFO, byPlayDurationMode))},
    {"byPlayDuration",         1,         JMNOR(JSTM(struct _PAGE_INFO, byPlayDuration))},
    {"bySwitchDuration",         1,         JMNOR(JSTM(struct _PAGE_INFO, bySwitchDuration))},
    {"bySwitchEffect",         1,         JMNOR(JSTM(struct _PAGE_INFO, bySwitchEffect))},
    {"dwBackgroundColor",         1,         JMNOR(JSTM(struct _PAGE_INFO, dwBackgroundColor))},
    {"byBackgroundPic",         1,         JMNOR(JSTM(struct _PAGE_INFO, byBackgroundPic))},
    {"byCharacterMode",         1,         JMNOR(JSTM(struct _PAGE_INFO, byCharacterMode))},
    {"winList",         1,         JMARR(JSTM(struct _PAGE_INFO, winList))},
    {"",         2,         JMCFG(stJson_WINDOWS_INFO, JSTM(struct _PAGE_INFO, winList[0]))},
};

static JSIF_CFG_T stJsonPROGRAM_INFO[] =
{
    {"dwProgramId",         1,         JMNOR(JSTM(struct PROGRAM_INFO, dwProgramId))},
    {"dwtest",         1,         JMNOR(JSTM(struct PROGRAM_INFO, dwtest))},
    {"byProgramName",         1,         JMARR(JSTM(struct PROGRAM_INFO, byProgramName))},
    {"",         2,         JMNOR(JSTM(struct PROGRAM_INFO, byProgramName[0]))},
    {"byProgramType",         1,         JMNOR(JSTM(struct PROGRAM_INFO, byProgramType))},
    {"bySharePpe",         1,         JMNOR(JSTM(struct PROGRAM_INFO, bySharePpe))},
    {"byMaterialDurationFlag",         1,         JMNOR(JSTM(struct PROGRAM_INFO, byMaterialDurationFlag))},
    {"stProResolutionInfo",         1,         JMCFG(stJson_RESOLUTION_INFO, JSTM(struct PROGRAM_INFO, stProResolutionInfo))},
    {"pageList",         1,         JMARR(JSTM(struct PROGRAM_INFO, pageList))},
    {"",         2,         JMCFG(stJson_PAGE_INFO, JSTM(struct PROGRAM_INFO, pageList[0]))},
};

static JSIF_CFG_T stJsonDEVICECONFIG[] =
{
    {"stProgramParam",         1,         JMARR(JSTM(struct DEVICECONFIG, stProgramParam))},
    {"",         2,         JMCFG(stJsonPROGRAM_INFO, JSTM(struct DEVICECONFIG, stProgramParam[0]))},
};

