#include "PCH.h"
#include "Logger/Logger.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/ostream_sink.h"
#include "spdlog/sinks/basic_file_sink.h"

#define FILE_SINK_INDEX (0)
#define CONSOLE_SINK_INDEX (1)

static const char* gDedicatedLoggerName = "EngineLogger";
static Path gLoggingFilePath{};

std::shared_ptr<spdlog::logger> GetLoggerPtr()
{
	return spdlog::get(gDedicatedLoggerName);
}

spdlog::level::level_enum CastLevel(const ELogLevel level)
{
	return static_cast<spdlog::level::level_enum>(level);
}

void Logger::Initialize()
{
	static const std::string patternWithSymbol{ "[%Y-%m-%d %H:%M:%S.$e][%l]%!: %v" };

	assert(!mbInitialized);

	gLoggingFilePath = Paths::GetLogDir() / TEXT("EgoEngine-Running.log");
	if (std::filesystem::exists(gLoggingFilePath))
	{
		std::filesystem::remove(gLoggingFilePath);
	}

	auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(gLoggingFilePath);

	// spdlog::init_thread_pool(1024, 1);
	// const auto logger = std::make_shared<spdlog::async_logger>(gDedicatedLoggerName, fileSink, spdlog::thread_pool(), spdlog::async_overflow_policy::block);
	const auto logger = std::make_shared<spdlog::logger>(gDedicatedLoggerName, fileSink);
	assert(logger.get());

	spdlog::register_logger(logger);

	logger->flush_on(spdlog::level::info);
	logger->sinks()[FILE_SINK_INDEX]->set_pattern(patternWithSymbol);

	mbInitialized = true;
}

Path Logger::Deinitialize(const bool bAborted)
{
	static const std::string patternWithoutSymbol{ "[%Y-%m-%d %H:%M:%S.$e][%l] %v" };

	assert(mbInitialized);

	DeactivateConsoleSink();

	auto logger = GetLoggerPtr();
	logger->set_pattern(patternWithoutSymbol);

	const auto level = bAborted ? spdlog::level::level_enum::err : spdlog::level::level_enum::info;

	logger->log(spdlog::level::info, TEXT("Closing log file..."));
	logger.reset();
	
	spdlog::shutdown();

	assert(std::filesystem::exists(gLoggingFilePath));

	auto finalLogFilename = std::format(TEXT("EgoEngine-{}.log"), getNowTimeString());
	finalLogFilename = Paths::GetLogDir() / finalLogFilename;

	std::filesystem::rename(gLoggingFilePath, finalLogFilename);

	mbInitialized = false;
	return finalLogFilename;
}

void Logger::ActivateConsoleSink()
{
	if (isConsoleSinkActivated())
	{
		return;
	}

	// TODO: implementation
}

void Logger::DeactivateConsoleSink()
{
	if (!isConsoleSinkActivated())
	{
		return;
	}

	GetLoggerPtr()->sinks().pop_back();
}

void Logger::SetFileLogPattern(const char* pattern)
{
	const auto logger = GetLoggerPtr();

	assert(logger.get() && logger->sinks().size() == 1);
	logger->sinks()[FILE_SINK_INDEX]->set_pattern(pattern);
}

void Logger::SetConsoleLogPattern(const char* pattern)
{
	if (!isConsoleSinkActivated())
	{
		return;
	}

	GetLoggerPtr()->sinks()[CONSOLE_SINK_INDEX]->set_pattern(pattern);
}

void Logger::SetLevel(ELogLevel level)
{	
	GetLoggerPtr()->set_level(static_cast<spdlog::level::level_enum>(level));
}

ELogLevel Logger::GetLevel()
{
	return static_cast<ELogLevel>(GetLoggerPtr()->level());
}

void Logger::Log(const ELogLevel level, std::wstringstream& stream)
{
	constexpr uint32_t maxLogLength = 512;

	const auto logLevel = static_cast<spdlog::level::level_enum>(level);
	std::wstring line;
	line.reserve(maxLogLength);

	while (!stream.eof())
	{
		std::getline(stream, line);
		logImpl(nullptr, INVALID_VALUE, nullptr, level, line);
	}
}

void Logger::logImpl(const char* file, int line, const char* function, const ELogLevel level, const std::wstring& message)
{
	const auto logger = GetLoggerPtr();

	if (file == nullptr || line == INVALID_VALUE || function == nullptr)
	{
		logger->log(CastLevel(level), message);
	}

	logger->log({ file, line, function }, CastLevel(level), message);
}

std::wstring Logger::getNowTimeString()
{
	const auto timer = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	tm tBuff{};
	localtime_s(&tBuff, &timer);  // NOLINT(cert-err33-c)

	std::wstringstream ss;
	ss << std::put_time(&tBuff, TEXT("%Y.%m.%d-%H.%M.%S"));

	return ss.str();
}

bool Logger::isConsoleSinkActivated()
{
	const auto logger = GetLoggerPtr();
	assert(logger.get());

	return logger->sinks().size() != CONSOLE_SINK_INDEX;
}
