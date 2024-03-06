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

namespace FZLib {

	class FZLIB_API LogSystem
	{
	public:
		enum class Pattern
		{
			Simple, LineScanner, Details,
		};

	public:
		static bool Initialize();
		static void ClearPattern();

		static void SetPattern(Pattern p);
		static void SetPattern(const std::string& format);

	public:
		static std::shared_ptr<spdlog::logger> GetLogger();

	private:
		static std::shared_ptr<spdlog::logger> s_pLogger;
	};


#pragma region Defines 
#define FZLOG_TRACE(...)		FZLib::LogSystem::GetLogger()->trace( __VA_ARGS__ );
#define FZLOG_DEBUG(...)		FZLib::LogSystem::GetLogger()->debug( __VA_ARGS__ );
#define FZLOG_INFO(...)			FZLib::LogSystem::GetLogger()->info( __VA_ARGS__ );
#define FZLOG_WARN(...)			FZLib::LogSystem::GetLogger()->warn( __VA_ARGS__ );
#define FZLOG_ERROR(...)		FZLib::LogSystem::GetLogger()->error( __VA_ARGS__ );
#define FZLOG_CRITICAL(...)		FZLib::LogSystem::GetLogger()->critical( __VA_ARGS__ );
#pragma endregion 

}

#endif
