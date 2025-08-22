#include "XEngine_PhoneHdr.h"
/********************************************************************
//    Created:     2025/08/22  13:56:51
//    File Name:   D:\XEngine_PhoneData\XEngine_Source\XEngine_APPPhone\XEngine_APPPhone.cpp
//    File Path:   D:\XEngine_PhoneData\XEngine_Source\XEngine_APPPhone
//    File Base:   XEngine_APPPhone
//    File Ext:    cpp
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     应用程序
//    History:
*********************************************************************/
int nPos = 0;
FILE* pSt_RFile = NULL;
FILE* pSt_WFile = NULL;

int main()
{
    CXEngine_PhonePacket m_PhonePacket;
    CXEngine_PhoneUNPack m_PhoneUNPack;
#ifndef _DEBUG
	if (setlocale(LC_ALL, ".UTF8") == NULL)
	{
		return -1;
	}
#endif
    LPCXSTR lpszSrceFile = _X("D:\\XEngine_PhoneData\\XEngine_Release\\Source.txt");
#ifdef _XENGINE_APPPHONE_CHARSET_UTF
    LPCXSTR lspzDestFile = _X("D:\\XEngine_PhoneData\\XEngine_Release\\phone_utf.dat");
#else
    LPCXSTR lspzDestFile = _X("D:\\XEngine_PhoneData\\XEngine_Release\\phone_gbk.dat");
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
    m_PhonePacket.XEngine_PhonePacket_Location(ptszMSGBuffer, &stl_ListLocation);
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
        XCHAR tszMSGBuffer[XPATH_MAX] = {};
        if (NULL == fgets(tszMSGBuffer, XPATH_MAX, pSt_RFile))
        {
            break;
        }
        tszMSGBuffer[_tcsxlen(tszMSGBuffer) - 1] = '\0';
        tszMSGBuffer[_tcsxlen(tszMSGBuffer) - 1] = '\0';
   
        nCount++;
        m_PhonePacket.XEngine_PhonePacket_Phone(tszMSGBuffer, &stl_ListLocation);
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