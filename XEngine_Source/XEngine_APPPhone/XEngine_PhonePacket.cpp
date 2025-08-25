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
函数名称：XEngine_PhonePacket_Header
函数功能：封装电话号码头
 参数.一：ptszMSGBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出封装的缓冲区
 参数.二：pInt_MSGLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出缓冲区大小
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CXEngine_PhonePacket::XEngine_PhonePacket_Header(XCHAR* ptszMSGBuffer, int* pInt_MSGLen)
{
	*pInt_MSGLen = 0;
	XCHAR tszYMDTime[32] = {};
	XENGINE_LIBTIME st_LibTime = {};
	XENGINE_PROTOCOLHDR st_ProtocolHdr = {};

	BaseLib_Time_GetSysTime(&st_LibTime);
	_xsntprintf(tszYMDTime, 32, _X("%04d%02d%02d"), st_LibTime.wYear, st_LibTime.wMonth, st_LibTime.wDay);

	st_ProtocolHdr.wHeader = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_HEADER;
	st_ProtocolHdr.byVersion = ENUM_XENGINE_PROTOCOLHDR_PAYLOAD_TYPE_STRING;
	st_ProtocolHdr.unOperatorType = XENGINE_COMMUNICATION_PROTOCOL_TYPE_PHONE;
	st_ProtocolHdr.unOperatorCode = XENGINE_COMMUNICATION_PROTOCOL_CODE_PHONE_HDR;
	st_ProtocolHdr.unPacketSize = _tcsxlen(tszYMDTime);
	st_ProtocolHdr.wCrypto = 0;
	st_ProtocolHdr.wTail = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_TAIL;

	memcpy(ptszMSGBuffer, &st_ProtocolHdr, sizeof(XENGINE_PROTOCOLHDR));
	*pInt_MSGLen += sizeof(XENGINE_PROTOCOLHDR);
	memcpy(ptszMSGBuffer + *pInt_MSGLen, tszYMDTime, st_ProtocolHdr.unPacketSize);
	*pInt_MSGLen += st_ProtocolHdr.unPacketSize;

	return true;
}
/********************************************************************
函数名称：XEngine_PhonePacket_ISPInfo
函数功能：封装运营商信息数据
 参数.一：ptszMSGBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出封装的缓冲区
 参数.二：pInt_MSGLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出缓冲区大小
 参数.三：lpszISPBuffer
  In/Out：Out
  类型：常量字符指针
  可空：N
  意思：输入要封装的ISP数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
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
	st_ProtocolHdr.wPacketSerial = (XSHOT)nISPCount;
	st_ProtocolHdr.wCrypto = 0;
	st_ProtocolHdr.wTail = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_TAIL;

	memcpy(ptszMSGBuffer, &st_ProtocolHdr, sizeof(XENGINE_PROTOCOLHDR));
	*pInt_MSGLen += sizeof(XENGINE_PROTOCOLHDR);
	memcpy(ptszMSGBuffer + *pInt_MSGLen, lpszISPBuffer, st_ProtocolHdr.unPacketSize);
	*pInt_MSGLen += st_ProtocolHdr.unPacketSize;

	return true;
}
/********************************************************************
函数名称：XEngine_PhonePacket_LocationInfo
函数功能：封装位置信息数据
 参数.一：ptszMSGBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出封装的缓冲区
 参数.二：pInt_MSGLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出缓冲区大小
 参数.三：lpszLocationBuffer
  In/Out：Out
  类型：常量字符指针
  可空：N
  意思：输入要封装的位置数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CXEngine_PhonePacket::XEngine_PhonePacket_LocationInfo(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, LPCXSTR lpszLocationBuffer)
{
	*pInt_MSGLen = 0;
	XENGINE_PROTOCOLHDR st_ProtocolHdr = {};

	XEngine_PhonePacket_LocationList(lpszLocationBuffer);

	st_ProtocolHdr.wHeader = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_HEADER;
	st_ProtocolHdr.byVersion = ENUM_XENGINE_PROTOCOLHDR_PAYLOAD_TYPE_STRING;
	st_ProtocolHdr.unOperatorType = XENGINE_COMMUNICATION_PROTOCOL_TYPE_PHONE;
	st_ProtocolHdr.unOperatorCode = XENGINE_COMMUNICATION_PROTOCOL_CODE_PHONE_LOCATION;
	st_ProtocolHdr.unPacketSize = _tcsxlen(lpszLocationBuffer);
	st_ProtocolHdr.wPacketSerial = (XSHOT)nLocalCount;
	st_ProtocolHdr.wCrypto = 0;
	st_ProtocolHdr.wTail = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_TAIL;

	memcpy(ptszMSGBuffer, &st_ProtocolHdr, sizeof(XENGINE_PROTOCOLHDR));
	*pInt_MSGLen += sizeof(XENGINE_PROTOCOLHDR);
	memcpy(ptszMSGBuffer + *pInt_MSGLen, lpszLocationBuffer, st_ProtocolHdr.unPacketSize);
	*pInt_MSGLen += st_ProtocolHdr.unPacketSize;
	return true;
}
//////////////////////////////////////////////////////////////////////////
//                          保护文件
//////////////////////////////////////////////////////////////////////////
bool CXEngine_PhonePacket::XEngine_PhonePacket_ISPList(LPCXSTR lpszISPBuffer)
{
	XCHAR tszISPBuffer[4096] = {};
	_tcsxcpy(tszISPBuffer, lpszISPBuffer);

	XCHAR* ptszTokTmp = NULL;
	XCHAR* ptszTokStr = _tcsxtok_s(tszISPBuffer, _X(" "), &ptszTokTmp);
	while (NULL != ptszTokStr)
	{
		nISPCount++;
		ptszTokStr = _tcsxtok_s(NULL, _X(" "), &ptszTokTmp);
	}
	return true;
}
bool CXEngine_PhonePacket::XEngine_PhonePacket_LocationList(LPCXSTR lpszLocationBuffer)
{
	XCHAR tszLocationBuffer[10240] = {};
	_tcsxcpy(tszLocationBuffer, lpszLocationBuffer);

	XCHAR* ptszTokTmp = NULL;
	XCHAR* ptszTokStr = _tcsxtok_s(tszLocationBuffer, _X(" "), &ptszTokTmp);
	while (NULL != ptszTokStr)
	{
		nLocalCount++;
		ptszTokStr = _tcsxtok_s(NULL, _X(" "), &ptszTokTmp);
	}
	return true;
}