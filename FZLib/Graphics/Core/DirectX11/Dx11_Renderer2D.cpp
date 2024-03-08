/*********************************************************************
 * @file   Dx11_Renderer2D.cpp
 * @brief  2D 렌더링을 위한 그래픽 라이브러리
 * 
 * @author FuJiGraphics
 * @date   2024/03/07
 *********************************************************************/

#include <pch.h>
#include "Dx11_Renderer2D.h"

namespace FZLib {

	Dx11_Renderer2D::~Dx11_Renderer2D()
	{
		// Empty
	}

	bool Dx11_Renderer2D::StartUp(const HWND& hwnd, int width, int height)
	{
		bool result = false;
		m_Hwnd = hwnd;
		m_Width = width;
		m_Height = height;

		// Init Device Resources
		result = m_DeviceManager->StartUp(m_Hwnd, m_Width, m_Height);
		return result;
	}

	bool Dx11_Renderer2D::Shutdown()
	{
		bool result = false;
		result = m_DeviceManager->Shutdown();
		return result;
	}

	std::string Dx11_Renderer2D::GetDeviceInfo()
	{
		return Specification::DirectX11;
	}

	void Dx11_Renderer2D::RenderFrame()
	{

	}


} // namespace FZLib