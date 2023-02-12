#include "Core/CorePCH.h"
#include "Config/ConfigManager.h"
#include "ConfigManagerImpl.h"

ConfigManager::~ConfigManager() = default;

ConfigManager& ConfigManager::Get()
{
	static ConfigManager instance;

	return instance;
}

void ConfigManager::LoadConfigFiles()
{
	mImpl->LoadConfigFiles();
}

std::vector<IniSection> ConfigManager::GetSections(const std::wstring& namePattern)
{
	return {};
}

ConfigManager::ConfigManager()
{
	mImpl = std::make_unique<ConfigManagerImpl>();
}
