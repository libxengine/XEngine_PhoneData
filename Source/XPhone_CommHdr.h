#pragma once
/********************************************************************
//    Created:     2024/06/24  14:04:51
//    File Name:   D:\phonedata\Source\XPhone_CommHdr.h
//    File Path:   D:\phonedata\Source
//    File Base:   XPhone_CommHdr
//    File Ext:    h
//    Project:     XEngine(����ͨ������)
//    Author:      qyt
//    Purpose:     ����ͷ�ļ�
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                          ��Э�鶨��;unOperatorType
//////////////////////////////////////////////////////////////////////////
typedef enum
{
	//�û���Ϣ
	ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_PHONE = ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_USER + 100
}ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_CUSTOM;
//���п�����
typedef enum
{
	ENUM_XENGINE_PHONE_TYPE_UNKNOWN = 0,	    //δ֪
	ENUM_XENGINE_PHONE_TYPE_SMCS                //
}ENUM_XENGINE_PHONE_TYPE;
//////////////////////////////////////////////////////////////////////////
//                          ��Э�鶨��:unOperatorCode
//////////////////////////////////////////////////////////////////////////
//��̨����Э��
#define XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_PHONE_HDR 0x0001     //����ͷ
#define XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_PHONE_RECORD 0x0002  //���ݼ�¼��
#define XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_PHONE_INDEX 0x0003   //����