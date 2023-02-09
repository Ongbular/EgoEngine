#include "Core/CorePCH.h"
#include "ConfigManagerImpl.h"
#include "Misc/EnginePaths.h"

namespace fs = std::filesystem;

ConfigManagerImpl::ConfigManagerImpl() = default;
ConfigManagerImpl::~ConfigManagerImpl() = default;

void ConfigManagerImpl::LoadConfigFiles()
{
	static bool bLoaded = false;
	if (bLoaded)
	{
		return;
	}

	const auto configDir = EnginePaths::GetConfigDir();
	if (!fs::exists(configDir))
	{
		return;
	}

	fs::directory_iterator iter(configDir);
	while (iter != fs::end(iter))
	{
		const auto& entryPath = iter->path();

		if (entryPath.has_extension() && entryPath.extension() == TEXT(".ini"))
		{
			const auto& nameBegin = entryPath.filename().wstring().cbegin();
			const auto& nameEnd = entryPath.filename().wstring().cend() - 4;

			std::wstring configName(nameBegin, nameEnd);
			mConfigFiles[configName].LoadFile(entryPath.c_str());
		}
	}

	bLoaded = true;
}
