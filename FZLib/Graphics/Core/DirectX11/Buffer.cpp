/*********************************************************************
 * @file   Buffer.cpp
 * @brief  렌더러에서 사용되는 버퍼 모음
 *
 * @author FuJiGraphics
 * @date   2024/03/08
 *********************************************************************/

#include <pch.h>
#include "Buffer.h"
#include "Helpers/DeviceManager.h"

namespace FZLib {
	namespace DirectX11 {

		using namespace Helpers;

		//-----------------------------------------------------------------------------
		// Vertex Buffer Member Funtions
		//-----------------------------------------------------------------------------
		VertexBuffer::VertexBuffer(unsigned int size)
		{
			// Create the vertex buffer.
			Device* device = DeviceManager::GetDevice();                                                                                                                                                                                                                                     
			m_VertexBuffer = device->CreateVertexBuffer(size);
		}

		VertexBuffer::~VertexBuffer()
		{
			Device* device = DeviceManager::GetDevice();
			ID3D11DeviceContext& dc = device->GetNativeContext();
			dc.Unmap(m_VertexBuffer, 0);
			m_MappedResource.reset();
		}

		bool VertexBuffer::Bind()
		{
			ResetSubResource(m_MappedResource);
			Device* device = DeviceManager::GetDevice();
			ID3D11DeviceContext& dc = device->GetNativeContext();
			dc.Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &(*m_MappedResource));
			return true;
		}

		bool VertexBuffer::UnBind()
		{
			Device* device = DeviceManager::GetDevice();
			ID3D11DeviceContext& dc = device->GetNativeContext();
			dc.Unmap(m_VertexBuffer, 0);
			return true;
		}

		bool VertexBuffer::AddVertices(float* vertices)
		{
			memcpy(m_MappedResource->pData, vertices, sizeof(vertices));
			return true;
		}

		void VertexBuffer::ResetSubResource(SubResource& subres)
		{
			subres.reset();
			subres = std::make_shared<D3D11_MAPPED_SUBRESOURCE>();
			ZeroMemory(&(*subres), sizeof(D3D11_MAPPED_SUBRESOURCE));
		}

		//-----------------------------------------------------------------------------
		// Index Buffer Member Funtions
		//-----------------------------------------------------------------------------
		IndexBuffer::IndexBuffer(unsigned int size)
		{
			// Create the buffer with the device.
			Device* device = DeviceManager::GetDevice();
			ID3D11DeviceContext& dc = device->GetNativeContext();
			m_IndexBuffer = device->CreateIndexBuffer(size);
		}

		IndexBuffer::~IndexBuffer()
		{
			Device* device = DeviceManager::GetDevice();
			ID3D11DeviceContext& dc = device->GetNativeContext();
			dc.Unmap(m_IndexBuffer, 0);
			m_MappedResource.reset();
		}

		bool IndexBuffer::Bind()
		{
			ResetSubResource(m_MappedResource);
			Device* device = DeviceManager::GetDevice();
			ID3D11DeviceContext& dc = device->GetNativeContext();
			dc.Map(m_IndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &(*m_MappedResource));
			return true;
		}

		bool IndexBuffer::UnBind()
		{
			Device* device = DeviceManager::GetDevice();
			ID3D11DeviceContext& dc = device->GetNativeContext();
			dc.Unmap(m_IndexBuffer, 0);
			return true;
		}

		bool IndexBuffer::AddIndices(unsigned int* indices)
		{
			memcpy(m_MappedResource->pData, indices, sizeof(indices));
			return true;
		}

		void IndexBuffer::ResetSubResource(SubResource& subres)
		{
			subres.reset();
			subres = std::make_shared<D3D11_MAPPED_SUBRESOURCE>();
			ZeroMemory(&(*subres), sizeof(D3D11_MAPPED_SUBRESOURCE));
		}
	} // namespace DirectX11
} // namespace FZLib