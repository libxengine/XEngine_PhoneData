#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <list>
#include <string>
#include <windows.h>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_Types.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include "../XPhone_CommHdr.h"
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

#ifdef _MSC_BUILD
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")
#endif

#define _XENGINE_APPPHONE_CHARSET_UTF 1