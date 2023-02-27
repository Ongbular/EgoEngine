#pragma once

#define SI_CONVERT_GENERIC
#include "simpleini/SimpleIni.h"

class ConfigManagerImpl
{
public:
	ConfigManagerImpl();
	~ConfigManagerImpl();

	void LoadConfigFiles();

private:
	std::unordered_map<std::wstring, CSimpleIniA> mConfigFiles;
};

