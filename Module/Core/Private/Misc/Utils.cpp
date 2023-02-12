#include "Core/CorePCH.h"
#include "Misc/Utils.h"

std::wstring Utils::StringToWideString(const std::string& str)
{
	if (str.length() == 0)
	{
		return {};
	}

	std::wstring ret;
	const int32 len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), static_cast<int32>(str.length()), nullptr, 0);
	checkMsg(len > 0, TEXT("MultiByteToWideChar Failed. ErrorCode = {}"), GetLastError());

	ret.resize(len);
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), static_cast<int32>(str.length()), ret.data(), len);

	return ret;
}

std::string Utils::WideStringToString(const std::wstring& str)
{
	if (str.length() == 0)
	{
		return {};
	}

	std::string ret;
	const int32 len = WideCharToMultiByte(CP_ACP, 0, str.c_str(), static_cast<int32>(str.length()), nullptr, 0, nullptr, nullptr);
	checkMsg(len > 0, TEXT("WideCharToMultiByte Failed. ErrorCode = {}"), GetLastError());

	ret.resize(len);
	WideCharToMultiByte(CP_ACP, 0, str.c_str(), static_cast<int32>(str.length()), ret.data(), len, nullptr, nullptr);

	return ret;
}
