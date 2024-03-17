#include "pch.h"
#include "Device.h"
#include "Helper/ResourceGenerator.h"

namespace FZLib {
	namespace DirectX11 {

		Device::Device(std::string& deviceName, 
					   HWND hwnd, FZuint w, FZuint h,
					   D3D_DRIVER_TYPE type = D3D_DRIVER_TYPE_HARDWARE)
			: m_vData()
			, m_strDeviceName(deviceName)
			, m_hWinHandle(hwnd)
			, m_iWinWidth(w)
			, m_iWinHeight(h)
			, m_eDriverType(type)
		{ 
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
			auto& resGen = Helper::ResourceGenerator::GetInstance(*this);
			pBuffer = resGen.CreateDynamicVertexBuffer(size);
			return (pBuffer);
		}

		ID3D11Buffer* Device::CreateVertexBuffer(FZfloat* vertices, FZuint size)
		{
			// Create a vertex buffer.
			ID3D11Buffer* pBuffer = nullptr;
			auto& resGen = Helper::ResourceGenerator::GetInstance(*this);
			pBuffer = resGen.CreateStaticVertexBuffer(vertices, size);
			return (pBuffer);
		}

		ID3D11Buffer* Device::CreateIndexBuffer(FZuint size)
		{
			// Create the buffer with the device.
			ID3D11Buffer* pBuffer = nullptr;
			auto& resGen = Helper::ResourceGenerator::GetInstance(*this);
			pBuffer = resGen.CreateDynamicIndexBuffer(size);
			return (pBuffer);
		}

		ID3D11Buffer* Device::CreateIndexBuffer(FZuint* indices, FZuint size)
		{
			// Create the buffer with the device.
			ID3D11Buffer* pBuffer = nullptr;
			auto& resGen = Helper::ResourceGenerator::GetInstance(*this);
			pBuffer = resGen.CreateStaticIndexBuffer(indices, size);
			return (pBuffer);
		}

		FZbool Device::Initialize()
		{
			FZbool	result;
			result = this->CreateDeviceAndSwapChain();
			FZLOG_FAILED(result);
			result = this->CreateBackBufferAndViewport();
			FZLOG_FAILED(result);
		}

		FZbool Device::CleanUp()
		{
			return (m_vData.Release());
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
			sd.BufferDesc.Width = m_iWinWidth;
			sd.BufferDesc.Height = m_iWinHeight;
			sd.BufferDesc.RefreshRate.Numerator = 60;
			sd.BufferDesc.RefreshRate.Denominator = 1;
			sd.OutputWindow = m_hWinHandle;
			// Create a Device, DeviceContext, SwapChain
			HRESULT hr = D3D11CreateDeviceAndSwapChain(
				nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, deviceFlags,
				ConfigFeatureLevel::Targets, ConfigFeatureLevel::Nums, D3D11_SDK_VERSION,
				&sd, &m_vData.SwapChain, &m_vData.Device,
				&m_vData.FeatureLevel, &m_vData.DeviceContext
			);
			return ((SUCCEEDED(hr)) ? FZtrue : FZfalse);
		}

		FZbool Device::CreateBackBufferAndViewport()
		{
			hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_BackBuffer);
			hr = m_Device->CreateRenderTargetView(m_BackBuffer.Get(), nullptr, m_RenderTarget.GetAddressOf());

			// Create a depth-stencil view for use with 3D rendering if needed.
			m_BackBuffer->GetDesc(&m_bbDesc);
			CD3D11_TEXTURE2D_DESC depthStencilDesc(
				DXGI_FORMAT_D24_UNORM_S8_UINT,
				static_cast<UINT> (m_bbDesc.Width),
				static_cast<UINT> (m_bbDesc.Height),
				1, // This depth stencil view has only one texture.
				1, // Use a single mipmap level.
				D3D11_BIND_DEPTH_STENCIL
			);

			m_Device->CreateTexture2D(&depthStencilDesc, nullptr, &m_DepthStencil);
			CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
			m_Device->CreateDepthStencilView(m_DepthStencil.Get(), &depthStencilViewDesc, &m_DepthStencilView);

			ZeroMemory(&m_Viewport, sizeof(D3D11_VIEWPORT));
			m_Viewport.Height = (float)m_bbDesc.Height;
			m_Viewport.Width = (float)m_bbDesc.Width;
			m_Viewport.MinDepth = 0;
			m_Viewport.MaxDepth = 1;

			m_DeviceContext->RSSetViewports(1, &m_Viewport);
			return (hr == S_OK) ? true : false;
		}


	} // namespace DirectX11
} // namespace FZLib