/*********************************************************************
 * @file   Dx11_DeviceManager.h
 * @brief  디바이스 생성 및 관리 컨테이너 매니저
 * 
 * @author FuJiGraphics
 * @date   2024/03/07
 *********************************************************************/

#pragma once
#ifndef __FZ_LIBRARY_DEVICEMANAGER_DIRECTX11__
#define __FZ_LIBRARY_DEVICEMANAGER_DIRECTX11__

#include "Dx11_CoreRef.h"

namespace FZLib {

	class FZLIB_API DeviceManager 
	{
	public:
		static DeviceManager& GetInstance();

	private:
		DeviceManager();
		DeviceManager(const DeviceManager&) = delete;
	public: // Constructor and Destructor
		~DeviceManager();

	public:	// Device Initialize Interface
		bool					StartUp(const HWND& hwnd, int width, int height);
		bool					Shutdown();

	public:	// Setting device state and Getting MetaData interface
		ID3D11Device&			GetDevice()	const;
		ID3D11DeviceContext&	GetDeviceContext() const;
		float					GetAspectRatio() const;
		unsigned int			GetWidth() const;
		unsigned int			GetHeight() const;
		bool					SetFullScreen();
		bool					SetWindowed();

	public: // Generate Resource Interface
		bool					CreateDeviceAndSwapChain(int bufWidth, int bufHeight);
		bool					CreateBackBufferAndViewport();
		bool					ResetBackBuffer();
		bool					EnumerateAdapters(std::vector<IDXGIAdapter*>* out);
		bool					ReleaseBackBuffer();

	private: // static class singleton instance
		static std::shared_ptr<DeviceManager>	s_Instance;

	private: // Member Variables
		HWND					m_WindowHandle;
		bool					m_Initialized;

		//-----------------------------------------------------------------------------
		// Direct3D device
		//-----------------------------------------------------------------------------
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>		m_DeviceContext;
		Microsoft::WRL::ComPtr<ID3D11Device>			m_Device;
		Microsoft::WRL::ComPtr<IDXGISwapChain>			m_SwapChain;

		//-----------------------------------------------------------------------------
		// DXGI swap chain device resources
		//-----------------------------------------------------------------------------
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			m_BackBuffer;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_RenderTarget;

		//-----------------------------------------------------------------------------
		// Direct3D device resources for the depth stencil
		//-----------------------------------------------------------------------------
		Microsoft::WRL::ComPtr<ID3D11Texture2D>         m_DepthStencil;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_DepthStencilView;

		//-----------------------------------------------------------------------------
		// Direct3D device metadata and device resource metadata
		//-----------------------------------------------------------------------------
		D3D_FEATURE_LEVEL								m_FeatureLevel;
		D3D11_TEXTURE2D_DESC							m_bbDesc;
		D3D11_VIEWPORT									m_Viewport;
	};

} // namespace FZLib

#endif
