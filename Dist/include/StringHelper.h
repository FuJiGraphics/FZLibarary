#pragma once
#ifndef __FZ_LIBRARY_STRING_HELPER__
#define __FZ_LIBRARY_STRING_HELPER__

#ifdef FZLIB_EXPORTS
#define FZLIB_API __declspec(dllexport)
#else
#define FZLIB_API __declspec(dllimport)
#endif

extern "C" {
	namespace FZLib {

		/**
		 * @brief	문자열 처리에 대한 헬퍼 클래스
		 */
		class FZLIB_API StringHelper
		{
			/**
			 * @brief	std::string을 LPCWSTR로 변환
			 * @param[in]	str	: 변환시킬 파라미터
			 * @return	std::wstring	: 변환된 LPCWSTR 타입의 wstring 
			 */
			static std::wstring StringToLPCWSTR(const std::string& str);

		};

	}	// namespace FZLib
}	// extern
#endif