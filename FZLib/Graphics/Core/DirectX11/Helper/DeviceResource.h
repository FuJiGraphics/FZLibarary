/*********************************************************************
 * @file   DeviceManager.h
 * @brief  디바이스 생성 및 관리 컨테이너 매니저
 * 
 * @author FuJiGraphics
 * @date   2024/03/12
 *********************************************************************/

#pragma once
#ifndef __FZ_LIBRARY_DEVICEMANAGER_DIRECTX11__
#define __FZ_LIBRARY_DEVICEMANAGER_DIRECTX11__

#include <Graphics/Core/DirectX11/CoreRef.h>

namespace FZLib {
	namespace DirectX11 {
		namespace Helper {

			class DeviceResource
			{
			public:
				DeviceResource();
				~DeviceResource();

			public:
				bool	StartUp(const HWND& hwnd, int width, int height);
				bool	Shutdown();

			public:
				ID3D11Device&			GetDevice()	const;
				ID3D11DeviceContext&	GetDeviceContext() const;
				float					GetAspectRatio() const;
				unsigned int			GetWidth() const;
				unsigned int			GetHeight() const;
				HWND					GetWindowHandle() const;
				bool					SetFullScreen();
				bool					SetWindowed();

			private: // Generate Resource Interface
				bool	CreateDeviceAndSwapChain(const HWND& hwnd, int bufWidth, int bufHeight);
				bool	CreateBackBufferAndViewport();
				bool	ResetBackBuffer();
				bool	EnumerateAdapters(std::vector<IDXGIAdapter*>* out);
				bool	ReleaseBackBuffer();

			private:
				Microsoft::WRL::ComPtr<ID3D11Device>			m_Device;
				Microsoft::WRL::ComPtr<ID3D11DeviceContext>		m_DeviceContext;
				Microsoft::WRL::ComPtr<IDXGISwapChain>			m_SwapChain;
				Microsoft::WRL::ComPtr<ID3D11Texture2D>			m_BackBuffer;
				Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_RenderTarget;
				Microsoft::WRL::ComPtr<ID3D11Texture2D>         m_DepthStencil;
				Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_DepthStencilView;
				D3D_FEATURE_LEVEL								m_FeatureLevel;
				D3D11_TEXTURE2D_DESC							m_bbDesc;
				D3D11_VIEWPORT									m_Viewport;
				bool											m_Initialized;
			};

		} // namespace Helper
	} // namespace DirectX11
} // namespace FZLib

#endif
