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
		 * @brief	���ڿ� ó���� ���� ���� Ŭ����
		 */
		class FZLIB_API StringHelper
		{
			/**
			 * @brief	std::string�� LPCWSTR�� ��ȯ
			 * @param[in]	str	: ��ȯ��ų �Ķ����
			 * @return	std::wstring	: ��ȯ�� LPCWSTR Ÿ���� wstring 
			 */
			static std::wstring StringToLPCWSTR(const std::string& str);

		};

	}	// namespace FZLib
}	// extern
#endif