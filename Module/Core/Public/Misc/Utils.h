#pragma once

#include "Core/CoreDLL.h"

class CORE_API Utils
{
public:
	NON_INSTANTIABLE(Utils)

	static std::wstring StringToWideString(const std::string& str);

	static std::string WideStringToString(const std::wstring& str);
};

