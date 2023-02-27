#include "PCH.h"
#include "Logger/ScopedLogLevel.h"
#include "Logger/Logger.h"

ScopedLogLevel::ScopedLogLevel(const ELogLevel level)
	: mCachedLevel(Logger::GetLevel())
{
	Logger::SetLevel(level);
}

ScopedLogLevel::~ScopedLogLevel()
{
	Logger::SetLevel(mCachedLevel);
}
