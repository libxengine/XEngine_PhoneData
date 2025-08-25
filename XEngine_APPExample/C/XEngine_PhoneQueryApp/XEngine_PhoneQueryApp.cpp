#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <string>
#include <unordered_map>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_Types.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include "../../../XEngine_Source/XPhone_CommHdr.h"
#include "../../../XEngine_Source/XEngine_APIModulePhone/APIPhone_Define.h"
#include "../../../XEngine_Source/XEngine_APIModulePhone/APIPhone_Error.h"

#ifdef _MSC_BUILD
#ifdef _DEBUG
#ifdef _M_X64
#pragma comment(lib,"../../../XEngine_Source/x64/Debug/XEngine_APIModulePhone")
#elif _M_ARM64
#pragma comment(lib,"../../../XEngine_Source/ARM64/Debug/XEngine_APIModulePhone")
#elif _M_IX86
#pragma comment(lib,"../../../XEngine_Source/Debug/XEngine_APIModulePhone")
#endif
#else
#ifdef _M_X64
#pragma comment(lib,"../../../XEngine_Source/x64/Release/XEngine_APIModulePhone")
#elif _M_ARM64
#pragma comment(lib,"../../../XEngine_Source/ARM64/Release/XEngine_APIModulePhone")
#elif _M_IX86
#pragma comment(lib,"../../../XEngine_Source/Release/XEngine_APIModulePhone")
#endif
#endif
#endif
//这只是个简单示例.更复杂的查找方法和算法需要自己实现

int main()
{
#ifndef _DEBUG
	if (setlocale(LC_ALL, ".UTF8") == NULL)
	{
		printf("Error setting locale.\n");
		return false;
	}
#endif
	LPCXSTR lpszFile = _X("D:\\XEngine_PhoneData\\XEngine_Release\\phone_gbk.dat");
	if (!APIModule_PhoneNumber_Init(lpszFile))
	{
		printf("APIModule_PhoneNumber_Init:%lX\n", APIPhone_GetLastError());
		return -1;
	}
	XENGINE_PHONEINFO st_PhoneInfo = {};

	_tcsxcpy(st_PhoneInfo.tszPhoneNumber, _X("1994088"));
	if (!APIModule_PhoneNumber_Query(&st_PhoneInfo))
	{
		printf("APIModule_PhoneNumber_Query:%lX\n", APIPhone_GetLastError());
		return -1;
	}
	printf("%s=%s,%s,%s,%s\n", st_PhoneInfo.tszPhoneNumber, st_PhoneInfo.tszISPName, st_PhoneInfo.tszProvincer, st_PhoneInfo.tszCity, st_PhoneInfo.tszAreaCode);

	APIModule_PhoneNumber_UnInit();
	return 0;
}