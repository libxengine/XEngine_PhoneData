#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_Types.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include "../../XPhone_CommHdr.h"

typedef struct
{
	XCHAR tszPhoneStr[64];
	XCHAR tszAreaStr[64];
	XCHAR tszPhoneType[64];
	XCHAR tszIndexStr[64];
	XCHAR tszTransferStr[64];
}XENGINE_PHONEINFO;

//这只是个简单示例.更复杂的查找方法和算法需要自己实现.谢谢
int main()
{
	LPCXSTR lpszFile = _X("D:\\phonedata\\Data\\phone_gbk.dat");
	LPCXSTR lpszPhoneStr = _X("1994088");
	FILE* pSt_File = _xtfopen(lpszFile, _X("rb"));

	if (NULL == pSt_File)
	{
		printf("read\n");
		return -1;
	}
	XCHAR* ptszMSGBuffer = (XCHAR*)malloc(XENGINE_MEMORY_SIZE_LARGE);
	if (NULL == ptszMSGBuffer)
	{
		return -1;
	}
	memset(ptszMSGBuffer, '\0', XENGINE_MEMORY_SIZE_LARGE);

	size_t nFSize = fread(ptszMSGBuffer, 1, XENGINE_MEMORY_SIZE_LARGE, pSt_File);
	fclose(pSt_File);

	int nPos = 0;
	XCHAR tszMSGBuffer[MAX_PATH] = {};
	XENGINE_PROTOCOLHDR st_ProtocolHdr = {};
	//得到头分区数据
	memcpy(&st_ProtocolHdr, ptszMSGBuffer, sizeof(XENGINE_PROTOCOLHDR));
	nPos += sizeof(XENGINE_PROTOCOLHDR);
	if (XENGIEN_COMMUNICATION_PACKET_PROTOCOL_HEADER != st_ProtocolHdr.wHeader || XENGIEN_COMMUNICATION_PACKET_PROTOCOL_TAIL != st_ProtocolHdr.wTail || ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_PHONE != st_ProtocolHdr.unOperatorType)
	{
		return false;
	}
	memcpy(tszMSGBuffer, ptszMSGBuffer + nPos, st_ProtocolHdr.unPacketSize);
	nPos += st_ProtocolHdr.unPacketSize;
	//得到类型映射
	XENGINE_PROTOCOLHDR st_ProtocolMap = {};
	memcpy(&st_ProtocolMap, ptszMSGBuffer + nPos, sizeof(XENGINE_PROTOCOLHDR));
	nPos += sizeof(XENGINE_PROTOCOLHDR);

	memset(tszMSGBuffer, '\0', sizeof(tszMSGBuffer));
	memcpy(tszMSGBuffer, ptszMSGBuffer + nPos, st_ProtocolMap.unPacketSize);
	nPos += st_ProtocolMap.unPacketSize;
	
	std::unordered_map<int, std::string> stl_MapISPName;
	XCHAR* ptszTokStr = _tcsxtok(tszMSGBuffer, _X(","));
	while (NULL != ptszTokStr)
	{
		XCHAR tszKEYStr[16] = {};
		XCHAR tszVLUStr[16] = {};
		int nRet = _stxscanf(ptszTokStr, _X("%[^-]-%s"), tszKEYStr, tszVLUStr);
		if (nRet != 2)
		{
			break;
		}
		stl_MapISPName.insert(std::make_pair(_ttxoi(tszKEYStr), tszVLUStr));
		ptszTokStr = _tcsxtok(NULL, _X(","));
	}
	//得到记录分区
	XENGINE_PROTOCOLHDR st_ProtocolRecord = {};
	memcpy(&st_ProtocolRecord, ptszMSGBuffer + nPos, sizeof(XENGINE_PROTOCOLHDR));
	nPos += sizeof(XENGINE_PROTOCOLHDR);
	nPos += st_ProtocolRecord.unPacketSize;
	//得到索引分区
	memset(&st_ProtocolRecord, '\0', sizeof(XENGINE_PROTOCOLHDR));
	memcpy(&st_ProtocolRecord, ptszMSGBuffer + nPos, sizeof(XENGINE_PROTOCOLHDR));
	nPos += sizeof(XENGINE_PROTOCOLHDR);

	XCHAR* ptszPhoneIndex = (XCHAR*)malloc(XENGINE_MEMORY_SIZE_LARGE);
	if (NULL == ptszPhoneIndex)
	{
		return -1;
	}
	memset(ptszPhoneIndex, '\0', XENGINE_MEMORY_SIZE_LARGE);
	memcpy(ptszPhoneIndex, ptszMSGBuffer + nPos, nFSize - nPos);

	ptszTokStr = _tcsxtok(ptszPhoneIndex, _X("\n"));
	while (NULL != ptszTokStr)
	{
		XENGINE_PHONEINFO st_PhoneInfo = {};

		int nRet = _stxscanf(ptszTokStr, _X("%[^-]-%[^-]-%[^-]-%[^-]-%s"), st_PhoneInfo.tszPhoneStr, st_PhoneInfo.tszAreaStr, st_PhoneInfo.tszPhoneType, st_PhoneInfo.tszIndexStr, st_PhoneInfo.tszTransferStr);
		if (nRet != 5)
		{
			break;
		}
		if (0 == _tcsxnicmp(lpszPhoneStr, st_PhoneInfo.tszPhoneStr, _tcsxlen(lpszPhoneStr)))
		{
			XCHAR tszLocationStr[MAX_PATH] = {};

			memcpy(tszLocationStr, ptszMSGBuffer + _ttxoi(st_PhoneInfo.tszIndexStr), 13);
			printf("%s = %s\n", lpszPhoneStr, tszLocationStr);
			break;
		}
		ptszTokStr = _tcsxtok(NULL, _X("\n"));
	}

	free(ptszMSGBuffer);
	free(ptszPhoneIndex);
	return 0;
}