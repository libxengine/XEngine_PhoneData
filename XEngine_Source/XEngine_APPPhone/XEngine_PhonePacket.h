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
	XCHAR tszISPName[XPATH_MIN];
	int nIndex;
}PHONENUMBER_ISPINFO;
typedef struct
{
	int nArea;
	XCHAR tszProvinceStr[64];
	XCHAR tszCityStr[64];
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
	bool XEngine_PhonePacket_Header(XCHAR* ptszMSGBuffer, int* pInt_MSGLen);
	bool XEngine_PhonePacket_ISPInfo(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, LPCXSTR lpszISPBuffer);
	bool XEngine_PhonePacket_LocationInfo(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, LPCXSTR lpszLocationBuffer);
	bool XEngine_PhonePacket_PHoneInfo(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, int nCount);
protected:
	bool XEngine_PhonePacket_ISPList(LPCXSTR lpszISPBuffer);
	bool XEngine_PhonePacket_LocationList(LPCXSTR lpszLocationBuffer);
private:
	std::unordered_map<int, PHONENUMBER_ISPINFO> stl_MapISPInfo; // 运营商信息
	std::unordered_map<int, XENGINE_LOCATION> stl_MapLocationInfo;
};