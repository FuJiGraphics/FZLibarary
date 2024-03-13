/*********************************************************************
 * @file   DeviceManager.cpp
 * @brief  디바이스 생성 및 관리 컨테이너 매니저
 * 
 * @author FuJiGraphics
 * @date   2024/03/12
 *********************************************************************/

#include <pch.h>
#include "DeviceManager.h"

namespace FZLib {
	namespace DirectX11 {
		namespace Helper {

#pragma region DeviceResource
			DeviceResource::DeviceResource()
				: m_Initialized(false)
				, m_FeatureLevel(D3D_FEATURE_LEVEL_11_1)
				, m_bbDesc()
				, m_Viewport()
				, m_DeviceContext()
				, m_Device()
				, m_SwapChain()
			{
				// Empty
			}

			DeviceResource::~DeviceResource()
			{
				if (m_Initialized == false)
					return;
				Shutdown();
			}

			bool DeviceResource::StartUp(const HWND& hwnd, int width, int height)
			{
				if (m_Initialized)
					return false;
				bool result = false;
				result = CreateDeviceAndSwapChain(hwnd, width, height);
				result = CreateBackBufferAndViewport();
				m_Initialized = true;
				return result;
			}

			bool DeviceResource::Shutdown()
			{
				bool result = false;
				m_Initialized = false;
				m_DeviceContext.Reset();
				m_SwapChain.Reset();
				m_Device.Reset();
				result = ReleaseBackBuffer();
				return result;
			}

			bool DeviceResource::CreateDeviceAndSwapChain(const HWND& hwnd, int bufWidth, int bufHeight)
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
				sd.OutputWindow = hwnd;

				// Create Device
				hr = D3D11CreateDeviceAndSwapChain(
					nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, deviceFlags,
					levels, ARRAYSIZE(levels), D3D11_SDK_VERSION, &sd,
					m_SwapChain.GetAddressOf(), m_Device.GetAddressOf(),
					&m_FeatureLevel, m_DeviceContext.GetAddressOf()
				);

				return (hr == S_OK) ? true : false;
			}

			bool DeviceResource::ResetBackBuffer()
			{
				HRESULT hr = S_OK;

				// DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL 플래그로 생성된 스왑 체인은 다음을 수행해야 합니다.
				// 전체 화면 모드 전환을 구현하기 위해 ResizeBuffers를 호출해야 합니다. 그렇지 않으면
				// 다음 프레젠테이션 호출이 실패합니다.

				// ResizeBuffers를 호출하기 전에 뒷면 버퍼 장치 리소스에 대한 모든 참조를 해제해야 합니다.
				// 버퍼 디바이스 리소스에 대한 모든 참조를 해제해야 합니다.
				ReleaseBackBuffer();

				// 이제 버퍼의 사이즈를 재설정할 수 있습니다.
				hr = m_SwapChain->ResizeBuffers(
					0,                   // 버퍼 수입니다. 기존 설정을 유지하려면 이 값을 0으로 설정합니다.
					0, 0,                // 스왑 체인의 너비와 높이입니다. 화면 해상도와 일치하도록 0으로 설정합니다.
					DXGI_FORMAT_UNKNOWN, // 이것은 DXGI가 현재 백 버퍼 형식을 유지하도록 지시합니다.
					0
				);

				hr = CreateBackBufferAndViewport();

				return (hr == S_OK) ? true : false;
			}

			bool DeviceResource::EnumerateAdapters(std::vector<IDXGIAdapter*>* out)
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

			bool DeviceResource::CreateBackBufferAndViewport()
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

			bool DeviceResource::ReleaseBackBuffer()
			{
				// TODO : result 결과 수정
				HRESULT	hr = S_OK;
				m_RenderTarget.Reset();
				m_BackBuffer.Reset();
				m_DepthStencilView.Reset();
				m_DepthStencil.Reset();
				m_DeviceContext->Flush();
				m_Initialized = false;
				return (hr == S_OK) ? true : false;
			}

			ID3D11Device& DeviceResource::GetDevice() const
			{
				return *m_Device.Get();
			}

			ID3D11DeviceContext& DeviceResource::GetDeviceContext() const
			{
				return *m_DeviceContext.Get();
			}

			DevicePackRef DeviceResource::GetDeviceAndContext() const
			{
				return { *m_Device.Get(), *m_DeviceContext.Get() };
			}

			float DeviceResource::GetAspectRatio() const
			{
				return static_cast<float>(m_bbDesc.Width) / static_cast<float>(m_bbDesc.Height);
			}

