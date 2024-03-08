/*********************************************************************
 * @file   Dx11_DeviceManager.cpp
 * @brief  ����̽� ���� �� ���� �����̳� �Ŵ���
 * 
 * @author FuJiGraphics
 * @date   2024/03/07
 *********************************************************************/

#include <pch.h>
#include "Dx11_DeviceManager.h"

namespace FZLib {

	DeviceManager::DeviceManager()
		: m_WindowHandle(NULL)
		, m_Initialized(false)
		, m_FeatureLevel(D3D_FEATURE_LEVEL_11_1)
		, m_bbDesc()
		, m_Viewport()
		, m_DeviceContext()
		, m_Device()
		, m_SwapChain()
	{
		// Empty
	}

	DeviceManager::~DeviceManager()
	{
		// delete device context
		m_DeviceContext->Release();
		m_DeviceContext.Reset();
		// delete swap chain
		m_SwapChain->Release();
		m_SwapChain.Reset();
		// delete device
		m_Device->Release();
		m_Device.Reset();
		ReleaseBackBuffer();
	}

	bool DeviceManager::StartUp(const HWND& hwnd, int width, int height)
	{
		bool result = false;
		m_WindowHandle = hwnd;
		result = CreateDeviceAndSwapChain(width, height);
		result = CreateBackBufferAndViewport();
		m_Initialized = true;
		return result;
	}

	bool DeviceManager::Shutdown()
	{
		bool result = false;
		m_WindowHandle = NULL;
		m_Initialized = false;
		m_DeviceContext.Reset();
		m_SwapChain.Reset();
		m_Device.Reset();
		result = ReleaseBackBuffer();
		return result;
	}

	float DeviceManager::GetAspectRatio() const
	{
		return static_cast<float>(m_bbDesc.Width) / static_cast<float>(m_bbDesc.Height);
	}

	unsigned int DeviceManager::GetWidth() const
	{
		return m_bbDesc.Width;
	}

	unsigned int DeviceManager::GetHeight() const
	{
		return m_bbDesc.Height;
	}

	bool DeviceManager::SetFullScreen()
	{
		HRESULT	hr = S_OK;
		hr = m_SwapChain->SetFullscreenState(TRUE, nullptr);
		hr = ResetBackBuffer();
		return (hr == S_OK) ? true : false;
	}

	bool DeviceManager::SetWindowed()
	{
		HRESULT hr = S_OK;
		hr = m_SwapChain->SetFullscreenState(FALSE, nullptr);
		hr = ResetBackBuffer();
		return (hr == S_OK) ? true : false;
	}

	bool DeviceManager::CreateDeviceAndSwapChain(int bufWidth, int bufHeight)
	{
		D3D_FEATURE_LEVEL levels[] = {
			D3D_FEATURE_LEVEL_9_1,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_11_1
		};
		UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
		HRESULT hr = S_OK;

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
		sd.BufferDesc.Width = bufWidth;
		sd.BufferDesc.Height = bufHeight;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.OutputWindow = m_WindowHandle;

		// Create Device
		hr = D3D11CreateDeviceAndSwapChain(
			nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, deviceFlags,
			levels, ARRAYSIZE(levels), D3D11_SDK_VERSION, &sd,
			m_SwapChain.GetAddressOf(), m_Device.GetAddressOf(),
			&m_FeatureLevel, m_DeviceContext.GetAddressOf()
		);

		return (hr == S_OK) ? true : false;
	}

	bool DeviceManager::ResetBackBuffer()
	{
		HRESULT hr = S_OK;
		
		// DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL �÷��׷� ������ ���� ü���� ������ �����ؾ� �մϴ�.
		// ��ü ȭ�� ��� ��ȯ�� �����ϱ� ���� ResizeBuffers�� ȣ���ؾ� �մϴ�. �׷��� ������
		// ���� ���������̼� ȣ���� �����մϴ�.

		// ResizeBuffers�� ȣ���ϱ� ���� �޸� ���� ��ġ ���ҽ��� ���� ��� ������ �����ؾ� �մϴ�.
		// ���� ����̽� ���ҽ��� ���� ��� ������ �����ؾ� �մϴ�.
		ReleaseBackBuffer();
		
		// ���� ������ ����� �缳���� �� �ֽ��ϴ�.
		hr = m_SwapChain->ResizeBuffers(
			0,                   // ���� ���Դϴ�. ���� ������ �����Ϸ��� �� ���� 0���� �����մϴ�.
			0, 0,                // ���� ü���� �ʺ�� �����Դϴ�. ȭ�� �ػ󵵿� ��ġ�ϵ��� 0���� �����մϴ�.
			DXGI_FORMAT_UNKNOWN, // �̰��� DXGI�� ���� �� ���� ������ �����ϵ��� �����մϴ�.
			0
		);
		
		hr = CreateBackBufferAndViewport();
		
		return (hr == S_OK) ? true : false;
	}

	bool DeviceManager::EnumerateAdapters(std::vector<IDXGIAdapter*>* out)
	{
		IDXGIAdapter* pAdapter;
		IDXGIFactory* pFactory = NULL;
		// Create a DXGIFactory object.
		if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory)))
		{
			return false;
		}
		for (UINT i = 0; pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i)
		{
			out->push_back(pAdapter);
		}
		if (pFactory)
		{
			pFactory->Release();
		}
		return true;
	}

	bool DeviceManager::CreateBackBufferAndViewport()
	{
		HRESULT hr = S_OK;

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

	bool DeviceManager::ReleaseBackBuffer()
	{
		HRESULT	hr = S_OK;
		m_RenderTarget.Reset();
		m_BackBuffer.Reset();
		m_DepthStencilView.Reset();
		m_DepthStencil.Reset();
		m_DeviceContext->Flush();
		m_Initialized = false;
		return (hr == S_OK) ? true : false;
	}

} // namespace FZLib
