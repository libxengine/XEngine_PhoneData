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
XHANDLE xhLog = NULL;
HELPCOMPONENTS_XLOG_CONFIGURE st_XLogConfigure = {};
PHONEMODULE_APPPARAMETER st_APPParameter = {};

#define _XENGINE_APPPHONE_CHARSET_UTF 1

void XEngine_APPPhone_Stop(int signo)
{
#ifdef _WINDOWS
	HelpComponents_XLog_Destroy(xhLog);

#endif
	exit(0);
}

int main()
{
    FILE* pSt_ISPFile = NULL;
    FILE* pSt_LocationFile = NULL;
    FILE* pSt_PhoneFile = NULL;
    FILE* pSt_DBDestFile = NULL;

#ifndef _DEBUG
	if (setlocale(LC_ALL, ".UTF8") == NULL)
	{
		return -1;
	}
#endif
	LPCXSTR lpszISPFile = _X("D:\\XEngine_PhoneData\\XEngine_DBSource\\ISP.txt");
	LPCXSTR lpszLocationFile = _X("D:\\XEngine_PhoneData\\XEngine_DBSource\\Location.txt");
	LPCXSTR lpszPhoneFile = _X("D:\\XEngine_PhoneData\\XEngine_DBSource\\Phone.txt");

#if 1 == _XENGINE_APPPHONE_CHARSET_UTF
	LPCXSTR lpszDestFile = _X("D:\\XEngine_PhoneData\\XEngine_Release\\phone_utf1.dat");
#else
	LPCXSTR lpszDestFile = _X("D:\\XEngine_PhoneData\\XEngine_Release\\phone_gbk1.dat");
#endif

	xhLog = HelpComponents_XLog_Init(HELPCOMPONENTS_XLOG_OUTTYPE_STD, &st_XLogConfigure);
	if (NULL == xhLog)
	{
		printf("启动服务中,启动日志失败,错误：%lX", XLog_GetLastError());
        goto XENGINE_APPPHONE_EXIT;
	}
	//设置日志打印级别
	HelpComponents_XLog_SetLogPriority(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("执行电话解封包中,初始化日志系统成功"));

	signal(SIGINT, XEngine_APPPhone_Stop);
	signal(SIGTERM, XEngine_APPPhone_Stop);
	signal(SIGABRT, XEngine_APPPhone_Stop);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("执行电话解封包中,初始化信号量处理程序成功"));
	//打包
	st_APPParameter.bPacket = true;
    if (st_APPParameter.bPacket)
    {
		CXEngine_PhonePacket m_PhonePacket;

		XCHAR tszISPBuffer[XPATH_MAX] = {};
		XCHAR tszLocationBuffer[8192] = {};

		pSt_ISPFile = _xtfopen(lpszISPFile, _X("rb"));
		if (NULL == pSt_ISPFile)
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("执行电话解封包中,打开ISP源失败"));
			goto XENGINE_APPPHONE_EXIT;
		}
		int nRet = fread(tszISPBuffer, 1, XPATH_MAX, pSt_ISPFile);
		fclose(pSt_ISPFile);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("执行电话解封包中,读取ISP源成功,数据大小:%d"), nRet);

		pSt_LocationFile = _xtfopen(lpszLocationFile, _X("rb"));
		if (NULL == pSt_ISPFile)
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("执行电话解封包中,打开位置源失败"));
			return -1;
		}
		nRet = fread(tszLocationBuffer, 1, sizeof(tszLocationBuffer), pSt_ISPFile);
		fclose(pSt_LocationFile);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("执行电话解封包中,读取Location源成功,数据大小:%d"), nRet);

		pSt_PhoneFile = _xtfopen(lpszPhoneFile, _X("rb"));
		if (NULL == pSt_ISPFile)
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("执行电话解封包中,打开电话源失败"));
			return -1;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("执行电话解封包中,读取Phone源成功"));

		pSt_DBDestFile = _xtfopen(lpszDestFile, _X("wb"));
		if (NULL == pSt_DBDestFile)
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("执行电话解封包中,创建目标失败"));
			return -1;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("执行电话解封包中,创建目标成功"));
		//////////////////////////////////////////////////////////////////////////HDR
		int nMSGLen = 0;
		XCHAR tszMSGBuffer[8192] = {};

		m_PhonePacket.XEngine_PhonePacket_Header(tszMSGBuffer, &nMSGLen);
		fwrite(tszMSGBuffer, 1, nMSGLen, pSt_DBDestFile);
		//////////////////////////////////////////////////////////////////////////ISP
		nMSGLen = 0;
		memset(tszMSGBuffer, 0, sizeof(tszMSGBuffer));

		m_PhonePacket.XEngine_PhonePacket_ISPInfo(tszMSGBuffer, &nMSGLen, tszISPBuffer);
		fwrite(tszMSGBuffer, 1, nMSGLen, pSt_DBDestFile);
		//////////////////////////////////////////////////////////////////////////Location
		nMSGLen = 0;
		memset(tszMSGBuffer, 0, sizeof(tszMSGBuffer));

		m_PhonePacket.XEngine_PhonePacket_LocationInfo(tszMSGBuffer, &nMSGLen, tszLocationBuffer);
		fwrite(tszMSGBuffer, 1, nMSGLen, pSt_DBDestFile);
		//////////////////////////////////////////////////////////////////////////Phone
		int nPos = ftell(pSt_DBDestFile);
		XENGINE_PROTOCOLHDR st_ProtocolHdr = {};

		st_ProtocolHdr.wHeader = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_HEADER;
		st_ProtocolHdr.byVersion = ENUM_XENGINE_PROTOCOLHDR_PAYLOAD_TYPE_STRING;
		st_ProtocolHdr.unOperatorType = XENGINE_COMMUNICATION_PROTOCOL_TYPE_PHONE;
		st_ProtocolHdr.unOperatorCode = XENGINE_COMMUNICATION_PROTOCOL_CODE_PHONE_INDEX;
		st_ProtocolHdr.unPacketSize = 0;
		st_ProtocolHdr.wPacketSerial = 0;
		st_ProtocolHdr.wCrypto = 0;
		st_ProtocolHdr.wTail = XENGIEN_COMMUNICATION_PACKET_PROTOCOL_TAIL;

		fwrite(&st_ProtocolHdr, 1, sizeof(XENGINE_PROTOCOLHDR), pSt_DBDestFile);
		while (1)
		{
			memset(tszMSGBuffer, 0, sizeof(tszMSGBuffer));
			if (NULL == fgets(tszMSGBuffer, XPATH_MAX, pSt_PhoneFile))
			{
				break;
			}
			typedef struct
			{
				XCHAR tszPhoneStr[64];
				XCHAR tszAreaStr[64];
				XCHAR tszPhoneType[64];
				XCHAR tszIndexStr[64];
				XCHAR tszTransferStr[64];
			}XENGINE_PHONEINDEX;

			XENGINE_PHONEINDEX st_PhoneIndex = {};
			int nRet = _stxscanf(tszMSGBuffer, _X("%[^-]-%[^-]-%[^-]-%[^-]-%s"), st_PhoneIndex.tszPhoneStr, st_PhoneIndex.tszAreaStr, st_PhoneIndex.tszPhoneType, st_PhoneIndex.tszIndexStr, st_PhoneIndex.tszTransferStr);
			if (nRet != 5)
			{
				break;
			}
			_xstprintf(tszMSGBuffer, _X("%s-%s-%s-%s\n"),st_PhoneIndex.tszPhoneStr, st_PhoneIndex.tszAreaStr, st_PhoneIndex.tszPhoneType, st_PhoneIndex.tszTransferStr);
			st_ProtocolHdr.unPacketSize++;
			fwrite(tszMSGBuffer, 1, _tcsxlen(tszMSGBuffer), pSt_DBDestFile);
		}
		//回写
		fseek(pSt_DBDestFile, nPos, SEEK_SET);
		fwrite(&st_ProtocolHdr, 1, sizeof(XENGINE_PROTOCOLHDR), pSt_DBDestFile);
		fclose(pSt_DBDestFile);
    }
    else
    {
		CXEngine_PhoneUNPack m_PhoneUNPack;
    }
    

XENGINE_APPPHONE_EXIT:
	//销毁日志资源
	HelpComponents_XLog_Destroy(xhLog);

	fclose(pSt_ISPFile);
	fclose(pSt_DBDestFile);
    fclose(pSt_PhoneFile);
    fclose(pSt_DBDestFile);
	return 0;
}