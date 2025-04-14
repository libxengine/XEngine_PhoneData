#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <list>
#include <string>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_Types.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include "../../Source/XPhone_CommHdr.h"

#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")

#define _XENGINE_APPPHONE_CHARSET_UTF 1
int nPos = 0;
FILE* pSt_RFile = NULL;
FILE* pSt_WFile = NULL;
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

bool XEngine_APPPhone_Location(XCHAR * ptszMSGBuffer, std::list<XENGINE_LOCATION>* pStl_ListLocation)
{
	char* ptszTokStr = ptszMSGBuffer;
	// 遍历数组，直到指针指向 \0
	while (*ptszTokStr != '\0')
	{
		XCHAR tszLocationStr[MAX_PATH] = {};
		XENGINE_LOCATION st_Location = {};

		st_Location.nPos = nPos;
		int nRet = _stxscanf(ptszTokStr, _X("%[^|]|%[^|]|%[^|]|%s"), st_Location.tszProvinceStr, st_Location.tszCityStr, st_Location.tszCodeStr, st_Location.tszAreaStr);
		if (nRet != 4)
		{
			break;
		}
		nRet = _xstprintf(tszLocationStr, _X("%s-%s-%s "), st_Location.tszAreaStr, st_Location.tszProvinceStr, st_Location.tszCityStr);

#ifdef _XENGINE_APPPHONE_CHARSET_UTF
		XCHAR tszUTFBuffer[MAX_PATH] = {};
		BaseLib_Charset_AnsiToUTF(tszLocationStr, tszUTFBuffer, &nRet);
		fwrite(tszUTFBuffer, 1, nRet, pSt_WFile);
#else
		fwrite(tszLocationStr, 1, nRet, pSt_WFile);
#endif
		nPos += nRet;
		pStl_ListLocation->push_back(st_Location);

        ptszTokStr += strlen(ptszTokStr) + 1;     // 移动指针到下一个子字符串的开始
	}
    return true;
}
bool XEngine_APPPhone_Phone(LPCXSTR lpszMSGBuffer, std::list<XENGINE_LOCATION>* pStl_ListLocation)
{
	XCHAR tszPhoneStr[MAX_PATH] = {};
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
	fwrite(tszPhoneStr, 1, nRet, pSt_WFile);
	nPos += nRet;

	return true;
}

