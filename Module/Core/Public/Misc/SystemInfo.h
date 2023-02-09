#pragma once

#include "Core/CoreDLL.h"

class CORE_API SystemInfo
{
public:
	NON_INSTANTIABLE(SystemInfo)

	static std::wstring GetProcessorName();

	static std::wstring GetOperatingSystemName();

	
};

