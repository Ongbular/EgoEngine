#pragma once

#include <filesystem>
#include "Core/CoreDLL.h"

class CORE_API EnginePaths
{
public:
	NON_INSTANTIABLE(EnginePaths)
	
	static std::filesystem::path GetLogDir();

	static std::filesystem::path GetEngineContentDir();

	static std::filesystem::path GetUserContentDir();

	static std::filesystem::path GetConfigDir();

	static std::filesystem::path GetWorkingDir();

private:
	static std::filesystem::path getContentDir();
};
