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
bool CXEngine_PhonePacket::XEngine_PhonePacket_Header(XCHAR* ptszMSGBuffer, int* pInt_MSGLen)
{
	*pInt_MSGLen = 0;
	XCHAR tszYMDTime[32] = {};
	XENGINE_PROTOCOLHDR st_ProtocolHdr = {};

	BaseLib_Time_TimeToStr(tszYMDTime, NULL, false);
	int nHLen = _tcsxlen(tszYMDTime);

	st_ProtocolHdr.wHeader = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_HEADER;
	st_ProtocolHdr.byVersion = ENUM_XENGINE_PROTOCOLHDR_PAYLOAD_TYPE_STRING;
	st_ProtocolHdr.unOperatorType = XENGINE_COMMUNICATION_PROTOCOL_TYPE_PHONE;
	st_ProtocolHdr.unOperatorCode = XENGINE_COMMUNICATION_PROTOCOL_CODE_PHONE_HDR;
	st_ProtocolHdr.unPacketSize = nHLen;
	st_ProtocolHdr.wCrypto = 0;
	st_ProtocolHdr.wTail = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_TAIL;

	memcpy(ptszMSGBuffer, &st_ProtocolHdr, sizeof(XENGINE_PROTOCOLHDR));
	*pInt_MSGLen += sizeof(XENGINE_PROTOCOLHDR);
	*pInt_MSGLen += nHLen;

	return true;
}
bool CXEngine_PhonePacket::XEngine_PhonePacket_ISPInfo(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, LPCXSTR lpszISPBuffer)
{
	XEngine_PhonePacket_ISPList(lpszISPBuffer);

	*pInt_MSGLen = 0;
	XENGINE_PROTOCOLHDR st_ProtocolHdr = {};

	st_ProtocolHdr.wHeader = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_HEADER;
	st_ProtocolHdr.byVersion = ENUM_XENGINE_PROTOCOLHDR_PAYLOAD_TYPE_STRING;
	st_ProtocolHdr.unOperatorType = XENGINE_COMMUNICATION_PROTOCOL_TYPE_PHONE;
	st_ProtocolHdr.unOperatorCode = XENGINE_COMMUNICATION_PROTOCOL_CODE_PHONE_ISP;
	st_ProtocolHdr.unPacketSize = _tcsxlen(lpszISPBuffer);
	st_ProtocolHdr.wPacketSerial = (XSHOT)stl_MapISPInfo.size();
	st_ProtocolHdr.wCrypto = 0;
	st_ProtocolHdr.wTail = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_TAIL;

	memcpy(ptszMSGBuffer, &st_ProtocolHdr, sizeof(XENGINE_PROTOCOLHDR));
	*pInt_MSGLen += sizeof(XENGINE_PROTOCOLHDR);
	memcpy(ptszMSGBuffer + *pInt_MSGLen, lpszISPBuffer, st_ProtocolHdr.unPacketSize);
	*pInt_MSGLen += st_ProtocolHdr.unPacketSize;

	return true;
}
bool CXEngine_PhonePacket::XEngine_PhonePacket_LocationInfo(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, LPCXSTR lpszLocationBuffer)
{
	*pInt_MSGLen = 0;
	XENGINE_PROTOCOLHDR st_ProtocolHdr = {};

	st_ProtocolHdr.wHeader = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_HEADER;
	st_ProtocolHdr.byVersion = ENUM_XENGINE_PROTOCOLHDR_PAYLOAD_TYPE_STRING;
	st_ProtocolHdr.unOperatorType = XENGINE_COMMUNICATION_PROTOCOL_TYPE_PHONE;
	st_ProtocolHdr.unOperatorCode = XENGINE_COMMUNICATION_PROTOCOL_CODE_PHONE_LOCATION;
	st_ProtocolHdr.unPacketSize = _tcsxlen(lpszLocationBuffer);
	st_ProtocolHdr.wPacketSerial = 13;
	st_ProtocolHdr.wCrypto = 0;
	st_ProtocolHdr.wTail = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_TAIL;

	memcpy(ptszMSGBuffer, &st_ProtocolHdr, sizeof(XENGINE_PROTOCOLHDR));
	*pInt_MSGLen += sizeof(XENGINE_PROTOCOLHDR);
	memcpy(ptszMSGBuffer + *pInt_MSGLen, lpszLocationBuffer, st_ProtocolHdr.unPacketSize);
	*pInt_MSGLen += st_ProtocolHdr.unPacketSize;
	return true;
}
bool CXEngine_PhonePacket::XEngine_PhonePacket_PHoneInfo(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, int nCount)
{
	*pInt_MSGLen = 0;
	XENGINE_PROTOCOLHDR st_ProtocolHdr = {};

	st_ProtocolHdr.wHeader = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_HEADER;
	st_ProtocolHdr.byVersion = ENUM_XENGINE_PROTOCOLHDR_PAYLOAD_TYPE_STRING;
	st_ProtocolHdr.unOperatorType = XENGINE_COMMUNICATION_PROTOCOL_TYPE_PHONE;
	st_ProtocolHdr.unOperatorCode = XENGINE_COMMUNICATION_PROTOCOL_CODE_PHONE_INDEX;
	st_ProtocolHdr.unPacketSize = nCount;
	st_ProtocolHdr.wPacketSerial = 0;
	st_ProtocolHdr.wCrypto = 0;
	st_ProtocolHdr.wTail = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_TAIL;

	memcpy(ptszMSGBuffer, &st_ProtocolHdr, sizeof(XENGINE_PROTOCOLHDR));
	*pInt_MSGLen += sizeof(XENGINE_PROTOCOLHDR);
	return true;
}
bool CXEngine_PhonePacket::XEngine_PhonePacket_ISPList(LPCXSTR lpszISPBuffer)
{
	XCHAR tszISPBuffer[4096] = {};
	_tcsxcpy(tszISPBuffer, lpszISPBuffer);

	XCHAR* ptszTokTmp = NULL;
	XCHAR* ptszTokStr = _tcsxtok_s(tszISPBuffer, _X(" "), &ptszTokTmp);
	while (NULL != ptszTokStr)
	{
		PHONENUMBER_ISPINFO st_ISPInfo = {};
		int nRet = _stxscanf(ptszTokStr, _X("%d-%s"), &st_ISPInfo.nIndex, st_ISPInfo.tszISPName);
		if (nRet != 2)
		{
			break;
		}
		stl_MapISPInfo.insert(std::make_pair(st_ISPInfo.nIndex, st_ISPInfo));
		ptszTokStr = _tcsxtok_s(NULL, _X(" "), &ptszTokTmp);
	}
	return true;
}
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
bool CXEngine_PhonePacket::XEngine_PhonePacket_LocationList(LPCXSTR lpszLocationBuffer)
{
	XCHAR tszLocationBuffer[4096] = {};
	_tcsxcpy(tszLocationBuffer, lpszLocationBuffer);

	XCHAR* ptszTokTmp = NULL;
	XCHAR* ptszTokStr = _tcsxtok_s(tszLocationBuffer, _X(" "), &ptszTokTmp);
	while (NULL != ptszTokStr)
	{
		XENGINE_LOCATION st_Location = {};
		int nRet = _stxscanf(ptszTokStr, _X("%d-%[^-]-%s"), &st_Location.nArea, st_Location.tszProvinceStr, st_Location.tszCityStr);
		if (nRet != 3)
		{
			break;
		}
		stl_MapLocationInfo.insert(std::make_pair(st_Location.nArea, st_Location));
		ptszTokStr = _tcsxtok_s(NULL, _X(" "), &ptszTokTmp);
	}
	return true;
}