#pragma once

#include "Logger/LoggerDLL.h"
#include "Logger/LogLevel.h"

#include "spdlog/spdlog.h"
// #include "spdlog/async.h"

class LOGGER_API Logger final
{
public:
	Logger() = delete;
	~Logger() = delete;

	static void Initialize();

	static std::filesystem::path Deinitialize(bool bAborted);

	static void ActivateConsoleSink();

	static void DeactivateConsoleSink();

	static void SetFileLogPattern(const char* pattern);

	static void SetConsoleLogPattern(const char* pattern);

	static void SetLevel(ELogLevel level);

	static ELogLevel GetLevel();

	static std::filesystem::path GetLogDir();

	template <typename... TArgs>
	static void Log(spdlog::source_loc sourceLoc, ELogLevel level, const std::wstring_view&& fmt, TArgs&&... args);

	template <typename... TArgs>
	static void Log(ELogLevel level, const std::wstring_view&& fmt, TArgs&&... args);

	static void Log(spdlog::source_loc sourceLoc, ELogLevel level, std::wstringstream& stream);

	static void Log(ELogLevel level, std::wstringstream& stream);

private:
	static std::shared_ptr<spdlog::logger> getLoggerPtr();

	static std::wstring getNowTimeString();

	static bool isConsoleSinkActivated();

	inline static bool mbInitialized = false;

public:
#define Trace(...) Log({__FILE__, __LINE__, SPDLOG_FUNCTION}, ELogLevel::Trace, __VA_ARGS__)
#define Debug(...) Log({__FILE__, __LINE__, SPDLOG_FUNCTION}, ELogLevel::Debug, __VA_ARGS__)
#define Info(...) Log({__FILE__, __LINE__, SPDLOG_FUNCTION}, ELogLevel::Info, __VA_ARGS__)
#define Warn(...) Log({__FILE__, __LINE__, SPDLOG_FUNCTION}, ELogLevel::Warn, __VA_ARGS__)
#define Error(...) Log({__FILE__, __LINE__, SPDLOG_FUNCTION}, ELogLevel::Error, __VA_ARGS__)
#define Fatal(...) Log({__FILE__, __LINE__, SPDLOG_FUNCTION}, ELogLevel::Fatal, __VA_ARGS__)
};

template <typename ... TArgs>
void Logger::Log(const spdlog::source_loc sourceLoc, const ELogLevel level, const std::wstring_view&& fmt, TArgs&&... args)
{
	getLoggerPtr()->log(sourceLoc, static_cast<spdlog::level::level_enum>(level), fmt, args...);
}

template <typename ... TArgs>
void Logger::Log(const ELogLevel level, const std::wstring_view&& fmt, TArgs&&... args)
{
	getLoggerPtr()->log({}, static_cast<spdlog::level::level_enum>(level), fmt, args...);
}
