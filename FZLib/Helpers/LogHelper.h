#pragma once
#ifndef __FZ_LIBRARY_LOG_HELPER__
#define __FZ_LIBRARY_LOG_HELPER__

#ifdef FZLIB_USAGE_DLL
#ifdef FZLIB_EXPORTS
#define FZLIB_API __declspec(dllexport)
#else
#define FZLIB_API __declspec(dllimport)
#endif
#else
#define FZLIB_API
#endif

#include "spdlog/spdlog.h"

#include <memory>
#include <utility>
#include <string>

namespace FZLib {

	class FZLIB_API LogSystem
	{
	public:
		static bool Initialize();
		static void ClearPattern();
		static void	RevertFormat();

		static void SetPattern(const std::string& format);
		static void AddPattern(const std::string& format);
		static void DelPattern(const std::string& format);
	public:
		static std::shared_ptr<spdlog::logger>	GetLogger();
		static std::string						GetCurrFormat();
		static std::string						GetPrevFormat();

	private:
		static std::string						s_prevFormat;
		static std::string						s_currFormat;
		static std::shared_ptr<spdlog::logger>	s_pLogger;
	};

#pragma region Defines 
#define FZLOG_TRACE(...)		SPDLOG_LOGGER_CALL( FZLib::LogSystem::GetLogger(), spdlog::level::trace, __VA_ARGS__);
#define FZLOG_DEBUG(...)		SPDLOG_LOGGER_CALL( FZLib::LogSystem::GetLogger(), spdlog::level::debug, __VA_ARGS__);
#define FZLOG_INFO(...)			SPDLOG_LOGGER_CALL( FZLib::LogSystem::GetLogger(), spdlog::level::info, __VA_ARGS__);
#define FZLOG_WARN(...)			SPDLOG_LOGGER_CALL( FZLib::LogSystem::GetLogger(), spdlog::level::warn, __VA_ARGS__);
#define FZLOG_ERROR(...)		SPDLOG_LOGGER_CALL( FZLib::LogSystem::GetLogger(), spdlog::level::err, __VA_ARGS__);
#define FZLOG_CRITICAL(...)		SPDLOG_LOGGER_CALL( FZLib::LogSystem::GetLogger(), spdlog::level::critical, __VA_ARGS__);

#if defined(DEBUG) || defined(_DEBUG)

	template <typename... Args>
	static bool LOG_SWITCHING__(bool obj, const char* fmt, Args&&...args)
	{
		if (obj == false)
		{
			FZLib::LogSystem::SetPattern("[%T][%s:%#][%!]\n %^%v%$");
			FZLib::LogSystem::GetLogger()->log(spdlog::source_loc{ __FILE__, __LINE__, SPDLOG_FUNCTION },
											   spdlog::level::info,
											   fmt, std::forward<Args>(args)...);
			FZLib::LogSystem::RevertFormat();
			return (true);
		}
		return (false);
	}

	#define FZLOG_SUCCEEDED(boolean_value, ...)	FZLib::LOG_SWITCHING__(!boolean_value, __VA_ARGS__)
	#define FZLOG_FAILED(boolean_value, ...)	FZLib::LOG_SWITCHING__(boolean_value, __VA_ARGS__)
#else
	#define FZLOG_SUCCEEDED(boolean_value)	boolean_value;
	#define FZLOG_FAILED(boolean_value)		boolean_value;
#endif

#pragma endregion 
} // namespace FZLib
#endif
