/*********************************************************************
 * @file   Dx11_Buffer.h
 * @brief  ���������� ���Ǵ� ���� ����
 *
 * @author FuJiGraphics
 * @date   2024/03/08
 *********************************************************************/

#pragma once
#ifndef __FZ_LIBRARY_VERTEXBUFFER_DIRECTX11__
#define __FZ_LIBRARY_VERTEXBUFFER_DIRECTX11__

#include "Dx11_CoreRef.h"
#include <Graphics/Core/Buffer.h>
#include "Dx11_DeviceManager.h"

namespace FZLib {

	/*********************************************************************
	 * @brief		Vertex Buffer class
	 * @details		�������� �����ϴ� ���� Ŭ����
	 *********************************************************************/
	class FZLIB_API Dx11_VertexBuffer : public VertexBuffer
	{
		using SubResource = std::shared_ptr<D3D11_MAPPED_SUBRESOURCE>;
	public:
		/**
		 * @brief		���� ������ ������
		 * @param[in]	size : ���� ������ ����Ʈ ũ��
		 */
		Dx11_VertexBuffer(unsigned int size);
		virtual ~Dx11_VertexBuffer();

	public: // Vertex Buffer Interface
		/**
		 * @brief	���� ���۸� ���ε��մϴ�.
		 * @return	bool : ���ε��� ���
		 */
		virtual bool Bind() final;
		/**
		 * @brief	���� ������ ���ε��� �����մϴ�.
		 * @return	bool : ���ε� ���� ���
		 */
		virtual bool UnBind() final;
		/**
		 * @brief	���� �����͸� ���ۿ� �߰��մϴ�.
		 * @return	bool : ��� (true/false)
		 */
		virtual bool AddVertices(float* vertices) final;

	public:
		void ResetSubResource(SubResource& subres);

	private:
		ID3D11Buffer*			m_VertexBuffer;
		SubResource				m_MappedResource;
	};

	/*********************************************************************
	 * @brief		Index Buffer class
	 * @details		������ ���� �ε������� �����ϴ� ���� Ŭ����
	 *********************************************************************/
	class FZLIB_API Dx11_IndexBuffer : public IndexBuffer
	{
		using SubResource = std::shared_ptr<D3D11_MAPPED_SUBRESOURCE>;
	public: // Create Index Buffer Instance
		Dx11_IndexBuffer(unsigned int size);
		virtual ~Dx11_IndexBuffer();

	public: // Index Buffer Interface
		/**
		 * @brief	�ε��� ���۸� ���ε��մϴ�.
		 * @return	bool : ���ε��� ���
		 */
		virtual bool Bind() final;
		/**
		 * @brief	�ε��� ������ ���ε��� �����մϴ�.
		 * @return	bool : ���ε� ���� ���
		 */
		virtual bool UnBind() final;
		/**
		 * @brief	�ε��� �����͸� ���ۿ� �߰��մϴ�.
		 * @return	bool : ��� (true/false)
		 */
		virtual bool AddIndices(unsigned int* indices) final;

	public:
		void ResetSubResource(SubResource& subres);

	private:
		ID3D11Buffer*		m_IndexBuffer;
		SubResource			m_MappedResource;

	};

} // namespace FZLib

#endif