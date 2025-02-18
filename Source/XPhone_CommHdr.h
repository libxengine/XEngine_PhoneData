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
#define XENGINE_COMMUNICATION_PROTOCOL_TYPE_PHONE (ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_USER + 100)

//银行卡类型
typedef enum
{
	ENUM_XENGINE_PHONE_TYPE_UNKNOWN = 0,	    //未知
	ENUM_XENGINE_PHONE_TYPE_CMCC,               //中国移动
	ENUM_XENGINE_PHONE_TYPE_CUCC,               //中国联通
	ENUM_XENGINE_PHONE_TYPE_CTCC,               //中国电信
	ENUM_XENGINE_PHONE_TYPE_CRTG,               //中国广电
	ENUM_XENGINE_PHONE_TYPE_CTCC_V,             //电信虚拟
	ENUM_XENGINE_PHONE_TYPE_CUCC_V,             //联通虚拟
	ENUM_XENGINE_PHONE_TYPE_CMCC_V,             //移动虚拟
	ENUM_XENGINE_PHONE_TYPE_CTCC_I,             //电信座机
	ENUM_XENGINE_PHONE_TYPE_CUCC_I,             //联通座机
	ENUM_XENGINE_PHONE_TYPE_CMCC_I,             //移动座机
	ENUM_XENGINE_PHONE_TYPE_SATE,               //卫星通信
	ENUM_XENGINE_PHONE_TYPE_IOT                 //物联网
}ENUM_XENGINE_PHONE_TYPE;
//////////////////////////////////////////////////////////////////////////
//                          子协议定义:unOperatorCode
//////////////////////////////////////////////////////////////////////////
//后台服务协议
#define XENGINE_COMMUNICATION_PROTOCOL_CODE_PHONE_HDR 0x0001              //数据头
#define XENGINE_COMMUNICATION_PROTOCOL_CODE_PHONE_ISP 0x0002              //运营商
#define XENGINE_COMMUNICATION_PROTOCOL_CODE_PHONE_RECORD 0x0003           //数据记录集
#define XENGINE_COMMUNICATION_PROTOCOL_CODE_PHONE_INDEX 0x0004            //索引
//////////////////////////////////////////////////////////////////////////
//                          数据结构定义
//////////////////////////////////////////////////////////////////////////
typedef struct
{
	XCHAR tszPhoneNumber[64];   //电话号码
	XCHAR tszProvincer[64];     //省/自治区/直辖市
	XCHAR tszCity[64];          //市/区     
	XCHAR tszAreaCode[64];      //区号
	XCHAR tszISPName[64];       //运营商名称
}XENGINE_PHONEINFO;