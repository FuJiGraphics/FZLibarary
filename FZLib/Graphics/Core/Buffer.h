/*********************************************************************
 * @file   Buffer.h
 * @brief  렌더러에서 사용되는 버퍼 모음
 * 
 * @author FuJiGraphics
 * @date   2024/03/08
 *********************************************************************/

#pragma once
#ifndef __FZ_LIBRARY_RENDERER2D__
#define __FZ_LIBRARY_RENDERER2D__

#include <Graphics/gcr.h>

namespace FZLib {

	/*********************************************************************
	 * @brief		정점 버퍼 클래스
	 * @details		정점들을 저장하는 버퍼 클래스
	 *********************************************************************/
	class FZLIB_API VertexBuffer 
	{
	public: // Create Vertex Buffer Instance
		/**
		 * @brief		정점 버퍼 생성
		 * @details	
		 * - 각 정점에 대한 버퍼를 생성합니다.
		 * - 버퍼에 대한 디바이스 종류는 컴파일 타임에 결정됩니다.
		 * @param[in]	vertices : 저장할 정점 배열
		 * @param[in]	size : 저장할 정점 배열의 바이트 크기
		 * @return		VertexBuffer* : 생성한 정점 버퍼의 객체 포인터
		 */
		static VertexBuffer* Create(float* vertices, unsigned int size);
		/**
		 * @brief		빈 정점 버퍼 생성
		 * @details		버퍼에 대한 디바이스 종류는 컴파일 타임에 결정됩니다.
		 * @param[in]	size : 정점 버퍼의 바이트 크기
		 * @return		VertexBuffer* : 생성한 정점 버퍼의 객체 포인터
		 */
		static VertexBuffer* Create(unsigned int size);

	public: // Vertex Buffer Interface
		/**
		 * @brief	정점 버퍼를 바인딩합니다.
		 * @return	bool : 바인딩된 결과
		 */
		virtual bool Bind() = 0;
		/**
		 * @brief	정점 버퍼의 바인딩을 해제합니다.
		 * @return	bool : 바인딩 해제 결과
		 */
		virtual bool UnBind() = 0;

	};


} // namespace FZLib

#endif
