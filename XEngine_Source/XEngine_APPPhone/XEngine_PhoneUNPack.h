#pragma once
/********************************************************************
//    Created:     2025/08/22  13:47:02
//    File Name:   D:\XEngine_PhoneData\XEngine_Source\XEngine_APPPhone\XEngine_PhoneUNPack.h
//    File Path:   D:\XEngine_PhoneData\XEngine_Source\XEngine_APPPhone
//    File Base:   XEngine_PhoneUNPack
//    File Ext:    h
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     数据解封装还原
//    History:
*********************************************************************/
typedef struct
{
	XCHAR tszPhoneStr[64];
	XCHAR tszPhoneType[64];
	XCHAR tszProvinceStr[64];
	XCHAR tszCityStr[64];
	XCHAR tszAreaStr[64];
	XCHAR tszTransferStr[64];
}XENGINE_PHONEINTERNAL;

class CXEngine_PhoneUNPack
{
public:
	CXEngine_PhoneUNPack();
	~CXEngine_PhoneUNPack();
public:
protected:
private:
};