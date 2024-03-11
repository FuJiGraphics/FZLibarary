/*********************************************************************
 * @file   Dx11_Renderer2D.h
 * @brief  2D 렌더링을 위한 그래픽 라이브러리
 * 
 * @author FuJiGraphics
 * @date   2024/03/07
 *********************************************************************/

#pragma once
#ifndef __FZ_LIBRARY_RENDERER2D_DIRECTX11__
#define __FZ_LIBRARY_RENDERER2D_DIRECTX11__

#include "Dx11_CoreRef.h"
#include "Dx11_DeviceManager.h"
#include <Graphics/Core/Renderer2D.h>

namespace FZLib {

	class FZLIB_API Dx11_Renderer2D : public Renderer2D
	{
	public: // Constructor and Destructor
		Dx11_Renderer2D() = default;
		virtual ~Dx11_Renderer2D();

	public: // Setup Devices in 2D Renderer
		virtual bool StartUp(const HWND& hwnd, int width, int height) final;
		virtual bool Shutdown() final;

	public: // Getter Setter Interface
		virtual std::string GetDeviceInfo() final;

	public: // Generic Interface
		virtual void RenderFrame() final;

	private:
		//-----------------------------------------------------------------------------
		// Renderer Metadata
		//-----------------------------------------------------------------------------
		HWND	m_Hwnd;
		int		m_Width, m_Height;
	};

} // namespace FZLib

#endif