			unsigned int DeviceResource::GetWidth() const
			{
				return m_bbDesc.Width;
			}

			unsigned int DeviceResource::GetHeight() const
			{
				return m_bbDesc.Height;
			}

			HWND DeviceResource::GetWindowHandle() const
			{
				DXGI_SWAP_CHAIN_DESC desc;
				m_SwapChain->GetDesc(&desc);
				return desc.OutputWindow;
			}

			bool DeviceResource::SetFullScreen()
			{
				HRESULT	hr = S_OK;
				hr = m_SwapChain->SetFullscreenState(TRUE, nullptr);
				hr = ResetBackBuffer();
				return (hr == S_OK) ? true : false;
			}

			bool DeviceResource::SetWindowed()
			{
				HRESULT hr = S_OK;
				hr = m_SwapChain->SetFullscreenState(FALSE, nullptr);
				hr = ResetBackBuffer();
				return (hr == S_OK) ? true : false;
			}
#pragma endregion

#pragma region DeviceManager
			std::unique_ptr<DeviceManager> DeviceManager::s_Instance = nullptr;

			DeviceManager& DeviceManager::GetInstance()
			{
				if (s_Instance == nullptr)
				{
					s_Instance = std::make_unique<DeviceManager>();
				}
				return *s_Instance;
			}

			DeviceManager::DeviceManager()
				: m_WindowHandle(NULL)
			{
				// Empty
			}

			DeviceManager::~DeviceManager()
			{
				Release();
			}

			void DeviceManager::Release()
			{
				for (auto& deviceResource: m_DeviceResources)
				{
					deviceResource.second.Shutdown();
				}
			}

			DeviceResource* DeviceManager::GetDeviceResource()
			{
				if (m_DeviceResources.begin() == m_DeviceResources.end())
					return nullptr;
				else
					return &m_DeviceResources.begin()->second;
			}

			DeviceResource* DeviceManager::GetDeviceResource(const std::string& deviceName)
			{
				if (m_DeviceResources.find(deviceName) == m_DeviceResources.end())
					return nullptr;
				else
					return &m_DeviceResources[deviceName];
			}

			DevicePackRef DeviceManager::GetFirstDeviceAndDeviceContext()
			{
				//if (m_DeviceResources.begin() == m_DeviceResources.end())
				//	FAILED
				
				auto&[device, deviceContext] = m_DeviceResources.begin()->second.GetDeviceAndContext();
				return { device, deviceContext };
			}

			DevicePackRef DeviceManager::GetDeviceAndDeviceContext(const std::string& deviceName)
			{
				//if (m_DeviceResources.find(deviceName) == m_DeviceResources.end())
				//	FAILED
				
				return m_DeviceResources.begin()->second.GetDeviceAndContext();
			}

			ID3D11Device* DeviceManager::GetFirstDevice()
			{
				if (m_DeviceResources.begin() == m_DeviceResources.end())
					return nullptr;
				else
					return &m_DeviceResources.begin()->second.GetDevice();
			}

			ID3D11DeviceContext* DeviceManager::GetFirstDeviceContext()
			{
				if (m_DeviceResources.begin() == m_DeviceResources.end())
					return nullptr;
				else
					return &m_DeviceResources.begin()->second.GetDeviceContext();
			}

			ID3D11Device* DeviceManager::GetDevice(const std::string& deviceName)
			{
				if (m_DeviceResources.find(deviceName) == m_DeviceResources.end())
					return nullptr;
				else
					return &m_DeviceResources[deviceName].GetDevice();
			}

			ID3D11DeviceContext* DeviceManager::GetDeviceContext(const std::string& deviceName)
			{
				if (m_DeviceResources.find(deviceName) == m_DeviceResources.end())
					return nullptr;
				else
					return &m_DeviceResources[deviceName].GetDeviceContext();
			}

			bool DeviceManager::GenerateDeviceResource(const std::string& deviceName, const HWND& hwnd, int width, int height)
			{
				if (m_DeviceResources.find(deviceName) == m_DeviceResources.end())
					return false;
				m_DeviceResources.insert(std::pair<std::string, DeviceResource>(deviceName, {}));
				m_DeviceResources[deviceName].StartUp(hwnd, width, height);
				return true;
			}

			bool DeviceManager::ReleaseDeviceResource(const std::string& deviceName)
			{
				if (m_DeviceResources.find(deviceName) == m_DeviceResources.end())
					return false;
				m_DeviceResources[deviceName].Shutdown();
				return true;
			}
#pragma endregion

		} // namespace Helper
	} // namespace DirectX11
} // namespace FZLib
