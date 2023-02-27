#pragma once

#include <filesystem>
#include "Core/CoreExport.h"

using Path = std::filesystem::path;

class CORE_API Paths
{
public:
	NON_INSTANTIABLE(Paths)
	
	static Path GetLogDir();

	static Path GetEngineContentDir();

	static Path GetUserContentDir();

	static Path GetConfigDir();
	
	static Path GetEngineDir();

	static Path GetBinariesDir();

private:
	static Path getContentDir();
};
