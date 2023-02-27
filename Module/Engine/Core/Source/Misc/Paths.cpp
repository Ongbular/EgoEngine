#include "PCH.h"
#include "Misc/Paths.h"

Path Paths::GetLogDir()
{
	return GetEngineDir() / TEXT("Logs");
}

Path Paths::GetEngineContentDir()
{
	return getContentDir() / TEXT("Logs");
}

Path Paths::GetUserContentDir()
{
	return getContentDir() / TEXT("Logs");
}

Path Paths::GetConfigDir()
{
	return GetEngineDir() / TEXT("Config");
}

Path Paths::GetEngineDir()
{
	static const std::filesystem::path engineDir = GetBinariesDir().parent_path().parent_path();
	return engineDir;
}

Path Paths::GetBinariesDir()
{
	static const Path binariesDir = std::filesystem::current_path();
	return binariesDir;
}

Path Paths::getContentDir()
{
	return GetEngineDir() / TEXT("Content");
}