int main()
{
#ifndef _DEBUG
	if (setlocale(LC_ALL, ".UTF8") == NULL)
	{
		return -1;
	}
#endif
    LPCXSTR lpszSrceFile = _X("D:\\XEngine_PhoneData\\Data\\Source.txt");
#ifdef _XENGINE_APPPHONE_CHARSET_UTF
    LPCXSTR lspzDestFile = _X("D:\\XEngine_PhoneData\\Data\\phone_utf.dat");
#else
    LPCXSTR lspzDestFile = _X("D:\\XEngine_PhoneData\\Data\\phone_gbk.dat");
#endif
    pSt_RFile = _xtfopen(lpszSrceFile, _X("rb"));
    pSt_WFile = _xtfopen(lspzDestFile, _X("wb"));

    if (NULL == pSt_RFile)
    {
        printf("read\n");
        return -1;
    }
    if (NULL == pSt_WFile)
    {
		printf("write\n");
		return -1;
    }
    XENGINE_PROTOCOLHDR st_ProtocolHdr = {};
    //////////////////////////////////////////////////////////////////////////HDR
	LPCXSTR lpszFVer = _X("20250414");
    int nHLen = _tcsxlen(lpszFVer);

    st_ProtocolHdr.wHeader = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_HEADER;
    st_ProtocolHdr.byVersion = ENUM_XENGINE_PROTOCOLHDR_PAYLOAD_TYPE_STRING;
    st_ProtocolHdr.unOperatorType = XENGINE_COMMUNICATION_PROTOCOL_TYPE_PHONE;
    st_ProtocolHdr.unOperatorCode = XENGINE_COMMUNICATION_PROTOCOL_CODE_PHONE_HDR;
    st_ProtocolHdr.unPacketSize = nHLen;
    st_ProtocolHdr.wCrypto = 0;
    st_ProtocolHdr.wTail = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_TAIL;

    fwrite(&st_ProtocolHdr, 1, sizeof(XENGINE_PROTOCOLHDR), pSt_WFile);
    nPos += sizeof(XENGINE_PROTOCOLHDR);
	fwrite(lpszFVer, 1, nHLen, pSt_WFile);
    nPos += nHLen;
    //////////////////////////////////////////////////////////////////////////ISP
    LPCXSTR lpszISPName = _X("0-UNKNOW,1-CMCC,2-CUCC,3-CTCC,4-CRTG,10-CTCC_V,11-CUCC_V,12-CMCC_V,20-CTCC_I,21-CUCC_I,22-CMCC_I,30-SATE,31-IOT");
    nHLen = _tcsxlen(lpszISPName);
	st_ProtocolHdr.wHeader = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_HEADER;
	st_ProtocolHdr.byVersion = ENUM_XENGINE_PROTOCOLHDR_PAYLOAD_TYPE_STRING;
	st_ProtocolHdr.unOperatorType = XENGINE_COMMUNICATION_PROTOCOL_TYPE_PHONE;
	st_ProtocolHdr.unOperatorCode = XENGINE_COMMUNICATION_PROTOCOL_CODE_PHONE_ISP;
	st_ProtocolHdr.unPacketSize = nHLen;
    st_ProtocolHdr.wPacketSerial = 13;
	st_ProtocolHdr.wCrypto = 0;
	st_ProtocolHdr.wTail = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_TAIL;

	fwrite(&st_ProtocolHdr, 1, sizeof(XENGINE_PROTOCOLHDR), pSt_WFile);
	nPos += sizeof(XENGINE_PROTOCOLHDR);
	fwrite(lpszISPName, 1, nHLen, pSt_WFile);
	nPos += nHLen;
    //////////////////////////////////////////////////////////////////////////
    XCHAR* ptszMSGBuffer = (XCHAR*)malloc(XENGINE_MEMORY_SIZE_MAX);
    if (NULL == ptszMSGBuffer)
    {
        return -1;
    }
    memset(ptszMSGBuffer, '\0', XENGINE_MEMORY_SIZE_MAX);

    int i = 0;
    while (true)
    {
		XCHAR ch = fgetc(pSt_RFile);
        if (ch == '\n')
        {
            break;
        }
		ptszMSGBuffer[i++] = ch;
    }

    int nNow = nPos;
    fwrite(&st_ProtocolHdr, 1, sizeof(XENGINE_PROTOCOLHDR), pSt_WFile);
	nPos += sizeof(XENGINE_PROTOCOLHDR);
    std::list<XENGINE_LOCATION> stl_ListLocation;
    XEngine_APPPhone_Location(ptszMSGBuffer, &stl_ListLocation);
    //重新覆写头
	st_ProtocolHdr.wHeader = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_HEADER;
	st_ProtocolHdr.byVersion = ENUM_XENGINE_PROTOCOLHDR_PAYLOAD_TYPE_STRING;
	st_ProtocolHdr.unOperatorType = XENGINE_COMMUNICATION_PROTOCOL_TYPE_PHONE;
	st_ProtocolHdr.unOperatorCode = XENGINE_COMMUNICATION_PROTOCOL_CODE_PHONE_RECORD;
	st_ProtocolHdr.unPacketSize = nPos - nNow - sizeof(XENGINE_PROTOCOLHDR);
	st_ProtocolHdr.wCrypto = 0;
	st_ProtocolHdr.wTail = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_TAIL;
    fseek(pSt_WFile, nNow, SEEK_SET);
	fwrite(&st_ProtocolHdr, 1, sizeof(XENGINE_PROTOCOLHDR), pSt_WFile);
    
    nNow = nPos;
    fseek(pSt_WFile, 0, SEEK_END);
    fwrite(&st_ProtocolHdr, 1, sizeof(XENGINE_PROTOCOLHDR), pSt_WFile);
    nPos += sizeof(XENGINE_PROTOCOLHDR);
    int nCount = 0;
    while (1)
    {
        XCHAR tszMSGBuffer[MAX_PATH] = {};
        if (NULL == fgets(tszMSGBuffer, MAX_PATH, pSt_RFile))
        {
            break;
        }
        tszMSGBuffer[_tcsxlen(tszMSGBuffer) - 1] = '\0';
        tszMSGBuffer[_tcsxlen(tszMSGBuffer) - 1] = '\0';
   
        nCount++;
        XEngine_APPPhone_Phone(tszMSGBuffer, &stl_ListLocation);
    }
	st_ProtocolHdr.wHeader = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_HEADER;
	st_ProtocolHdr.byVersion = ENUM_XENGINE_PROTOCOLHDR_PAYLOAD_TYPE_STRING;
	st_ProtocolHdr.unOperatorType = XENGINE_COMMUNICATION_PROTOCOL_TYPE_PHONE;
	st_ProtocolHdr.unOperatorCode = XENGINE_COMMUNICATION_PROTOCOL_CODE_PHONE_INDEX;
	st_ProtocolHdr.unPacketSize = nCount;
	st_ProtocolHdr.wCrypto = 0;
	st_ProtocolHdr.wTail = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_TAIL;
	fseek(pSt_WFile, nNow, SEEK_SET);
	fwrite(&st_ProtocolHdr, 1, sizeof(XENGINE_PROTOCOLHDR), pSt_WFile);

    fclose(pSt_RFile);
    fclose(pSt_WFile);
    return 0;
}