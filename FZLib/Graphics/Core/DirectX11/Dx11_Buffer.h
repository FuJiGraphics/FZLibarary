/*********************************************************************
 * @file   Dx11_Buffer.h
 * @brief  렌더러에서 사용되는 버퍼 모음
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
	 * @details		정점들을 저장하는 버퍼 클래스
	 *********************************************************************/
	class FZLIB_API Dx11_VertexBuffer : public VertexBuffer
	{
		using SubResource = std::shared_ptr<D3D11_MAPPED_SUBRESOURCE>;
	public:
		/**
		 * @brief		정점 버퍼의 생성자
		 * @param[in]	size : 정점 버퍼의 바이트 크기
		 */
		Dx11_VertexBuffer(unsigned int size);
		virtual ~Dx11_VertexBuffer();

	public: // Vertex Buffer Interface
		/**
		 * @brief	정점 버퍼를 바인딩합니다.
		 * @return	bool : 바인딩된 결과
		 */
		virtual bool Bind() final;
		/**
		 * @brief	정점 버퍼의 바인딩을 해제합니다.
		 * @return	bool : 바인딩 해제 결과
		 */
		virtual bool UnBind() final;
		/**
		 * @brief	정점 데이터를 버퍼에 추가합니다.
		 * @return	bool : 결과 (true/false)
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
	 * @details		정점에 대한 인덱스들을 저장하는 버퍼 클래스
	 *********************************************************************/
	class FZLIB_API Dx11_IndexBuffer : public IndexBuffer
	{
		using SubResource = std::shared_ptr<D3D11_MAPPED_SUBRESOURCE>;
	public: // Create Index Buffer Instance
		Dx11_IndexBuffer(unsigned int size);
		virtual ~Dx11_IndexBuffer();

	public: // Index Buffer Interface
		/**
		 * @brief	인덱스 버퍼를 바인딩합니다.
		 * @return	bool : 바인딩된 결과
		 */
		virtual bool Bind() final;
		/**
		 * @brief	인덱스 버퍼의 바인딩을 해제합니다.
		 * @return	bool : 바인딩 해제 결과
		 */
		virtual bool UnBind() final;
		/**
		 * @brief	인덱스 데이터를 버퍼에 추가합니다.
		 * @return	bool : 결과 (true/false)
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