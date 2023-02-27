#pragma once

#include "Core/CoreExport.h"
#include "Logger/LogLevel.h"
#include "Misc/Paths.h"

class CORE_API Logger final
{
public:
	Logger() = delete;
	~Logger() = delete;

	static void Initialize();

	static Path Deinitialize(bool bAborted);

	static void ActivateConsoleSink();

	static void DeactivateConsoleSink();

	static void SetFileLogPattern(const char* pattern);

	static void SetConsoleLogPattern(const char* pattern);

	static void SetLevel(ELogLevel level);

	static ELogLevel GetLevel();
	
	template <typename... TArgs>
	static void Log(const char* file, int line, const char* function, ELogLevel level, std::_Fmt_wstring<TArgs...> fmt, TArgs&&... args);

	template <typename... TArgs>
	static void Log(ELogLevel level, std::_Fmt_wstring<TArgs...> fmt, TArgs&&... args);
	
	static void Log(ELogLevel level, std::wstringstream& stream);

private:
	static void logImpl(const char* file, int line, const char* function, ELogLevel level, const std::wstring& message);
	
	static std::wstring getNowTimeString();

	static bool isConsoleSinkActivated();

	inline static bool mbInitialized = false;

public:
#define Trace(...)	Log(__FILE__, __LINE__, __FUNCTION__, ELogLevel::Trace, __VA_ARGS__)
#define Debug(...)	Log(__FILE__, __LINE__, __FUNCTION__, ELogLevel::Debug, __VA_ARGS__)
#define Info(...)	Log(__FILE__, __LINE__, __FUNCTION__, ELogLevel::Info, __VA_ARGS__)
#define Warn(...)	Log(__FILE__, __LINE__, __FUNCTION__, ELogLevel::Warn, __VA_ARGS__)
#define Error(...)	Log(__FILE__, __LINE__, __FUNCTION__, ELogLevel::Error, __VA_ARGS__)
#define Fatal(...)	Log(__FILE__, __LINE__, __FUNCTION__, ELogLevel::Fatal, __VA_ARGS__)
};

template <typename ... TArgs>
void Logger::Log(const char* file, int line, const char* function, ELogLevel level, std::_Fmt_wstring<TArgs...> fmt,
	TArgs&&... args)
{
	const auto message = std::format(fmt, std::forward<TArgs>(args)...);
	logImpl(file, line, function, level, message);
}

template <typename ... TArgs>
void Logger::Log(ELogLevel level, std::_Fmt_wstring<TArgs...> fmt, TArgs&&... args)
{
	const auto message = std::format(fmt, std::forward<TArgs>(args)...);
	logImpl(nullptr, INVALID_VALUE, nullptr, level, message);
}
