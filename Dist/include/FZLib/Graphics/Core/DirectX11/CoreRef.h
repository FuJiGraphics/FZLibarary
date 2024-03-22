/*********************************************************************
 * @file   Dx11_CoreRef.h
 * @brief  DirectX11 환경을 위한 헤더 및 라이브러리 모음
 *
 * @author FuJiGraphics
 * @date   2024/03/08
 *********************************************************************/

#pragma once
#ifndef __FZ_LIBRARY_DX11COREREFERENCES_DIRECTX11__
#define __FZ_LIBRARY_DX11COREREFERENCES_DIRECTX11__

#include <Graphics/gcr.h>
#include <d3d11.h>
#include <wrl.h>

// import d3d11.lib
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

// Debug mode
#include <Helpers/LogHelper.h>

// macros
#define SAFE_DELETE_COM(p)	\
{							\
	if(p)					\
	{						\
		p->Release();		\
		p = nullptr;		\
	}						\
}

// structures
namespace FZLib {
	namespace DirectX11 {
		
		struct WindowInfo {
			HWND	Handle	= NULL;
			FZuint	Width	= 0;
			FZuint	Height	= 0;
		};

		// Feature Levels
		struct ConfigFeatureLevel
		{
			constexpr static D3D_FEATURE_LEVEL Targets[] =
			{
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0,
				D3D_FEATURE_LEVEL_9_3,
				D3D_FEATURE_LEVEL_9_2,
				D3D_FEATURE_LEVEL_9_1
			};
			constexpr static unsigned int Nums = ARRAYSIZE(Targets);
		};

		struct DeviceResources
		{
			ID3D11Device*			Device					= nullptr;
			ID3D11DeviceContext*	DeviceContext			= nullptr;
			IDXGISwapChain*			SwapChain				= nullptr;
			ID3D11Texture2D*		SwapChainBackBuffer		= nullptr;
			ID3D11RenderTargetView*	RenderTargetView		= nullptr;
			ID3D11Texture2D*        DepthStencilBuffer		= nullptr;
			ID3D11DepthStencilView* DepthStencilView		= nullptr;
			D3D11_TEXTURE2D_DESC	BackBufferDesc;
			D3D_FEATURE_LEVEL		FeatureLevel;
			D3D11_VIEWPORT			Viewport;

			inline FZbool Release()
			{
				this->ReleaseBackBuffer();
				SAFE_DELETE_COM(this->SwapChain);
				SAFE_DELETE_COM(this->DeviceContext);
				SAFE_DELETE_COM(this->Device);
				return (this->Empty());
			}

			inline FZbool ReleaseBackBuffer()
			{
				SAFE_DELETE_COM(RenderTargetView);
				SAFE_DELETE_COM(SwapChainBackBuffer);
				SAFE_DELETE_COM(DepthStencilView);
				SAFE_DELETE_COM(DepthStencilBuffer);
				DeviceContext->Flush();
				return (FZtrue);
			}

			inline FZbool Empty()
			{
				return ((Device || DeviceContext ||
						SwapChain || SwapChainBackBuffer || RenderTargetView ||
						DepthStencilBuffer || DepthStencilView) ? FZfalse : FZtrue);
			}

			~DeviceResources() { this->Release(); }
		};
	} // namespace DirectX11
} // namespace FZLib

#endif
