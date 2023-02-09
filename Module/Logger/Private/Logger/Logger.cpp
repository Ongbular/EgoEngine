#include "Logger/LoggerPCH.h"
#include "Logger/Logger.h"
#include "spdlog/sinks/ostream_sink.h"
#include "spdlog/sinks/basic_file_sink.h"

#define FILE_SINK_INDEX (0)
#define CONSOLE_SINK_INDEX (1)

static const char* gDedicatedLoggerName = "EngineLogger";
static std::filesystem::path gLoggingFilePath{};
static const std::string gPatternWithSymbol{ "[%Y-%m-%d %H:%M:%S.$e][%l]%!: %v" };
static const std::string gPatternWithoutSymbol{ "[[%Y-%m-%d %H:%M:%S.$e]][%l] %v" };

void Logger::Initialize()
{
	assert(!mbInitialized);

	gLoggingFilePath = GetLogDir() / TEXT("OwlEngine-Running.log");
	assert(!std::filesystem::exists(gLoggingFilePath));

	auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(gLoggingFilePath);

	const auto logger = std::make_shared<spdlog::logger>(gDedicatedLoggerName, fileSink);
	logger->sinks()[FILE_SINK_INDEX]->set_pattern(gPatternWithSymbol);

	spdlog::register_logger(logger);
	mbInitialized = true;
}

std::filesystem::path Logger::Deinitialize(const bool bAborted)
{
	assert(mbInitialized);

	DeactivateConsoleSink();

	const auto logger = getLoggerPtr();
	logger->set_pattern(gPatternWithoutSymbol);

	const auto level = bAborted ? spdlog::level::level_enum::err : spdlog::level::level_enum::info;

	logger->log(spdlog::level::info, TEXT("Closing log file..."));
	spdlog::drop(gDedicatedLoggerName);
	spdlog::shutdown();

	assert(std::filesystem::exists(gLoggingFilePath));

	auto finalLogFilename = std::format(TEXT("OwlEngine-{}.log"), getNowTimeString());
	finalLogFilename = GetLogDir() / finalLogFilename;

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

	getLoggerPtr()->sinks().pop_back();
}

void Logger::SetFileLogPattern(const char* pattern)
{
	const auto logger = getLoggerPtr();

	assert(logger.get() && logger->sinks().size() == 1);
	logger->sinks()[FILE_SINK_INDEX]->set_pattern(pattern);
}

void Logger::SetConsoleLogPattern(const char* pattern)
{
	if (!isConsoleSinkActivated())
	{
		return;
	}

	getLoggerPtr()->sinks()[CONSOLE_SINK_INDEX]->set_pattern(pattern);
}

void Logger::SetLevel(ELogLevel level)
{	
	getLoggerPtr()->set_level(static_cast<spdlog::level::level_enum>(level));
}

ELogLevel Logger::GetLevel()
{
	return static_cast<ELogLevel>(getLoggerPtr()->level());
}

std::filesystem::path Logger::GetLogDir()
{
	constexpr auto rootDir = std::filesystem::current_path().parent_path();
	return rootDir / TEXT("Logs");
}

void Logger::Log(const spdlog::source_loc sourceLoc, const ELogLevel level, std::wstringstream& stream)
{
	constexpr uint32_t maxLogLength = 512;

	const auto logLevel = static_cast<spdlog::level::level_enum>(level);
	std::wstring line;
	line.reserve(maxLogLength);

	while (!stream.eof())
	{
		std::getline(stream, line);
		getLoggerPtr()->log(sourceLoc, logLevel, line);
	}
}

void Logger::Log(const ELogLevel level, std::wstringstream& stream)
{
	Log({}, level, stream);
}

std::shared_ptr<spdlog::logger> Logger::getLoggerPtr()
{
	const auto ret = spdlog::get(gDedicatedLoggerName);
	assert(ret.get());

	return ret;
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
	const auto logger = getLoggerPtr();
	assert(logger.get());

	return logger->sinks().size() != CONSOLE_SINK_INDEX;
}
