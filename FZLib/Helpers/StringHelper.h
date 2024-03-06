#pragma once
#ifndef __FZ_LIBRARY_STRING_HELPER__
#define __FZ_LIBRARY_STRING_HELPER__

#ifdef FZLIB_EXPORTS
	#define FZLIB_API __declspec(dllexport)
#else
	#define FZLIB_API __declspec(dllimport)
#endif

// Standard include headers
#include <string>

extern "C" {
	namespace FZLib {

		class FZLIB_API StringHelper
		{
		public:
			/**
			 * @brief	std::string을 LPCWSTR로 변환
			 * @param[in]	str	: 변환시킬 파라미터
			 * @return	std::wstring	: 변환된 LPCWSTR 타입의 wstring
			 */
			static std::wstring StringToWString(const std::string& str);
		};

	} // namespace FZLib
}
#endif