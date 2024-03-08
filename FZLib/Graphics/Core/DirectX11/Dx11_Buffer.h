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

namespace FZLib {

	class FZLIB_API Dx11_VertexBuffer : public VertexBuffer
	{
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

	};

} // namespace FZLib

#endif