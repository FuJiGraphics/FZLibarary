/*********************************************************************
 * @file   Dx11_Renderer2D.cpp
 * @brief  2D 렌더링을 위한 그래픽 라이브러리
 * 
 * @author FuJiGraphics
 * @date   2024/03/07
 *********************************************************************/

#include <pch.h>
#include "Renderer2D.h"

namespace FZLib {
	namespace DirectX11 {

		int Renderer2D::s_RendererCount = 0;

		Renderer2D::Renderer2D(const std::string& name)
			: m_Name(name)
			, m_Hwnd(nullptr)
			, m_Width(0) ,m_Height(0)
			, m_Initialized(false)
		{
			++s_RendererCount;
			m_RenderID = std::to_string(s_RendererCount);
		}

		Renderer2D::Renderer2D(const std::string& name, const HWND& hwnd, int width, int height)
			: m_Name(name)
		{
			++s_RendererCount;
			m_RenderID = std::to_string(s_RendererCount);
			StartUp(hwnd, width, height);
		}

		Renderer2D::~Renderer2D()
		{
			--s_RendererCount;
			Shutdown();
		}

		bool Renderer2D::StartUp(const HWND& hwnd, int width, int height)
		{
			if (m_Initialized == true)
				return false;
			m_Initialized = true;

			m_Hwnd = hwnd;
			m_Width = width;
			m_Height = height;

			auto& dm = Helper::DeviceManager::GetInstance();
			return dm.GenerateDeviceResource(m_Name + m_RenderID, hwnd, width, height);
		}

		bool Renderer2D::Shutdown()
		{
			if (m_Initialized == false)
				return (false);
			m_Initialized = false;
			auto& dm = Helper::DeviceManager::GetInstance();
			dm.Release();
			return (true);
		}

		std::string Renderer2D::GetDeviceInfo()
		{
			return Specification::DirectX11;
		}

		void Renderer2D::RenderFrame()
		{

		}

		inline ID3D11Device* Renderer2D::GetDevice()
		{
			if (m_Initialized == false)
				return false;
			auto* deviceRes = Helper::DeviceManager::GetInstance().GetDeviceResource(m_Name + m_RenderID);
			return (deviceRes != nullptr) ? &deviceRes->GetDevice() : nullptr;
		}

		inline ID3D11DeviceContext* Renderer2D::GetDeviceContext()
		{
			if (m_Initialized == false)
				return false;
			auto* deviceRes = Helper::DeviceManager::GetInstance().GetDeviceResource(m_Name + m_RenderID);
			return (deviceRes != nullptr) ? &deviceRes->GetDeviceContext() : nullptr;
		}

	} // namespace DirectX11
} // namespace FZLib