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
#ifdef _DEBUG
	#include <Helpers/LogHelper.h>
#endif

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
			HWND	Handle;
			FZuint	Width;
			FZuint	Height;
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
			D3D_FEATURE_LEVEL		FeatureLevel;

			inline FZbool Release()
			{
				SAFE_DELETE_COM(this->Device);
				SAFE_DELETE_COM(this->DeviceContext);
				SAFE_DELETE_COM(this->SwapChain);
				SAFE_DELETE_COM(this->SwapChainBackBuffer);
				SAFE_DELETE_COM(this->RenderTargetView);
				SAFE_DELETE_COM(this->DepthStencilBuffer);
				SAFE_DELETE_COM(this->DepthStencilView);
				return ((this->Empty()) ? true : false);
			}

			inline FZbool Empty()
			{
				return ((Device || DeviceContext ||
						SwapChain || SwapChainBackBuffer || RenderTargetView ||
						DepthStencilBuffer || DepthStencilView) ? false : true);
			}

			~DeviceResources() { this->Release(); }
		};
	} // namespace DirectX11
} // namespace FZLib

#endif
