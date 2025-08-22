#pragma once
/********************************************************************
//    Created:     2025/08/22  13:43:08
//    File Name:   D:\XEngine_PhoneData\XEngine_Source\XEngine_APPPhone\XEngine_PhonePacket.h
//    File Path:   D:\XEngine_PhoneData\XEngine_Source\XEngine_APPPhone
//    File Base:   XEngine_PhonePacket
//    File Ext:    h
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     数据打包类
//    History:
*********************************************************************/
typedef struct
{
	int nPos;
	XCHAR tszProvinceStr[64];
	XCHAR tszCityStr[64];
	XCHAR tszCodeStr[64];
	XCHAR tszAreaStr[64];
}XENGINE_LOCATION;
typedef struct
{
	XCHAR tszSerialStr[64];
	XCHAR tszPhoneStr[64];
	XCHAR tszPhoneType[64];
	XCHAR tszProvinceStr[64];
	XCHAR tszCityStr[64];
	XCHAR tszAreaStr[64];
	XCHAR tszTransferStr[64];
}XENGINE_PHONEINTERNAL;

class CXEngine_PhonePacket
{
public:
    CXEngine_PhonePacket();
    ~CXEngine_PhonePacket();
public:
    bool XEngine_PhonePacket_Location(XCHAR* ptszMSGBuffer, std::list<XENGINE_LOCATION>* pStl_ListLocation);
    bool XEngine_PhonePacket_Phone(LPCXSTR lpszMSGBuffer, std::list<XENGINE_LOCATION>* pStl_ListLocation);
protected:
private:
};