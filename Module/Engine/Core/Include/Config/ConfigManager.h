#pragma once

#include "Core/CoreExport.h"
#include "Config/IniSection.h"

class CORE_API ConfigManager
{
public:
	~ConfigManager();

	static ConfigManager& Get();

	void LoadConfigFiles();

	std::vector<IniSection> GetSections(const std::wstring& namePattern);

private:
	ConfigManager();

	std::unique_ptr<class ConfigManagerImpl> mImpl;
};

