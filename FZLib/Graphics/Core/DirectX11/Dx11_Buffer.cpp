/*********************************************************************
 * @file   Dx11_Buffer.cpp
 * @brief  ���������� ���Ǵ� ���� ����
 *
 * @author FuJiGraphics
 * @date   2024/03/08
 *********************************************************************/

#include <pch.h>
#include "Dx11_Buffer.h"

namespace FZLib {

//-----------------------------------------------------------------------------
// Vertex Buffer Member Funtions
//-----------------------------------------------------------------------------
	Dx11_VertexBuffer::Dx11_VertexBuffer(unsigned int size)
	{
		// ���� ���� ����ü ����
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.ByteWidth = size;						// ������ ũ��(����Ʈ)
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;				// https://learn.microsoft.com/ko-kr/windows/win32/api/d3d11/ne-d3d11-d3d11_usage
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ���� Ÿ��
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;
		
		D3D11_SUBRESOURCE_DATA vData;
		ZeroMemory(&vData, sizeof(D3D11_SUBRESOURCE_DATA));
		vData.pSysMem = nullptr;
		vData.SysMemPitch = 0;
		vData.SysMemSlicePitch = 0;

		// Create the vertex buffer.
		auto& deviceManager = DeviceManager::GetInstance();
		ID3D11Device& device = deviceManager.GetDevice();
		device.CreateBuffer(&bufferDesc, &vData, &m_VertexBuffer);
	}

	Dx11_VertexBuffer::~Dx11_VertexBuffer()
	{
		auto& deviceManager = DeviceManager::GetInstance();
		ID3D11DeviceContext& dc = deviceManager.GetDeviceContext();
		dc.Unmap(m_VertexBuffer, 0);
		m_MappedResource.reset();
	}

	bool Dx11_VertexBuffer::Bind()
	{
		auto& deviceManager = DeviceManager::GetInstance();
		ID3D11DeviceContext&  dc = deviceManager.GetDeviceContext();
		ResetSubResource(m_MappedResource);
		dc.Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &(*m_MappedResource));
		return true;
	}

	bool Dx11_VertexBuffer::UnBind()
	{
		auto& deviceManager = DeviceManager::GetInstance();
		ID3D11DeviceContext& dc = deviceManager.GetDeviceContext();
		dc.Unmap(m_VertexBuffer, 0);
		return true;
	}

	bool Dx11_VertexBuffer::AddVertices(float* vertices)
	{
		memcpy(m_MappedResource->pData, vertices, sizeof(vertices));
		return true;
	}

	void Dx11_VertexBuffer::ResetSubResource(SubResource& subres)
	{
		subres.reset();
		subres = std::make_shared<D3D11_MAPPED_SUBRESOURCE>();
		ZeroMemory(&(*subres), sizeof(D3D11_MAPPED_SUBRESOURCE));
	}


//-----------------------------------------------------------------------------
// Index Buffer Member Funtions
//-----------------------------------------------------------------------------
	Dx11_IndexBuffer::Dx11_IndexBuffer(unsigned int size)
	{
		// �ε��� ���� ����ü ����
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.ByteWidth = size;						// ������ ũ��(����Ʈ)
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;				// https://learn.microsoft.com/ko-kr/windows/win32/api/d3d11/ne-d3d11-d3d11_usage
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;		// ���� Ÿ��
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vData;
		ZeroMemory(&vData, sizeof(D3D11_SUBRESOURCE_DATA));
		vData.pSysMem = nullptr;
		vData.SysMemPitch = 0;
		vData.SysMemSlicePitch = 0;

		// Create the buffer with the device.
		auto& deviceManager = DeviceManager::GetInstance();
		ID3D11Device& dc = deviceManager.GetDevice();
		dc.CreateBuffer(&bufferDesc, &vData, &m_IndexBuffer);
	}

	Dx11_IndexBuffer::~Dx11_IndexBuffer()
	{
		auto& deviceManager = DeviceManager::GetInstance();
		ID3D11DeviceContext& dc = deviceManager.GetDeviceContext();
		dc.Unmap(m_IndexBuffer, 0);
		m_MappedResource.reset();
	}

	bool Dx11_IndexBuffer::Bind()
	{
		auto& deviceManager = DeviceManager::GetInstance();
		ID3D11DeviceContext&  dc = deviceManager.GetDeviceContext();
		ResetSubResource(m_MappedResource);
		dc.Map(m_IndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &(*m_MappedResource));
		return true;
	}

	bool Dx11_IndexBuffer::UnBind()
	{
		auto& deviceManager = DeviceManager::GetInstance();
		ID3D11DeviceContext& dc = deviceManager.GetDeviceContext();
		dc.Unmap(m_IndexBuffer, 0);
		return true;
	}

	bool Dx11_IndexBuffer::AddIndices(unsigned int* indices)
	{
		memcpy(m_MappedResource->pData, indices, sizeof(indices));
		return true;
	}

	void Dx11_IndexBuffer::ResetSubResource(SubResource& subres)
	{
		subres.reset();
		subres = std::make_shared<D3D11_MAPPED_SUBRESOURCE>();
		ZeroMemory(&(*subres), sizeof(D3D11_MAPPED_SUBRESOURCE));
	}

} // namespace FZLib