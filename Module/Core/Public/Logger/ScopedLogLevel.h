#pragma once

#include "Core/CoreDLL.h"
#include "Logger/LogLevel.h"

class CORE_API ScopedLogLevel final
{
public:
	explicit ScopedLogLevel(ELogLevel level);
	~ScopedLogLevel();

private:
	ELogLevel mCachedLevel;
};

#define SCOPED_LOG_LEVEL(level) ScopedLogLevel sll(level)
