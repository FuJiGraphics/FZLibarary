#include "pch.h"
#include "ResourceGenerator.h"

namespace FZLib {
	namespace DirectX11 {
		namespace Helper {
			std::unique_ptr<ResourceGenerator>		ResourceGenerator::s_pInstance = nullptr;
			std::map<std::string, DeviceResource>	ResourceGenerator::s_mDeviceResources;
			DeviceResource*							ResourceGenerator::s_CurrDeviceResource = nullptr;
			ID3D11Device*							ResourceGenerator::s_CurrDevice = nullptr;
			ID3D11DeviceContext*					ResourceGenerator::s_CurrDeviceContext = nullptr;

			ResourceGenerator& ResourceGenerator::GetInstance()
			{
				if (s_pInstance == nullptr)
				{
					s_pInstance = std::make_unique<ResourceGenerator>();
				}
				return (*s_pInstance);
			}

			DeviceResource* ResourceGenerator::GetDeviceResource(const std::string& deviceName)
			{
				if (s_mDeviceResources.find(deviceName) == s_mDeviceResources.end())
					return (nullptr);
				return &s_mDeviceResources[deviceName];
			}

			ID3D11Device* ResourceGenerator::GetCurrentDevice() const
			{
				return (s_CurrDevice);
			}

			ID3D11DeviceContext* ResourceGenerator::GetCurrentDeviceContext() const
			{
				return (s_CurrDeviceContext);
			}
                       
			bool ResourceGenerator::ReleaseDeviceResource(const std::string& deviceName)
			{
				if (s_mDeviceResources.find(deviceName) == s_mDeviceResources.end())
					return (false);
				auto& deviceResource = s_mDeviceResources[deviceName];
				bool result = deviceResource.Shutdown();
				result = s_mDeviceResources.erase(deviceName);
				return (result);
			}

			bool ResourceGenerator::ReleaseDeviceResources()
			{
				if (s_mDeviceResources.empty())
					return (false);
				for (auto& deviceResource : s_mDeviceResources)
				{
					deviceResource.second.Shutdown();
				}
				return (true);
			}

			bool ResourceGenerator::GenerateDeviceResources(const std::string& deviceName, const HWND& hwnd, int width, int height)
			{
				if (s_mDeviceResources.find(deviceName) == s_mDeviceResources.end())
					return (false);
				s_mDeviceResources.insert({ deviceName, {/*Default Constructor*/} });
				s_mDeviceResources[deviceName].StartUp(hwnd, width, height);
				this->SetDeviceResource(s_mDeviceResources[deviceName]);
				return (true);
			}

			bool ResourceGenerator::ApplyDeviceResources(const std::string& deviceName)
			{
				if (s_mDeviceResources.find(deviceName) == s_mDeviceResources.end())
					return (false);
				this->SetDeviceResource(s_mDeviceResources[deviceName]);
				return (true);
			}

			ID3D11Buffer* ResourceGenerator::CreateVertexBuffer(unsigned int size, bool dynamic, bool streamout, D3D11_SUBRESOURCE_DATA* pData)
			{
				D3D11_BUFFER_DESC desc;
				desc.ByteWidth = size;
				desc.MiscFlags = 0;
				desc.StructureByteStride = 0;
				// 버퍼의 용도 선택
				if (dynamic)
				{
					desc.Usage = D3D11_USAGE_DYNAMIC;
					desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				}
				else
				{
					desc.Usage = D3D11_USAGE_IMMUTABLE;
					desc.CPUAccessFlags = 0;
				}
				// 파이프라인 바인딩 지점 선택
				if (streamout)
					desc.BindFlags = D3D11_BIND_VERTEX_BUFFER | D3D11_BIND_STREAM_OUTPUT;
				else
					desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				// 설정된 Desc를 기준으로 Buffer 생성
				ID3D11Buffer* pBuffer = nullptr;

				HRESULT hr = S_OK;
				if (pData == nullptr)
				{
					D3D11_SUBRESOURCE_DATA vData;
					ZeroMemory(&vData, sizeof(D3D11_SUBRESOURCE_DATA));
					vData.pSysMem = nullptr;
					vData.SysMemPitch = 0;
					vData.SysMemSlicePitch = 0;
					hr = s_CurrDevice->CreateBuffer(&desc, &vData, &pBuffer);
				}
				else 
					hr = s_CurrDevice->CreateBuffer(&desc, pData, &pBuffer);
				
				if (FAILED(hr))
					pBuffer = nullptr;
				
				return (pBuffer);
			}

			ID3D11Buffer* ResourceGenerator::CreateIndexBuffer(unsigned int size, bool dynamic, D3D11_SUBRESOURCE_DATA * pData)
			{
				D3D11_BUFFER_DESC desc;
				desc.ByteWidth = size;
				desc.MiscFlags = 0;
				desc.StructureByteStride = 0;
				desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
				// 버퍼의 용도 선택
				if (dynamic)
				{
					desc.Usage = D3D11_USAGE_DYNAMIC;
					desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				}
				else
				{
					desc.Usage = D3D11_USAGE_IMMUTABLE;
					desc.CPUAccessFlags = 0;
				}
				// 설정된 Desc를 기준으로 Buffer 생성
				ID3D11Buffer* pBuffer = nullptr;
				HRESULT hr = S_OK;
				if (pData == nullptr)
				{
					D3D11_SUBRESOURCE_DATA vData;
					ZeroMemory(&vData, sizeof(D3D11_SUBRESOURCE_DATA));
					vData.pSysMem = nullptr;
					vData.SysMemPitch = 0;
					vData.SysMemSlicePitch = 0;
					hr = s_CurrDevice->CreateBuffer(&desc, &vData, &pBuffer);
				}
				else
					hr = s_CurrDevice->CreateBuffer(&desc, pData, &pBuffer);

				if (FAILED(hr))
					pBuffer = nullptr;

				return (pBuffer);
			}

