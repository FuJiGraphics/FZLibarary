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

namespace FZLib {

	class FZLIB_API Dx11_VertexBuffer : public VertexBuffer
	{
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

	};

} // namespace FZLib

#endif