#include "pch.h"
#include "LogHelper.h"

// ref spdlog
#include "spdlog/sinks/stdout_color_sinks.h"

namespace FZLib {

	std::shared_ptr<spdlog::logger> LogSystem::s_pLogger = nullptr;

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
		SetPattern(Pattern::Simple);
	}

	void LogSystem::SetPattern(Pattern p)
	{
		switch (p)
		{
			case Pattern::Simple:
				spdlog::set_pattern("%^[%T] %n: %v%$");
				break;
			case Pattern::LineScanner:
				spdlog::set_pattern("%^[%T][%s][Line:%#] %n: %v%$");
				break;
			case Pattern::Details:
				spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
				break;
		}
	}

	void LogSystem::SetPattern(const std::string& format)
	{
		LogSystem::SetPattern(format);
	}

	std::shared_ptr<spdlog::logger> LogSystem::GetLogger()
	{
		LogSystem::Initialize();
		return s_pLogger;
	}

}
