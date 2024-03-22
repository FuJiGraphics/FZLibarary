#include "pch.h"
#include "LogHelper.h"

// ref spdlog
#include "spdlog/sinks/stdout_color_sinks.h"

namespace FZLib {

	std::shared_ptr<spdlog::logger>		LogSystem::s_pLogger = nullptr;
	std::string							LogSystem::s_currFormat = "%^[FILE:%s][LINE:%#][CALL:%!]{ %T }";
	std::string							LogSystem::s_prevFormat = "%^[FILE:%s][LINE:%#][CALL:%!]{ %T }";

	bool LogSystem::Initialize()
	{
		if (s_pLogger != nullptr)
			return (false);
		auto logger = spdlog::stdout_color_mt("FZLogger");
		s_pLogger = logger;
		LogSystem::SetPattern(s_currFormat);
		logger->set_level(spdlog::level::trace);
		return (true);
	}

	void LogSystem::ClearPattern()
	{
		LogSystem::Initialize();
		s_prevFormat = s_currFormat;
		s_currFormat = "%^[FILE:%s][LINE:%#][CALL:%!]{ %T }";
	}

	void LogSystem::RevertFormat()
	{
		LogSystem::SetPattern(LogSystem::GetPrevFormat());
	}

	void LogSystem::SetPattern(const std::string& format)
	{
		LogSystem::Initialize();
		s_prevFormat = s_currFormat;
		s_currFormat = format;
		spdlog::set_pattern(s_currFormat);
	}

	void LogSystem::AddPattern(const std::string& format)
	{
		s_currFormat += format;
		LogSystem::SetPattern(s_currFormat);
	}

	void LogSystem::DelPattern(const std::string& format)
	{
		if (auto pos = s_currFormat.rfind(format) != std::string::npos)
		{
			s_currFormat.erase(pos, format.size());
			LogSystem::SetPattern(s_currFormat);
		}
	}

	std::shared_ptr<spdlog::logger> LogSystem::GetLogger()
	{
		LogSystem::Initialize();
		return s_pLogger;
	}

	std::string LogSystem::GetCurrFormat()
	{
		return (s_currFormat);
	}

	std::string LogSystem::GetPrevFormat()
	{
		return (s_prevFormat);
	}
}
