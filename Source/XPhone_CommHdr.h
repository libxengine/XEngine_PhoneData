#pragma once
/********************************************************************
//    Created:     2024/06/24  14:04:51
//    File Name:   D:\phonedata\Source\XPhone_CommHdr.h
//    File Path:   D:\phonedata\Source
//    File Base:   XPhone_CommHdr
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     公用头文件
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                          主协议定义;unOperatorType
//////////////////////////////////////////////////////////////////////////
typedef enum
{
	//用户消息
	ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_PHONE = ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_USER + 100
}ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_CUSTOM;
//银行卡类型
typedef enum
{
	ENUM_XENGINE_PHONE_TYPE_UNKNOWN = 0,	    //未知
	ENUM_XENGINE_PHONE_TYPE_SMCS                //
}ENUM_XENGINE_PHONE_TYPE;
//////////////////////////////////////////////////////////////////////////
//                          子协议定义:unOperatorCode
//////////////////////////////////////////////////////////////////////////
//后台服务协议
#define XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_PHONE_HDR 0x0001     //数据头
#define XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_PHONE_RECORD 0x0002  //数据记录集
#define XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_PHONE_INDEX 0x0003   //索引