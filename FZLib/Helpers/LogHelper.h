#pragma once
#ifndef __FZ_LIBRARY_LOG_HELPER__
#define __FZ_LIBRARY_LOG_HELPER__

#ifdef FZLIB_EXPORTS
#define FZLIB_API __declspec(dllexport)
#else
#define FZLIB_API __declspec(dllimport)
#endif

#include "spdlog/spdlog.h"

#include <memory>
#include <utility>
#include <string>

extern "C" {
	namespace FZLib {

		class FZLIB_API LogSystem
		{
		public:
			enum class Pattern {
				Blank, Simple, LineScan, FunctionScan
			};

			struct Format {
				static const std::string&&	
					DEFAULT;
			};

		public:
			static bool Initialize();
			static void ClearPattern();

			static void SetPattern(Pattern p);
			static void SetPattern(const std::string& format);
			static void AddPattern(const std::string& format);
			static void DelPattern(const std::string& format);

			static void SetTemporaryFormat(const std::string& format);
		public:
			static std::shared_ptr<spdlog::logger>	GetLogger();
			static std::string&						GetLogFormat();

		private:
			static std::string						s_strLogFormat;
			static std::shared_ptr<spdlog::logger>	s_pLogger;
		};

#pragma region Defines 
	#define FZLOG_TRACE(...)		SPDLOG_LOGGER_CALL( FZLib::LogSystem::GetLogger(), spdlog::level::trace, __VA_ARGS__);
	#define FZLOG_DEBUG(...)		SPDLOG_LOGGER_CALL( FZLib::LogSystem::GetLogger(), spdlog::level::debug, __VA_ARGS__);
	#define FZLOG_INFO(...)			SPDLOG_LOGGER_CALL( FZLib::LogSystem::GetLogger(), spdlog::level::info, __VA_ARGS__);
	#define FZLOG_WARN(...)			SPDLOG_LOGGER_CALL( FZLib::LogSystem::GetLogger(), spdlog::level::warn, __VA_ARGS__);
	#define FZLOG_ERROR(...)		SPDLOG_LOGGER_CALL( FZLib::LogSystem::GetLogger(), spdlog::level::err, __VA_ARGS__);
	#define FZLOG_CRITICAL(...)		SPDLOG_LOGGER_CALL( FZLib::LogSystem::GetLogger(), spdlog::level::critical, __VA_ARGS__);

// for debug modes
#if defined(DEBUG) || defined(_DEBUG)
	#define FZLOG_FAILED(boolean_value)						\
{															\
	if(!boolean_value)										\
	{														\
		LogSystem::SetTemporaryFormat(						\
		LogSystem::Format::DEFAULT);						\
		FZLOG_CRITICAL("Failed to execute operation.");		\
		LogSystem::SetPattern(LogSystem::GetLogFormat());	\
	}														\
}
#else
	#define FZLOG_FAILED(boolean_value)
#endif
#pragma endregion 

	} // namespace FZLib
} // extern "C"
#endif
