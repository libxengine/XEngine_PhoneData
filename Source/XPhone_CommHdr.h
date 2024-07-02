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
#define XENGINE_COMMUNICATION_PROTOCOL_TYPE_PHONE (ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_USER + 100)

//���п�����
typedef enum
{
	ENUM_XENGINE_PHONE_TYPE_UNKNOWN = 0,	    //δ֪
	ENUM_XENGINE_PHONE_TYPE_CMCC,               //�й��ƶ�
	ENUM_XENGINE_PHONE_TYPE_CUCC,               //�й���ͨ
	ENUM_XENGINE_PHONE_TYPE_CTCC,               //�й�����
	ENUM_XENGINE_PHONE_TYPE_CRTG,               //�й����
	ENUM_XENGINE_PHONE_TYPE_CTCC_V,             //��������
	ENUM_XENGINE_PHONE_TYPE_CUCC_V,             //��ͨ����
	ENUM_XENGINE_PHONE_TYPE_CMCC_V,             //�ƶ�����
	ENUM_XENGINE_PHONE_TYPE_CTCC_I,             //��������
	ENUM_XENGINE_PHONE_TYPE_CUCC_I,             //��ͨ����
	ENUM_XENGINE_PHONE_TYPE_CMCC_I,             //�ƶ�����
	ENUM_XENGINE_PHONE_TYPE_SATE,               //����ͨ��
	ENUM_XENGINE_PHONE_TYPE_IOT                 //������
}ENUM_XENGINE_PHONE_TYPE;
//////////////////////////////////////////////////////////////////////////
//                          ��Э�鶨��:unOperatorCode
//////////////////////////////////////////////////////////////////////////
//��̨����Э��
#define XENGINE_COMMUNICATION_PROTOCOL_CODE_PHONE_HDR 0x0001              //����ͷ
#define XENGINE_COMMUNICATION_PROTOCOL_CODE_PHONE_ISP 0x0002              //��Ӫ��
#define XENGINE_COMMUNICATION_PROTOCOL_CODE_PHONE_RECORD 0x0003           //���ݼ�¼��
#define XENGINE_COMMUNICATION_PROTOCOL_CODE_PHONE_INDEX 0x0004            //����
//////////////////////////////////////////////////////////////////////////
//                          ���ݽṹ����
//////////////////////////////////////////////////////////////////////////
typedef struct
{
	XCHAR tszPhoneNumber[64];   //�绰����
	XCHAR tszProvincer[64];     //ʡ/������/ֱϽ��
	XCHAR tszCity[64];          //��/��     
	XCHAR tszAreaCode[64];      //����
	XCHAR tszISPName[64];       //��Ӫ������
}XENGINE_PHONEINFO;