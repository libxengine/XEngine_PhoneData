#include "pch.h"
#include "APIModule_PhoneNumber/APIModule_PhoneNumber.h"
/********************************************************************
//    Created:     2024/06/28  14:55:16
//    File Name:   D:\phonedata\Source\C\XEngine_APIModulePhone\pch.cpp
//    File Path:   D:\phonedata\Source\C\XEngine_APIModulePhone
//    File Base:   pch
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出实现
//    History:
*********************************************************************/
bool APIPhone_IsErrorOccur = false;
XLONG APIPhone_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CAPIModule_PhoneNumber m_APIPhone;
//////////////////////////////////////////////////////////////////////////
//                        导出实现
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG APIPhone_GetLastError(int* pInt_ErrorCode)
{
	if (NULL != pInt_ErrorCode)
	{
		*pInt_ErrorCode = errno;
	}
	return APIPhone_dwErrorCode;
}
/************************************************************************/
/*                         号码查询                                     */
/************************************************************************/
extern "C" bool APIModule_PhoneNumber_Init(LPCXSTR lpszDBFile)
{
	return m_APIPhone.APIModule_PhoneNumber_Init(lpszDBFile);
}
extern "C" void APIModule_PhoneNumber_UnInit()
{
	return m_APIPhone.APIModule_PhoneNumber_UnInit();
}
extern "C" bool APIModule_PhoneNumber_Query(XENGINE_PHONEINFO* pSt_PhoneInfo)
{
	return m_APIPhone.APIModule_PhoneNumber_Query(pSt_PhoneInfo);
}