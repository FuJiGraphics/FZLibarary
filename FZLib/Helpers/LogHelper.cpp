#include "pch.h"
#include "LogHelper.h"

// ref spdlog
#include "spdlog/sinks/stdout_color_sinks.h"

namespace FZLib {

	std::shared_ptr<spdlog::logger>	LogSystem::s_pLogger = nullptr;
	std::string						LogSystem::s_strLogFormat = LogSystem::Format::TEXT;

	/*const std::string&&
		LogSystem::Format::SPACE	= " ",
		LogSystem::Format::TEXT		= "%v%$",
		LogSystem::Format::COLOR	= "%^",
		LogSystem::Format::ASSIGN	= ": ",
		LogSystem::Format::NAME		= "[Logger:%n]",
		LogSystem::Format::LINE		= "[Line:%#]",
		LogSystem::Format::FILE		= "[%s]",
		LogSystem::Format::FUNC		= "[Location:%!]",
		LogSystem::Format::YEAR		= "[%Y]",
		LogSystem::Format::MONTH	= "[%B]",
		LogSystem::Format::DAY		= "[%A]",
		LogSystem::Format::TIME		= "[%T]";*/

	const std::string&& LogSystem::Format::DEFAULT = "%^[FILE:%s][LINE:%#][CALL:%!]{ %T }";

	bool LogSystem::Initialize()
	{
		if (s_pLogger != nullptr)
			return false;
		auto logger = spdlog::stdout_color_mt("FZLogger");
		s_pLogger = logger;
		LogSystem::SetPattern(Pattern::Simple);
		logger->set_level(spdlog::level::trace);
		return true;
	}

	void LogSystem::ClearPattern()
	{
		LogSystem::Initialize();
		LogSystem::SetPattern(Pattern::Blank);
	}

	void LogSystem::SetPattern(Pattern p)
	{
		LogSystem::Initialize();
		switch (p)
		{
			case Pattern::Blank:		
				break;
			case Pattern::Simple:		
				break;
			case Pattern::LineScan:		
				break;
			case Pattern::FunctionScan:	
				break;
		}
		spdlog::set_pattern(s_strLogFormat);
	}

	void LogSystem::SetPattern(const std::string& format)
	{
		LogSystem::Initialize();
		LogSystem::s_strLogFormat = format;
		spdlog::set_pattern(format);
	}

	void LogSystem::AddPattern(const std::string& format)
	{
		s_strLogFormat += format;
	}

	void LogSystem::DelPattern(const std::string& format)
	{
		if (auto pos = s_strLogFormat.rfind(format) != std::string::npos)
		{
			s_strLogFormat.erase(pos, format.size());
		}
	}

	void LogSystem::SetTemporaryFormat(const std::string& format)
	{
		spdlog::set_pattern(format);
	}

	std::shared_ptr<spdlog::logger> LogSystem::GetLogger()
	{
		LogSystem::Initialize();
		return s_pLogger;
	}
	std::string & LogSystem::GetLogFormat()
	{
		return (s_strLogFormat);
	}
}
