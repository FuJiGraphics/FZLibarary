/*****************************************************************//**
 * @file   DeviceManager.h
 * @brief  디바이스를 관리하는 클래스
 * 
 * @author cj@zv-lab.com
 * @date   2024/03/17
 *********************************************************************/

#pragma once
#ifndef __FZ_LIBRARY_DEVICEMANAGER_DIRECTX11__
#define __FZ_LIBRARY_DEVICEMANAGER_DIRECTX11__

#include "../../../gcr.h"
#include "../Device.h"

namespace FZLib {
	namespace DirectX11 {
		namespace Helpers {

			class FZLIB_API DeviceManager 
			{
			public:
				static DirectX11::Device*	CreateDevice(const std::string& dcName, HWND hwnd, int width, int height);
				static DirectX11::Device*	GetDevice(const std::string& dcName = std::string());
				static FZbool				ReleaseDevice(const std::string& dcName = std::string());

			private:
				static std::map<std::string, DirectX11::Device*> s_DeviceMap;
			};

		} // namespace Helper
	} // namespace DirectX11
} // namespace FZLib

#endif
