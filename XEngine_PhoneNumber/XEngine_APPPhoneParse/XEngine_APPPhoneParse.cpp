#include <string>
#include <vector>
#include <cstdint>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>

#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")

#if defined(_WIN32)
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#else
#error Visual Studio 2010 SP1 or above required
#endif
#endif

enum CARDTYPE
{
	UNKNOWN = 0,	// 未知，查找失败
	CMCC,			// 中国移动
	CUCC,			// 中国联通
	CTCC,			// 中国电信
	CTCC_V,			// 电信虚拟运营商
	CUCC_V,			// 联通虚拟运营商
	CMCC_V			// 移动虚拟运营商
};

enum DATALEN
{
	CHAR_LENGTH = 1,
	INT_LENGTH = 4,
	PHONE_LENGTH = 7,
	HEAD_LENGTH = 8,
	PHONE_INDEX_LENGTH = 9
};

enum RECORD
{
	PROVINCE = 0,	// 省份
	CITY,			// 城市
	ZIPCODE,		// 邮编
	AREACODE		// 长途区号
};

std::string getPhoneType(CARDTYPE type);

struct PhoneInfo
{
	PhoneInfo()
		: type(UNKNOWN), phone(0) {	}

	CARDTYPE type;
	uint32_t phone;
	std::string zipCode;
	std::string areaCode;
	std::string province;
	std::string city;
};

struct DataHead
{
	char version[4];
	uint32_t offset;
};

struct Record
{
	uint32_t phone;
	uint32_t offset;
	uint8_t type;
};

class PhoneData
{
public:
	PhoneData();
	PhoneInfo _lookUp(uint32_t phone7) const;
	static std::string getRecordContent(const std::vector<char>& buffer, size_t startOffset);

private:
	std::vector<char> buffer;
	DataHead* head;
	size_t recordCount;
};



static std::vector<std::string> ssplit(const std::string& str, const std::string& c)
{
	std::vector<std::string> vec;
	std::string::size_type pos1 = 0, pos2 = str.find(c);
	while (std::string::npos != pos2)
	{
		std::string tmp = str.substr(pos1, pos2 - pos1);
		if (!tmp.empty())
		{
			vec.push_back(std::move(tmp));
		}

		pos1 = pos2 + c.size();
		pos2 = str.find(c, pos1);
	}
	if (pos1 < str.length())
	{
		vec.push_back(str.substr(pos1));
	}
	return vec;
}

std::string getPhoneType(CARDTYPE type)
{
	assert(type > UNKNOWN && type <= CMCC_V);

	switch (type)
	{
	case UNKNOWN:
		return std::string("未知");
	case CMCC:
		return std::string("中国移动");
	case CUCC:
		return std::string("中国联通");
	case CTCC:
		return std::string("中国电信");
	case CTCC_V:
		return std::string("电信虚拟运营商");
	case CUCC_V:
		return std::string("联通虚拟运营商");
	case CMCC_V:
		return std::string("移动虚拟运营商");
	default:
		return std::string();
	}
}

PhoneData::PhoneData()
{
	std::wstring path = L"D:\\XEngine_PhoneData\\Data\\phone.dat";
	std::ifstream stream(path, std::ios::binary);
	if (!stream.is_open())
	{
		head = nullptr;
		return;
	}

	buffer = std::vector<char>(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
	head = reinterpret_cast<DataHead*>(buffer.data());
	recordCount = (buffer.size() - head->offset) / PHONE_INDEX_LENGTH;
}

PhoneInfo PhoneData::_lookUp(uint32_t phone7) const
{
	int i = 0;
	size_t left = 0;
	size_t currentOffset = head->offset;

	FILE* pSt_File = fopen("D:\\XEngine_PhoneData\\Data\\Source.txt", "wb");

	int nLen = head->offset - 9;
	XCHAR* ptszMSGBuffer = (XCHAR*)malloc(XENGINE_MEMORY_SIZE_MAX);
	memset(ptszMSGBuffer, '\0', XENGINE_MEMORY_SIZE_MAX);

	BaseLib_Charset_UTFToAnsi(buffer.data() + 8, ptszMSGBuffer, &nLen);
	fwrite(ptszMSGBuffer, 1, nLen, pSt_File);
	fwrite("\r\n", 1, 2, pSt_File);

	while (left <= recordCount)
	{
		if (currentOffset >= buffer.size())
		{
			break;
		}

		auto _buffer = std::vector<char>(buffer.cbegin() + currentOffset, buffer.cbegin() + currentOffset + PHONE_INDEX_LENGTH);
		Record* _record = reinterpret_cast<Record*>(_buffer.data());

		std::string recordContent = getRecordContent(buffer, _record->offset);
		std::vector <std::string> contents = ssplit(recordContent, std::string("|"));
		PhoneInfo info;
		info.type = static_cast<CARDTYPE>(_record->type);
		info.phone = _record->phone;
		info.province = contents[PROVINCE];
		info.city = contents[CITY];
		info.zipCode = contents[ZIPCODE];
		info.areaCode = contents[AREACODE];

		int nPLen = info.province.length();
		int nCLen = info.city.length();
		XCHAR tszProvinceStr[64] = {};
		XCHAR tszCityStr[64] = {};

		BaseLib_Charset_UTFToAnsi(info.province.c_str(), tszProvinceStr, &nPLen);
		BaseLib_Charset_UTFToAnsi(info.city.c_str(), tszCityStr, &nCLen);

		XCHAR tszMSGBuffer[XPATH_MAX] = {};
		int nRet = sprintf(tszMSGBuffer, "%d,%d,%d,%s,%s,%s,0\r\n", i++, info.phone, info.type, tszProvinceStr, tszCityStr, info.areaCode.c_str());
		fwrite(tszMSGBuffer, 1, nRet, pSt_File);

		currentOffset += PHONE_INDEX_LENGTH;
	}
	fclose(pSt_File);

	return PhoneInfo();
}

std::string PhoneData::getRecordContent(const std::vector<char>& buffer, size_t startOffset)
{
	size_t endOffset = std::find(buffer.cbegin() + startOffset, buffer.cend(), '\0') - buffer.cbegin();
	return std::string(buffer.cbegin() + startOffset, buffer.cbegin() + endOffset);
}

int main()
{
#ifndef _DEBUG
	if (setlocale(LC_ALL, ".UTF8") == NULL)
	{
		return -1;
	}
#endif
	PhoneData data;
	auto info = data._lookUp(0);

	return 0;
}