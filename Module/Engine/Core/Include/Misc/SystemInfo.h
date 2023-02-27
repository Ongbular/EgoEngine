#pragma once

#include "Core/CoreExport.h"

class CORE_API SystemInfo
{
public:
	NON_INSTANTIABLE(SystemInfo)

	static std::wstring GetProcessorName();

	static std::wstring GetOperatingSystemName();

	
};

