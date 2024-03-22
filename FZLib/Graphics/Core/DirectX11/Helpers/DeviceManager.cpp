#include "pch.h"
#include "DeviceManager.h"

namespace FZLib {
	namespace DirectX11 {
		namespace Helpers {

			std::map<std::string, DirectX11::Device*> DeviceManager::s_DeviceMap;

			DirectX11::Device* DeviceManager::CreateDevice(const std::string& dcName, HWND hwnd, int width, int height)
			{
				if (s_DeviceMap.find(dcName) != s_DeviceMap.end())
					return (nullptr);
				Device* pDevice = new Device(dcName, hwnd, width, height);
				s_DeviceMap.insert({ dcName, pDevice });
				return (s_DeviceMap[dcName]);
			}

			DirectX11::Device* DeviceManager::GetDevice(const std::string& dcName)
			{
				if (s_DeviceMap.find(dcName) == s_DeviceMap.end())
					return (nullptr);
				else if (dcName.size() < 1)
					return (s_DeviceMap.begin()->second);
				else
					return (s_DeviceMap[dcName]);
			}

			FZbool DeviceManager::ReleaseDevice(const std::string& dcName)
			{
				if (s_DeviceMap.find(dcName) == s_DeviceMap.end())
					return (FZfalse);
				else if (dcName.size() < 1)
				{
					s_DeviceMap.erase(s_DeviceMap.begin());
					return (FZtrue);
				}
				else if (s_DeviceMap.find(dcName)->first == dcName)
				{
					s_DeviceMap.erase(s_DeviceMap.find(dcName));
					return (FZtrue);
				}
				return (FZfalse);
			}

		} // namespace Helper
	} // namespace DirectX11
} // namespace FZLib