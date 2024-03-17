#include "pch.h"
#include "ResourceGenerator.h"

namespace FZLib {
	namespace DirectX11 {
		namespace Helper {
			std::unique_ptr<ResourceGenerator>		ResourceGenerator::s_pInstance = nullptr;
			ID3D11Device*							ResourceGenerator::s_pCurrUsedDevice = nullptr;
			ID3D11DeviceContext*					ResourceGenerator::s_pCurrUsedContext = nullptr;

			ResourceGenerator& ResourceGenerator::GetInstance(Device& device)
			{
				if (s_pInstance == nullptr)
				{
					s_pInstance = std::make_unique<ResourceGenerator>();
				}
				s_pCurrUsedDevice = &device.GetNativeDevice();
				s_pCurrUsedContext = &device.GetNativeContext();
				return (*s_pInstance);
			}

			ID3D11Buffer* ResourceGenerator::CreateVertexBuffer(FZuint size, FZbool dynamic, FZbool streamout, D3D11_SUBRESOURCE_DATA* pData)
			{
				D3D11_BUFFER_DESC desc;
				desc.ByteWidth = size;
				desc.MiscFlags = 0;
				desc.StructureByteStride = 0;
				desc.Usage = (dynamic) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_IMMUTABLE;
				desc.CPUAccessFlags = (dynamic) ? D3D11_CPU_ACCESS_WRITE : NULL;
				desc.BindFlags = (streamout) ? D3D11_BIND_VERTEX_BUFFER | D3D11_BIND_STREAM_OUTPUT : D3D11_BIND_VERTEX_BUFFER;
				ID3D11Buffer* pBuffer = nullptr;
				HRESULT hr = s_pCurrUsedDevice->CreateBuffer(&desc, pData, &pBuffer);
				return ((SUCCEEDED(hr)) ? pBuffer : nullptr);
			}

			ID3D11Buffer* ResourceGenerator::CreateStaticVertexBuffer(FZfloat* vertices, FZuint size, FZbool streamOut)
			{
#ifdef _DEBUG
				if (size < 0)
				{
					FZLOG_ERROR("Failed to Create Static Vertex Buffer! -> An OverFlow occurred");
					return nullptr;
				}
#endif
				D3D11_SUBRESOURCE_DATA vData;
				ZeroMemory(&vData, sizeof(D3D11_SUBRESOURCE_DATA));
				vData.pSysMem = vertices;
				vData.SysMemPitch = 0;
				vData.SysMemSlicePitch = 0;
				return (this->CreateVertexBuffer(size, FZfalse, streamOut, &vData));
			}

			ID3D11Buffer* ResourceGenerator::CreateDynamicVertexBuffer(FZuint size, FZbool streamOut)
			{
#ifdef _DEBUG
				if (size < 0)
				{
					FZLOG_ERROR("Failed to Create Dynamic Vertex Buffer! -> An OverFlow occurred");
					return nullptr;
				}
#endif
				return (this->CreateVertexBuffer(size, FZtrue, streamOut, nullptr));;
			}

			ID3D11Buffer* ResourceGenerator::CreateIndexBuffer(FZuint size, FZbool dynamic, D3D11_SUBRESOURCE_DATA* pData)
			{
				D3D11_BUFFER_DESC desc;
				desc.ByteWidth = size;
				desc.MiscFlags = 0;
				desc.StructureByteStride = 0;
				desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
				desc.Usage = (dynamic) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_IMMUTABLE;
				desc.CPUAccessFlags = (dynamic) ? D3D11_CPU_ACCESS_WRITE : NULL;
				ID3D11Buffer* pBuffer = nullptr;
				HRESULT hr = s_pCurrUsedDevice->CreateBuffer(&desc, pData, &pBuffer);
				return ((SUCCEEDED(hr)) ? pBuffer : nullptr);
			}

			ID3D11Buffer * ResourceGenerator::CreateStaticIndexBuffer(FZuint* indices, FZuint size)
			{
#ifdef _DEBUG
				if (size < 0)
				{
					FZLOG_ERROR("Failed to Create Static Index Buffer! -> An OverFlow occurred");
					return nullptr;
				}
#endif
				D3D11_SUBRESOURCE_DATA vData;
				ZeroMemory(&vData, sizeof(D3D11_SUBRESOURCE_DATA));
				vData.pSysMem = indices;
				vData.SysMemPitch = 0;
				vData.SysMemSlicePitch = 0;
				return (this->CreateIndexBuffer(size, FZfalse, &vData));
			}

			ID3D11Buffer * ResourceGenerator::CreateDynamicIndexBuffer(FZuint size)
			{
#ifdef _DEBUG
				if (size < 0)
				{
					FZLOG_ERROR("Failed to Create Dynamic Index Buffer! -> An OverFlow occurred");
					return nullptr;
				}
#endif
				return (this->CreateIndexBuffer(size, FZtrue, nullptr));;
			}

			ID3D11Buffer* ResourceGenerator::CreateConstantBuffer(FZuint size, FZbool dynamic, FZbool CPUupdates, D3D11_SUBRESOURCE_DATA * pData)
			{
				D3D11_BUFFER_DESC desc;
				desc.ByteWidth = size;
				desc.MiscFlags = 0;
				desc.StructureByteStride = 0;
				desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				if (dynamic && CPUupdates)
				{
					desc.Usage = D3D11_USAGE_DYNAMIC;
					desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				}
				else if (dynamic && !CPUupdates)
				{
					desc.Usage = D3D11_USAGE_DYNAMIC;
					desc.CPUAccessFlags = NULL;
				}
				else
				{
					desc.Usage = D3D11_USAGE_IMMUTABLE;
					desc.CPUAccessFlags = NULL;
				}
				ID3D11Buffer* pBuffer = nullptr;
				HRESULT hr = s_pCurrUsedDevice->CreateBuffer(&desc, pData, &pBuffer);
				return ((SUCCEEDED(hr)) ? pBuffer : nullptr);
			}

			ID3D11Buffer* ResourceGenerator::CreateStructuredBuffer(FZuint count, FZuint structSize, FZbool CPUwritable, FZbool GPUwritable, D3D11_SUBRESOURCE_DATA* pData)
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
				HRESULT hr = s_pCurrUsedDevice->CreateBuffer(&desc, pData, &pBuffer);
				return ((SUCCEEDED(hr)) ? pBuffer : nullptr);
			}

			ID3D11ShaderResourceView* ResourceGenerator::CreateBufferShaderResourceView(ID3D11Resource* pResource)
			{
				D3D11_SHADER_RESOURCE_VIEW_DESC desc;
				desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
				desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
				desc.Buffer.ElementOffset = 0;
				desc.Buffer.ElementWidth = 100;
				ID3D11ShaderResourceView* pView = nullptr;
				HRESULT hr = s_pCurrUsedDevice->CreateShaderResourceView(pResource, &desc, &pView);
				return ((SUCCEEDED(hr)) ? pView : nullptr);
			}

			ID3D11UnorderedAccessView* ResourceGenerator::CreateBufferUnorderedAccessView(ID3D11Resource* pResource)
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
				HRESULT hr = s_pCurrUsedDevice->CreateUnorderedAccessView(pResource, &desc, &pView);
				return ((SUCCEEDED(hr)) ? pView : nullptr);
			}

		} // namespace Helper
	} // namespace DirectX11
} // namespace FZLib