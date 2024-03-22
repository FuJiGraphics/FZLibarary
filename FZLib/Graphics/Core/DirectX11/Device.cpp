#include "pch.h"
#include "Device.h"
#include "Helpers/ResourceGenerator.h"

namespace FZLib {
	namespace DirectX11 {

		using namespace Helpers;

		Device::Device(const std::string& dcName, HWND hwnd, 
					   FZuint w, FZuint h, D3D_DRIVER_TYPE type)
			: m_Data()
			, m_WinData()
			, m_DeviceName(dcName)
			, m_DriverType(type)
		{ 
			m_WinData.Handle = hwnd;
			m_WinData.Width  = w;
			m_WinData.Height = h;
			this->Initialize();
		}

		Device::~Device()
		{ 
			this->CleanUp();
		}

		ID3D11Buffer* Device::CreateVertexBuffer(FZuint size)
		{
			// Create a vertex buffer.
			ID3D11Buffer* pBuffer = nullptr;
			auto& resGen = ResourceGenerator::GetInstance(*this);
			pBuffer = resGen.CreateDynamicVertexBuffer(size);
			return (pBuffer);
		}

		ID3D11Buffer* Device::CreateVertexBuffer(FZfloat* vertices, FZuint size)
		{
			// Create a vertex buffer.
			ID3D11Buffer* pBuffer = nullptr;
			auto& resGen = ResourceGenerator::GetInstance(*this);
			pBuffer = resGen.CreateStaticVertexBuffer(vertices, size);
			return (pBuffer);
		}

		ID3D11Buffer* Device::CreateIndexBuffer(FZuint size)
		{
			// Create the buffer with the device.
			ID3D11Buffer* pBuffer = nullptr;
			auto& resGen = ResourceGenerator::GetInstance(*this);
			pBuffer = resGen.CreateDynamicIndexBuffer(size);
			return (pBuffer);
		}

		ID3D11Buffer* Device::CreateIndexBuffer(FZuint* indices, FZuint size)
		{
			// Create the buffer with the device.
			ID3D11Buffer* pBuffer = nullptr;
			auto& resGen = ResourceGenerator::GetInstance(*this);
			pBuffer = resGen.CreateStaticIndexBuffer(indices, size);
			return (pBuffer);
		}

		void Device::Present()
		{
			static float color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
			m_Data.DeviceContext->OMSetRenderTargets(1, &m_Data.RenderTargetView, m_Data.DepthStencilView);
			m_Data.DeviceContext->ClearRenderTargetView(m_Data.RenderTargetView, color);
			m_Data.SwapChain->Present(1, 0);
		}

		FZbool Device::Initialize()
		{
			FZbool	result;
			result = this->CreateDeviceAndSwapChain();
			FZLOG_FAILED(result);
			result = this->CreateBackBufferAndViewport();
			FZLOG_FAILED(result);
			return (result);
		}

		FZbool Device::CleanUp()
		{
			return (m_Data.Release());
		}

		FZbool Device::CreateDeviceAndSwapChain()
		{
			FZuint deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(DEBUG) || defined(_DEBUG)
			deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
			// Description SwapChain
			DXGI_SWAP_CHAIN_DESC sd;
			ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));
			sd.Windowed = TRUE;
			sd.BufferCount = 2;
			sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
			sd.BufferDesc.Width = m_WinData.Width;
			sd.BufferDesc.Height = m_WinData.Height;
			sd.BufferDesc.RefreshRate.Numerator = 60;
			sd.BufferDesc.RefreshRate.Denominator = 1;
			sd.OutputWindow = m_WinData.Handle;
			// Create a Device, DeviceContext, SwapChain
			HRESULT hr = D3D11CreateDeviceAndSwapChain(
				nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, deviceFlags,
				ConfigFeatureLevel::Targets, ConfigFeatureLevel::Nums, D3D11_SDK_VERSION,
				&sd, &m_Data.SwapChain, &m_Data.Device,
				&m_Data.FeatureLevel, &m_Data.DeviceContext
			);
			return (SUCCEEDED(hr));
		}

		FZbool Device::CreateBackBufferAndViewport()
		{
			HRESULT hr = S_OK;
			hr = m_Data.SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_Data.SwapChainBackBuffer);
			hr = m_Data.Device->CreateRenderTargetView(m_Data.SwapChainBackBuffer, nullptr, &m_Data.RenderTargetView);

			// Create a depth-stencil view for use with 3D rendering if needed.
			m_Data.SwapChainBackBuffer->GetDesc(&m_Data.BackBufferDesc);
			CD3D11_TEXTURE2D_DESC depthStencilDesc(
				DXGI_FORMAT_D24_UNORM_S8_UINT,
				static_cast<UINT> (m_Data.BackBufferDesc.Width),
				static_cast<UINT> (m_Data.BackBufferDesc.Height),
				1, // This depth stencil view has only one texture.
				1, // Use a single mipmap level.
				D3D11_BIND_DEPTH_STENCIL
			);

			m_Data.Device->CreateTexture2D(&depthStencilDesc, nullptr, &m_Data.DepthStencilBuffer);
			CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
			m_Data.Device->CreateDepthStencilView(m_Data.DepthStencilBuffer, &depthStencilViewDesc, &m_Data.DepthStencilView);

			ZeroMemory(&m_Data.Viewport, sizeof(D3D11_VIEWPORT));
			m_Data.Viewport.Height = (float)m_Data.BackBufferDesc.Height;
			m_Data.Viewport.Width = (float)m_Data.BackBufferDesc.Width;
			m_Data.Viewport.MinDepth = 0;
			m_Data.Viewport.MaxDepth = 1;

			m_Data.DeviceContext->RSSetViewports(1, &m_Data.Viewport);
			return (SUCCEEDED(hr));
		}


	} // namespace DirectX11
} // namespace FZLib