#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_Types.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include "../../XPhone_CommHdr.h"
#include "../XEngine_APIModulePhone/APIPhone_Define.h"
#include "../XEngine_APIModulePhone/APIPhone_Error.h"

#ifdef _DEBUG
#ifdef _WIN64
#pragma comment(lib,"../x64/Debug/XEngine_APIModulePhone")
#else
#pragma comment(lib,"../Debug/XEngine_APIModulePhone")
#endif
#else
#ifdef _WIN64
#pragma comment(lib,"../x64/Release/XEngine_APIModulePhone")
#else
#pragma comment(lib,"../Release/XEngine_APIModulePhone")
#endif
#endif
//这只是个简单示例.更复杂的查找方法和算法需要自己实现

int main()
{
	LPCXSTR lpszFile = _X("D:\\phonedata\\Data\\phone_gbk.dat");
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