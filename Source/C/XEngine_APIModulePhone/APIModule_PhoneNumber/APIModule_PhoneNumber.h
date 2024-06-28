#pragma once
/********************************************************************
//    Created:     2024/06/28  14:09:51
//    File Name:   D:\phonedata\Source\C\XEngine_APIModulePhone\APIModule_PhoneNumber\APIModule_PhoneNumber.h
//    File Path:   D:\phonedata\Source\C\XEngine_APIModulePhone\APIModule_PhoneNumber
//    File Base:   APIModule_PhoneNumber
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     电话查询接口
//    History:
*********************************************************************/

class CAPIModule_PhoneNumber
{
public:
	CAPIModule_PhoneNumber();
	~CAPIModule_PhoneNumber();
public:
	bool APIModule_PhoneNumber_Init(LPCXSTR lpszDBFile);
	void APIModule_PhoneNumber_UnInit();
	bool APIModule_PhoneNumber_Query(XENGINE_PHONEINFO* pSt_PhoneInfo);
protected:
	bool APIModule_PhoneNumber_Check(LPCXSTR lpszMSGBuffer);
	std::string APIModule_PhoneNumber_7Digits(LPCXSTR lpszMSGBuffer);
private:
	size_t nPos = 0;
	size_t nFSize = 0;
	XCHAR* ptszMSGBuffer = NULL;
	XCHAR* ptszPhoneIndex = NULL;

	XENGINE_PROTOCOLHDR st_ProtocolHdr = {};
	XENGINE_PROTOCOLHDR st_ProtocolMap = {};
	XENGINE_PROTOCOLHDR st_ProtocolRecord = {};
	XENGINE_PROTOCOLHDR st_ProtocolIndex = {};
private:
	std::unordered_map<int, std::string> stl_MapISPName;
};
