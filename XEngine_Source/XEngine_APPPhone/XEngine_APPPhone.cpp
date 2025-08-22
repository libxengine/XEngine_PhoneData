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

#ifdef _XENGINE_APPPHONE_CHARSET_UTF
	LPCXSTR lspzDestFile = _X("D:\\XEngine_PhoneData\\XEngine_Release\\phone_utf1.dat");
#else
	LPCXSTR lspzDestFile = _X("D:\\XEngine_PhoneData\\XEngine_Release\\phone_gbk1.dat");
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
		XCHAR tszLocationBuffer[4096] = {};

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

		pSt_DBDestFile = _xtfopen(lspzDestFile, _X("wb"));
		if (NULL == pSt_DBDestFile)
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("执行电话解封包中,创建目标失败"));
			return -1;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("执行电话解封包中,创建目标成功"));
		//////////////////////////////////////////////////////////////////////////HDR
		int nMSGLen = 0;
		XCHAR tszMSGBuffer[1024] = {};

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
		int nCount = 0;
		nMSGLen = 0;
		memset(tszMSGBuffer, 0, sizeof(tszMSGBuffer));

		while (1)
		{
			XCHAR tszMSGBuffer[XPATH_MAX] = {};
			if (NULL == fgets(tszMSGBuffer, XPATH_MAX, pSt_PhoneFile))
			{
				break;
			}
			nCount++;
		}
		m_PhonePacket.XEngine_PhonePacket_PHoneInfo(tszMSGBuffer, &nMSGLen, nCount);
		fwrite(tszMSGBuffer, 1, nMSGLen, pSt_DBDestFile);

		while (1)
		{
			XCHAR tszMSGBuffer[XPATH_MAX] = {};
			if (NULL == fgets(tszMSGBuffer, XPATH_MAX, pSt_PhoneFile))
			{
				break;
			}
			fwrite(tszMSGBuffer, 1, _tcsxlen(tszMSGBuffer), pSt_DBDestFile);
		}
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