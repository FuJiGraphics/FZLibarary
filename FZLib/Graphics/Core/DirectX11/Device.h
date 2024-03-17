/*********************************************************************
 * @file   Dx11_Device.h
 * @brief  DirectX11의 리소스 생성 및 관리를 위한 디바이스
 *
 * @author FuJiGraphics
 * @date   2024/03/14
 *********************************************************************/

#pragma once
#ifndef __FZ_LIBRARY_DEVICE_DIRECTX11__
#define __FZ_LIBRARY_DEVICE_DIRECTX11__

#include "CoreRef.h"
#include "Buffer.h"

namespace FZLib {
	namespace DirectX11 {

		struct WinInfo {

		};

		class FZLIB_API Device
		{
		public:
			Device(std::string& deviceName, HWND hwnd, FZuint w, FZuint h, D3D_DRIVER_TYPE type = D3D_DRIVER_TYPE_HARDWARE);
			~Device();

		public:
			inline ID3D11Device&			GetNativeDevice() const		{ return (*m_vData.Device); }
			inline ID3D11DeviceContext&		GetNativeContext() const	{ return (*m_vData.DeviceContext); }
			inline std::string				GetDeviceName()	const		{ return (m_strDeviceName); }

		public:
			ID3D11Buffer*		CreateVertexBuffer(FZuint size);
			ID3D11Buffer*		CreateVertexBuffer(FZfloat* vertices, FZuint size);
			ID3D11Buffer*		CreateIndexBuffer(FZuint size);
			ID3D11Buffer*		CreateIndexBuffer(FZuint* indices, FZuint size);

		private:
			FZbool	Initialize();
			FZbool	CleanUp();

		private:
			FZbool	CreateDeviceAndSwapChain();
			FZbool	CreateBackBufferAndViewport();

		private:
			DeviceResources			m_vData; 
			std::string				m_strDeviceName;
			HWND					m_hWinHandle;
			FZuint					m_iWinWidth;
			FZuint					m_iWinHeight;
			D3D_DRIVER_TYPE			m_eDriverType;
		};

	} // namespace DirectX11
} // namespace FZLib

#endif
