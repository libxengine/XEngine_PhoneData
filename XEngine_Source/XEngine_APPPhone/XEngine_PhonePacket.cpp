#include "XEngine_PhoneHdr.h"
/********************************************************************
//    Created:     2025/08/22  13:44:26
//    File Name:   D:\XEngine_PhoneData\XEngine_Source\XEngine_APPPhone\XEngine_PhonePacket.cpp
//    File Path:   D:\XEngine_PhoneData\XEngine_Source\XEngine_APPPhone
//    File Base:   XEngine_PhonePacket
//    File Ext:    cpp
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     数据打包类实现
//    History:
*********************************************************************/
CXEngine_PhonePacket::CXEngine_PhonePacket()
{

}
CXEngine_PhonePacket::~CXEngine_PhonePacket()
{

}
//////////////////////////////////////////////////////////////////////////
//                          公用头文件
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：XEngine_PhonePacket_Location
函数功能：封包位置信息
 参数.一：ptszMSGBuffer
  In/Out：
  类型：
  可空：
  意思：
 参数.二：
  In/Out：
  类型：
  可空：
  意思：
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CXEngine_PhonePacket::XEngine_PhonePacket_Location(XCHAR * ptszMSGBuffer, std::list<XENGINE_LOCATION>* pStl_ListLocation)
{
    int nPos = 0;
	char* ptszTokStr = ptszMSGBuffer;
	// 遍历数组，直到指针指向 \0
	while (*ptszTokStr != '\0')
	{
		XCHAR tszLocationStr[XPATH_MAX] = {};
		XENGINE_LOCATION st_Location = {};

		st_Location.nPos = nPos;
		int nRet = _stxscanf(ptszTokStr, _X("%[^|]|%[^|]|%[^|]|%s"), st_Location.tszProvinceStr, st_Location.tszCityStr, st_Location.tszCodeStr, st_Location.tszAreaStr);
		if (nRet != 4)
		{
			break;
		}
		nRet = _xstprintf(tszLocationStr, _X("%s-%s-%s "), st_Location.tszAreaStr, st_Location.tszProvinceStr, st_Location.tszCityStr);

		nPos += nRet;
		pStl_ListLocation->push_back(st_Location);

        ptszTokStr += strlen(ptszTokStr) + 1;     // 移动指针到下一个子字符串的开始
	}
    return true;
}
/********************************************************************
函数名称：XEngine_PhonePacket_Phone
函数功能：写电话索引信息
 参数.一：
  In/Out：
  类型：
  可空：
  意思：
 参数.二：
  In/Out：
  类型：
  可空：
  意思：
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CXEngine_PhonePacket::XEngine_PhonePacket_Phone(LPCXSTR lpszMSGBuffer, std::list<XENGINE_LOCATION>* pStl_ListLocation)
{
	XCHAR tszPhoneStr[XPATH_MAX] = {};
	XENGINE_PHONEINTERNAL st_PhoneInfo = {};

	int nRet = _stxscanf(lpszMSGBuffer, _X("%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s"), st_PhoneInfo.tszSerialStr, st_PhoneInfo.tszPhoneStr, st_PhoneInfo.tszPhoneType, st_PhoneInfo.tszProvinceStr, st_PhoneInfo.tszCityStr, st_PhoneInfo.tszAreaStr, st_PhoneInfo.tszTransferStr);
	if (nRet != 7)
	{
		return false;
	}

    bool bFound = false;
    auto stl_ListIterator = pStl_ListLocation->begin();
    for (; stl_ListIterator != pStl_ListLocation->end(); stl_ListIterator++)
    {
        if ((0 == _tcsxnicmp(stl_ListIterator->tszProvinceStr, st_PhoneInfo.tszProvinceStr, _tcsxlen(st_PhoneInfo.tszProvinceStr))) && (0 == _tcsxnicmp(stl_ListIterator->tszCityStr, st_PhoneInfo.tszCityStr,  _tcsxlen(st_PhoneInfo.tszCityStr))))
        {
            bFound = true;
            break;
        }
    }
	if (!bFound)
	{
        printf("没有找到位置信息\n");
        return false;
	}

    int nType = _ttxoi(st_PhoneInfo.tszPhoneType);

    if (4 == nType)
    {
        nType = 10;
    }
    else if (5 == nType)
    {
        nType = 11;
    }
	else if (6 == nType)
	{
		nType = 12;
	}
    else if (7 == nType)
    {
        nType = 4;
    }
	nRet = _xstprintf(tszPhoneStr, _X("%s-%s-%d-%d-0\n"), st_PhoneInfo.tszPhoneStr, st_PhoneInfo.tszAreaStr, nType, stl_ListIterator->nPos);
	//fwrite(tszPhoneStr, 1, nRet, pSt_WFile);
	//nPos += nRet;

	return true;
}