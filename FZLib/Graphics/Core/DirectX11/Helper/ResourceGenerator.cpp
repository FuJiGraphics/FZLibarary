#include "pch.h"
#include "ResourceGenerator.h"

namespace FZLib {
	namespace DirectX11 {
		namespace Helper {
			std::unique_ptr<ResourceGenerator>		ResourceGenerator::s_pInstance = nullptr;

			ResourceGenerator& ResourceGenerator::GetInstance(ID3D11Device& device, ID3D11DeviceContext& deviceContext)
			{
				if (s_pInstance == nullptr)
				{
					s_pInstance = std::make_unique<ResourceGenerator>();
				}
				s_pInstance->SetDeviceAndDeviceContext(device, deviceContext);
				return *s_pInstance;
			}

			ResourceGenerator::ResourceGenerator()
				: m_pDevice(nullptr)
				, m_pDeviceContext(nullptr)
			{
				// Empty
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
					hr = m_pDevice->CreateBuffer(&desc, &vData, &pBuffer);
				}
				else 
					hr = m_pDevice->CreateBuffer(&desc, pData, &pBuffer);
				
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
					hr = m_pDevice->CreateBuffer(&desc, &vData, &pBuffer);
				}
				else
					hr = m_pDevice->CreateBuffer(&desc, pData, &pBuffer);

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
					hr = m_pDevice->CreateBuffer(&desc, &vData, &pBuffer);
				}
				else
					hr = m_pDevice->CreateBuffer(&desc, pData, &pBuffer);

				if (FAILED(hr))
					pBuffer = nullptr;

				return (pBuffer);
			}

			ID3D11Buffer* ResourceGenerator::CreateStructuredBuffer(unsigned int count,
																	unsigned int structSize,
																	bool CPUwritable,
																	bool GPUwritable,
																	D3D11_SUBRESOURCE_DATA * pData)
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
					hr = m_pDevice->CreateBuffer(&desc, &vData, &pBuffer);
				}
				else
					hr = m_pDevice->CreateBuffer(&desc, pData, &pBuffer);
				if (FAILED(hr))
					return (nullptr);
				return (pBuffer);
			}

			void ResourceGenerator::SetDeviceAndDeviceContext(ID3D11Device& device, ID3D11DeviceContext& deviceContext)
			{
				m_pDevice = &device;
				m_pDeviceContext = &deviceContext;
			}

		} // namespace Helper
	} // namespace DirectX11
} // namespace FZLib