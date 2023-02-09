#pragma once

#include "Logger/LoggerDLL.h"
#include "Logger/LogLevel.h"

class LOGGER_API ScopedLogLevel final
{
public:
	explicit ScopedLogLevel(ELogLevel level);
	~ScopedLogLevel();

private:
	ELogLevel mCachedLevel;
};

#define SCOPED_LOG_LEVEL(level) ScopedLogLevel sll(level)