			ID3D11Buffer * ResourceGenerator::CreateConstantBuffer(unsigned int size, bool dynamic, bool CPUupdates, D3D11_SUBRESOURCE_DATA * pData)
			{
				D3D11_BUFFER_DESC desc;
				desc.ByteWidth = size;
				desc.MiscFlags = 0;
				desc.StructureByteStride = 0;
				desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				// 버퍼의 용도 선택
				if (dynamic && CPUupdates)
				{
					desc.Usage = D3D11_USAGE_DYNAMIC;
					desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				}
				else if (dynamic && !CPUupdates)
				{
					desc.Usage = D3D11_USAGE_DYNAMIC;
					desc.CPUAccessFlags = 0;
				}
				else
				{
					desc.Usage = D3D11_USAGE_IMMUTABLE;
					desc.CPUAccessFlags = 0;
				}
				// 설정된 Desc를 기준으로 Buffer 생성
				ID3D11Buffer* pBuffer = nullptr;
				HRESULT hr = S_OK;
				if (pData == nullptr)
				{
					D3D11_SUBRESOURCE_DATA vData;
					ZeroMemory(&vData, sizeof(D3D11_SUBRESOURCE_DATA));
					vData.pSysMem = nullptr;
					vData.SysMemPitch = 0;
					vData.SysMemSlicePitch = 0;
					hr = s_CurrDevice->CreateBuffer(&desc, &vData, &pBuffer);
				}
				else
					hr = s_CurrDevice->CreateBuffer(&desc, pData, &pBuffer);

				if (FAILED(hr))
					pBuffer = nullptr;

				return (pBuffer);
			}

			ID3D11Buffer* ResourceGenerator::CreateStructuredBuffer(unsigned int count,
																	unsigned int structSize,
																	bool CPUwritable,
																	bool GPUwritable,
																	D3D11_SUBRESOURCE_DATA* pData)
			{
				D3D11_BUFFER_DESC desc;
				desc.ByteWidth = count * structSize;
				desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
				desc.StructureByteStride = structSize;

				if (!CPUwritable && !GPUwritable)
				{
					desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
					desc.Usage = D3D11_USAGE_IMMUTABLE;
					desc.CPUAccessFlags = 0;
				}
				else if (CPUwritable && !GPUwritable)
				{
					desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
					desc.Usage = D3D11_USAGE_IMMUTABLE;
					desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				}
				else if (!CPUwritable && GPUwritable)
				{
					desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
					desc.Usage = D3D11_USAGE_DEFAULT;
					desc.CPUAccessFlags = 0;
				}
				else
					return (nullptr);

				ID3D11Buffer* pBuffer = nullptr;
				HRESULT hr;
				if (pData == nullptr)
				{
					D3D11_SUBRESOURCE_DATA vData;
					ZeroMemory(&vData, sizeof(D3D11_SUBRESOURCE_DATA));
					vData.pSysMem = nullptr;
					vData.SysMemPitch = 0;
					vData.SysMemSlicePitch = 0;
					hr = s_CurrDevice->CreateBuffer(&desc, &vData, &pBuffer);
				}
				else
					hr = s_CurrDevice->CreateBuffer(&desc, pData, &pBuffer);
				if (FAILED(hr))
					return (nullptr);
				return (pBuffer);
			}

			ID3D11ShaderResourceView* ResourceGenerator::CreateBufferShaderResourceView(ID3D11Resource* pResource)
			{
				D3D11_SHADER_RESOURCE_VIEW_DESC desc;
				desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
				desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
				desc.Buffer.ElementOffset = 0;
				desc.Buffer.ElementWidth = 100;
				ID3D11ShaderResourceView* pView = nullptr;
				s_CurrDevice->CreateShaderResourceView(pResource, &desc, &pView);
				return (pView);
			}

			ID3D11UnorderedAccessView * ResourceGenerator::CreateBufferUnorderedAccessView(ID3D11Resource* pResource)
			{
				D3D11_UNORDERED_ACCESS_VIEW_DESC desc;
				desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
				desc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
				desc.Buffer.FirstElement = 0;
				desc.Buffer.NumElements = 100;
				desc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_COUNTER;
				//desc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_APPEND;
				//desc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
				ID3D11UnorderedAccessView* pView = nullptr;
				s_CurrDevice->CreateUnorderedAccessView(pResource, &desc, &pView);
				return (pView);
			}

			void ResourceGenerator::SetDeviceResource(DeviceResource& deviceResource)
			{
				s_CurrDeviceResource = &deviceResource;
				s_CurrDevice = &deviceResource.GetDevice();
				s_CurrDeviceContext = &deviceResource.GetDeviceContext();
			}

		} // namespace Helper
	} // namespace DirectX11
} // namespace FZLib