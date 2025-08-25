#include "XEngine_PhoneHdr.h"
/********************************************************************
//    Created:     2025/08/22  14:33:04
//    File Name:   D:\XEngine_PhoneData\XEngine_Source\XEngine_APPPhone\XEngine_Configure.cpp
//    File Path:   D:\XEngine_PhoneData\XEngine_Source\XEngine_APPPhone
//    File Base:   XEngine_Configure
//    File Ext:    cpp
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     启动配置参数
//    History:
*********************************************************************/
bool XEngine_Configure_Parament(int argc, char** argv)
{
	for (int i = 0; i < argc; i++)
	{
		if (0 == _tcsxicmp("-h", argv[i]))
		{
			XEngine_Configure_Help();
			return false;
		}
		else if (0 == _tcsxicmp("-p", argv[i]))
		{
			st_APPParameter.nPType = _ttxoi(argv[i++]);
		}
	}

	return true;
}

void XEngine_Configure_Help()
{
	printf(_X("--------------------------启动参数帮助开始--------------------------\n"));
	printf(_X("启动参数：程序 参数 参数值，参数是区分大小写的。\n"));
	printf(_X("-h or -H：启动参数帮助提示信息\n"));
	printf(_X("--------------------------启动参数帮助结束--------------------------\n"));
}
