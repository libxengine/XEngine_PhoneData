#pragma once
/********************************************************************
//    Created:     2024/06/28  14:55:29
//    File Name:   D:\phonedata\Source\C\XEngine_APIModulePhone\APIPhone_Define.h
//    File Path:   D:\phonedata\Source\C\XEngine_APIModulePhone
//    File Base:   APIPhone_Define
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     电话号码信息查询模块
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                       导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG APIPhone_GetLastError(int* pInt_ErrorCode = NULL);
/*********************************************************************************
*                                导出函数定义                                    *
*********************************************************************************/
/********************************************************************
函数名称：APIModule_PhoneNumber_Init
函数功能：初始化模块
 参数.一：lpszDBFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入数据库路径
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool APIModule_PhoneNumber_Init(LPCXSTR lpszDBFile);
/********************************************************************
函数名称：APIModule_PhoneNumber_UnInit
函数功能：反初始化
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" void APIModule_PhoneNumber_UnInit();
/********************************************************************
函数名称：APIModule_PhoneNumber_Query
函数功能：查询电话号码信息
 参数.一：pSt_PhoneInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要查询的号码,输出查询到的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool APIModule_PhoneNumber_Query(XENGINE_PHONEINFO* pSt_PhoneInfo);