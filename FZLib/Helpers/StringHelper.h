#pragma once
#ifndef __FZ_LIBRARY_STRING_HELPER__
#define __FZ_LIBRARY_STRING_HELPER__

#ifdef FZLIB_EXPORTS
	#define FZLIB_API __declspec(dllexport)
#else
	#define FZLIB_API __declspec(dllimport)
		#ifdef __DEBUG
			#pragma comment (lib, "../Dist/lib/Debug/x86_64/FZLib.lib")
		#else
			#pragma comment (lib, "../Dist/lib/Release/x86_64/FZLib.lib")
		#endif
#endif

extern "C" {
	namespace FZLib {
		namespace StringHelper {

			/**
			 * @brief	std::string을 LPCWSTR로 변환
			 * @param[in]	str	: 변환시킬 파라미터
			 * @return	std::wstring	: 변환된 LPCWSTR 타입의 wstring
			 */
			std::wstring FZLIB_API StringToLPCWSTR(const std::string& str);


		}	// namespace StringHelper
	}	// namespace FZLib
}	// extern
#endif