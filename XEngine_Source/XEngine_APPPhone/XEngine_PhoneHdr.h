#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <list>
#include <string>
#include <windows.h>
#include <signal.h>
#include <unordered_map>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_Types.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_HelpComponents/XLog_Define.h>
#include <XEngine_Include/XEngine_HelpComponents/XLog_Error.h>
#include "../XPhone_CommHdr.h"
#include "XEngine_Configure.h"
#include "XEngine_PhonePacket.h"
#include "XEngine_PhoneUNPack.h"
/********************************************************************
//    Created:     2025/08/22  13:42:12
//    File Name:   D:\XEngine_PhoneData\XEngine_Source\XEngine_APPPhone\XEngine_PhoneHdr.h
//    File Path:   D:\XEngine_PhoneData\XEngine_Source\XEngine_APPPhone
//    File Base:   XEngine_PhoneHdr
//    File Ext:    h
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     公用头文件
//    History:
*********************************************************************/
typedef struct  
{
	bool bPacket;
}PHONEMODULE_APPPARAMETER;

extern XHANDLE xhLog;
extern HELPCOMPONENTS_XLOG_CONFIGURE st_XLogConfigure;

extern PHONEMODULE_APPPARAMETER st_APPParameter;

#ifdef _MSC_BUILD
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")
#pragma comment(lib,"XEngine_HelpComponents/HelpComponents_XLog")
#endif