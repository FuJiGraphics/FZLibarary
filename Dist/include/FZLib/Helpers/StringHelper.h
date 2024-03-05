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
		namespace StringHelper {

			/**
			 * @brief	std::string�� LPCWSTR�� ��ȯ
			 * @param[in]	str	: ��ȯ��ų �Ķ����
			 * @return	std::wstring	: ��ȯ�� LPCWSTR Ÿ���� wstring
			 */
			std::wstring FZLIB_API StringToLPCWSTR(const std::string& str);


		}	// namespace StringHelper
	}	// namespace FZLib
}	// extern
#endif