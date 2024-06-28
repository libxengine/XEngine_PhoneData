#include "pch.h"
#include "APIModule_PhoneNumber.h"
/********************************************************************
//    Created:     2024/06/28  14:10:15
//    File Name:   D:\phonedata\Source\C\XEngine_APIModulePhone\APIModule_PhoneNumber\APIModule_PhoneNumber.cpp
//    File Path:   D:\phonedata\Source\C\XEngine_APIModulePhone\APIModule_PhoneNumber
//    File Base:   APIModule_PhoneNumber
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     电话查询接口
//    History:
*********************************************************************/
CAPIModule_PhoneNumber::CAPIModule_PhoneNumber()
{
}
CAPIModule_PhoneNumber::~CAPIModule_PhoneNumber()
{
}
//////////////////////////////////////////////////////////////////////////
//                       公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：APIModule_PhoneNumber_Init
函数功能：初始化模块
 参数.一：lpszDBFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入数据库路径
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CAPIModule_PhoneNumber::APIModule_PhoneNumber_Init(LPCXSTR lpszDBFile)
{
	APIPhone_IsErrorOccur = false;

	if (NULL == lpszDBFile)
	{
		APIPhone_IsErrorOccur = true;
		APIPhone_dwErrorCode = ERROR_XENGINE_PHONENUMBER_APIMODULE_PARAMENT;
		return false;
	}
	FILE* pSt_File = _xtfopen(lpszDBFile, _X("rb"));
	if (NULL == pSt_File)
	{
		APIPhone_IsErrorOccur = true;
		APIPhone_dwErrorCode = ERROR_XENGINE_PHONENUMBER_APIMODULE_OPENFILE;
		return false;
	}
	ptszMSGBuffer = (XCHAR*)malloc(XENGINE_MEMORY_SIZE_LARGE);
	if (NULL == ptszMSGBuffer)
	{
		APIPhone_IsErrorOccur = true;
		APIPhone_dwErrorCode = ERROR_XENGINE_PHONENUMBER_APIMODULE_MALLOC;
		return false;
	}
	memset(ptszMSGBuffer, '\0', XENGINE_MEMORY_SIZE_LARGE);
	nFSize = fread(ptszMSGBuffer, 1, XENGINE_MEMORY_SIZE_LARGE, pSt_File);
	fclose(pSt_File);

	if (nFSize <= 0)
	{
		APIPhone_IsErrorOccur = true;
		APIPhone_dwErrorCode = ERROR_XENGINE_PHONENUMBER_APIMODULE_READ;
		return false;
	}

	if (!APIModule_PhoneNumber_Check(ptszMSGBuffer))
	{
		return false;
	}
    return true;
}
/********************************************************************
函数名称：APIModule_PhoneNumber_UnInit
函数功能：反初始化
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
void CAPIModule_PhoneNumber::APIModule_PhoneNumber_UnInit()
{
	APIPhone_IsErrorOccur = false;

	if (NULL != ptszMSGBuffer)
	{
		free(ptszMSGBuffer);
		ptszMSGBuffer = NULL;
	}
}
/********************************************************************
函数名称：APIModule_PhoneNumber_Query
函数功能：查询电话号码信息
 参数.一：pSt_PhoneInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要查询的号码,输出查询到的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CAPIModule_PhoneNumber::APIModule_PhoneNumber_Query(XENGINE_PHONEINFO *pSt_PhoneInfo)
{
	APIPhone_IsErrorOccur = false;

	if (NULL == pSt_PhoneInfo)
	{
		APIPhone_IsErrorOccur = true;
		APIPhone_dwErrorCode = ERROR_XENGINE_PHONENUMBER_APIMODULE_PARAMENT;
		return false;
	}
	//查找
	XCHAR* ptszPhoneIndex = (XCHAR*)malloc(XENGINE_MEMORY_SIZE_LARGE);
	if (NULL == ptszPhoneIndex)
	{
		APIPhone_IsErrorOccur = true;
		APIPhone_dwErrorCode = ERROR_XENGINE_PHONENUMBER_APIMODULE_MALLOC;
		return false;
	}
	memset(ptszPhoneIndex, '\0', XENGINE_MEMORY_SIZE_LARGE);
	memcpy(ptszPhoneIndex, ptszMSGBuffer + nPos, nFSize - nPos);

	bool bFound = false;
	XCHAR* ptszTokTmp = NULL;
	XCHAR* ptszTokStr = _tcsxtok_s(ptszPhoneIndex, _X("\n"), &ptszTokTmp);
	while (NULL != ptszTokStr)
	{
		typedef struct
		{
			XCHAR tszPhoneStr[64];
			XCHAR tszAreaStr[64];
			XCHAR tszPhoneType[64];
			XCHAR tszIndexStr[64];
			XCHAR tszTransferStr[64];
		}XENGINE_PHONEINDEX;

		XENGINE_PHONEINDEX st_PhoneIndex = {};
		int nRet = _stxscanf(ptszTokStr, _X("%[^-]-%[^-]-%[^-]-%[^-]-%s"), st_PhoneIndex.tszPhoneStr, st_PhoneIndex.tszAreaStr, st_PhoneIndex.tszPhoneType, st_PhoneIndex.tszIndexStr, st_PhoneIndex.tszTransferStr);
		if (nRet != 5)
		{
			break;
		}

		std::string m_StrPhone = APIModule_PhoneNumber_7Digits(pSt_PhoneInfo->tszPhoneNumber);
		if (0 == _tcsxnicmp(m_StrPhone.c_str(), st_PhoneIndex.tszPhoneStr, m_StrPhone.length()))
		{
			XCHAR tszLocationStr[MAX_PATH] = {};
			memcpy(tszLocationStr, ptszMSGBuffer + _ttxoi(st_PhoneIndex.tszIndexStr), 64);

			XCHAR* ptszSubTmp = NULL;
			XCHAR* ptszSubStr = _tcsxtok_s(tszLocationStr, _X("\n"), &ptszSubTmp);

			int nRet = _stxscanf(ptszSubStr, _X("%[^-]-%[^-]-%s"), pSt_PhoneInfo->tszAreaCode, pSt_PhoneInfo->tszProvincer, pSt_PhoneInfo->tszCity);
			if (3 != nRet)
			{
				break;
			}
			auto stl_MapIterator = stl_MapISPName.find(_ttxoi(st_PhoneIndex.tszPhoneType));
			if (stl_MapIterator != stl_MapISPName.end())
			{
				_tcsxcpy(pSt_PhoneInfo->tszISPName, stl_MapIterator->second.c_str());
			}
			bFound = true;
			break;
		}
		ptszTokStr = _tcsxtok_s(NULL, _X("\n"), &ptszTokTmp);
	}

	free(ptszPhoneIndex);
	ptszPhoneIndex = NULL;

	if (!bFound)
	{
		APIPhone_IsErrorOccur = true;
		APIPhone_dwErrorCode = ERROR_XENGINE_PHONENUMBER_APIMODULE_NOTFOUND;
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
//                       保护函数
//////////////////////////////////////////////////////////////////////////
bool CAPIModule_PhoneNumber::APIModule_PhoneNumber_Check(LPCXSTR lpszMSGBuffer)
{
	APIPhone_IsErrorOccur = false;

	nPos = 0;
	XCHAR tszMSGBuffer[MAX_PATH] = {};
	//得到头分区数据
	memcpy(&st_ProtocolHdr, lpszMSGBuffer, sizeof(XENGINE_PROTOCOLHDR));
	nPos += sizeof(XENGINE_PROTOCOLHDR);
	if (XENGIEN_COMMUNICATION_PACKET_PROTOCOL_HEADER != st_ProtocolHdr.wHeader || XENGIEN_COMMUNICATION_PACKET_PROTOCOL_TAIL != st_ProtocolHdr.wTail || ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_PHONE != st_ProtocolHdr.unOperatorType)
	{
		APIPhone_IsErrorOccur = true;
		APIPhone_dwErrorCode = ERROR_XENGINE_PHONENUMBER_APIMODULE_VER;
		return false;
	}
	memcpy(tszMSGBuffer, lpszMSGBuffer + nPos, st_ProtocolHdr.unPacketSize);
	nPos += st_ProtocolHdr.unPacketSize;
	//得到类型映射
	memcpy(&st_ProtocolMap, lpszMSGBuffer + nPos, sizeof(XENGINE_PROTOCOLHDR));
	nPos += sizeof(XENGINE_PROTOCOLHDR);

	memset(tszMSGBuffer, '\0', sizeof(tszMSGBuffer));
	memcpy(tszMSGBuffer, lpszMSGBuffer + nPos, st_ProtocolMap.unPacketSize);
	nPos += st_ProtocolMap.unPacketSize;

	XCHAR* ptszTokStr = _tcsxtok(tszMSGBuffer, _X(","));
	while (NULL != ptszTokStr)
	{
		XCHAR tszKEYStr[16] = {};
		XCHAR tszVLUStr[16] = {};
		int nRet = _stxscanf(ptszTokStr, _X("%[^-]-%s"), tszKEYStr, tszVLUStr);
		if (nRet != 2)
		{
			break;
		}
		stl_MapISPName.insert(std::make_pair(_ttxoi(tszKEYStr), tszVLUStr));
		ptszTokStr = _tcsxtok(NULL, _X(","));
	}
	//得到记录分区
	memcpy(&st_ProtocolRecord, ptszMSGBuffer + nPos, sizeof(XENGINE_PROTOCOLHDR));
	nPos += sizeof(XENGINE_PROTOCOLHDR);
	nPos += st_ProtocolRecord.unPacketSize;
	//得到索引分区
	memcpy(&st_ProtocolIndex, ptszMSGBuffer + nPos, sizeof(XENGINE_PROTOCOLHDR));
	nPos += sizeof(XENGINE_PROTOCOLHDR);
	return true;
}
std::string CAPIModule_PhoneNumber::APIModule_PhoneNumber_7Digits(LPCXSTR lpszMSGBuffer)
{
	APIPhone_IsErrorOccur = false;

	std::string str = lpszMSGBuffer;

	if (str.length() < 7) 
	{
		str.append(7 - str.length(), '0');
	}
	else if (str.length() > 7) 
	{
		str = str.substr(0, 7);
	}

	return str;
}