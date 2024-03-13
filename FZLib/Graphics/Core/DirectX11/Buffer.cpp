/*********************************************************************
 * @file   Buffer.cpp
 * @brief  ���������� ���Ǵ� ���� ����
 *
 * @author FuJiGraphics
 * @date   2024/03/08
 *********************************************************************/

#include <pch.h>
#include "Buffer.h"
#include "Helper/DeviceManager.h"
#include "Helper/ResourceGenerator.h"

namespace FZLib {
	namespace DirectX11 {
		//-----------------------------------------------------------------------------
		// Vertex Buffer Member Funtions
		//-----------------------------------------------------------------------------
		VertexBuffer::VertexBuffer(unsigned int size)
		{
			// Create the vertex buffer.
			auto& deviceManager = Helper::DeviceManager::GetInstance();
			auto& [device, deviceContext] = deviceManager.GetFirstDeviceAndDeviceContext();
			auto& resGenerator = Helper::ResourceGenerator::GetInstance(device, deviceContext);
			m_VertexBuffer = resGenerator.CreateVertexBuffer(size, true, false);
		}

		VertexBuffer::~VertexBuffer()
		{
			auto& deviceManager = Helper::DeviceManager::GetInstance();
			ID3D11DeviceContext* dc = deviceManager.GetFirstDeviceContext();
			dc->Unmap(m_VertexBuffer, 0);
			m_MappedResource.reset();
		}

		bool VertexBuffer::Bind()
		{
			ResetSubResource(m_MappedResource);
			auto& deviceManager = Helper::DeviceManager::GetInstance();
			ID3D11DeviceContext* dc = deviceManager.GetFirstDeviceContext();
			dc->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &(*m_MappedResource));
			return true;
		}

		bool VertexBuffer::UnBind()
		{
			auto& deviceManager = Helper::DeviceManager::GetInstance();
			ID3D11DeviceContext* dc = deviceManager.GetFirstDeviceContext();
			dc->Unmap(m_VertexBuffer, 0);
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
			auto& deviceManager = Helper::DeviceManager::GetInstance();
			auto&[device, deviceContext] = deviceManager.GetFirstDeviceAndDeviceContext();
			auto& resGenerator = Helper::ResourceGenerator::GetInstance(device, deviceContext);
			m_IndexBuffer = resGenerator.CreateIndexBuffer(size, true);
		}

		IndexBuffer::~IndexBuffer()
		{
			auto& deviceManager = Helper::DeviceManager::GetInstance();
			ID3D11DeviceContext* dc = deviceManager.GetFirstDeviceContext();
			dc->Unmap(m_IndexBuffer, 0);
			m_MappedResource.reset();
		}

		bool IndexBuffer::Bind()
		{
			ResetSubResource(m_MappedResource);
			auto& deviceManager = Helper::DeviceManager::GetInstance();
			ID3D11DeviceContext* dc = deviceManager.GetFirstDeviceContext();
			dc->Map(m_IndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &(*m_MappedResource));
			return true;
		}

		bool IndexBuffer::UnBind()
		{
			auto& deviceManager = Helper::DeviceManager::GetInstance();
			ID3D11DeviceContext* dc = deviceManager.GetFirstDeviceContext();
			dc->Unmap(m_IndexBuffer, 0);
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