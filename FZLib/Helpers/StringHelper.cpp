#include "pch.h"
#include "StringHelper.h"

namespace FZLib {
	namespace StringHelper {

		std::wstring StringHelper::StringToLPCWSTR(const std::string& str)
		{
			int size;
			int slength = (int)str.length() + 1;
			size = MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, 0, 0);
			wchar_t* buf = new wchar_t[size];
			MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, buf, size);
			std::wstring wStr(buf);
			delete[] buf;
			buf = nullptr;
			return wStr;
		}

	}	// namespace StringHelper
}	// namespace FZLib
