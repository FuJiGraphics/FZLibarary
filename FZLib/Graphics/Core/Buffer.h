/*********************************************************************
 * @file   Buffer.h
 * @brief  ���������� ���Ǵ� ���� ����
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
	 * @brief		���� ���� Ŭ����
	 * @details		�������� �����ϴ� ���� Ŭ����
	 *********************************************************************/
	class FZLIB_API VertexBuffer 
	{
	public: // Create Vertex Buffer Instance
		/**
		 * @brief		���� ���� ����
		 * @details	
		 * - �� ������ ���� ���۸� �����մϴ�.
		 * - ���ۿ� ���� ����̽� ������ ������ Ÿ�ӿ� �����˴ϴ�.
		 * @param[in]	vertices : ������ ���� �迭
		 * @param[in]	size : ������ ���� �迭�� ����Ʈ ũ��
		 * @return		VertexBuffer* : ������ ���� ������ ��ü ������
		 */
		static VertexBuffer* Create(float* vertices, unsigned int size);
		/**
		 * @brief		�� ���� ���� ����
		 * @details		���ۿ� ���� ����̽� ������ ������ Ÿ�ӿ� �����˴ϴ�.
		 * @param[in]	size : ���� ������ ����Ʈ ũ��
		 * @return		VertexBuffer* : ������ ���� ������ ��ü ������
		 */
		static VertexBuffer* Create(unsigned int size);

	public: // Vertex Buffer Interface
		/**
		 * @brief	���� ���۸� ���ε��մϴ�.
		 * @return	bool : ���ε��� ���
		 */
		virtual bool Bind() = 0;
		/**
		 * @brief	���� ������ ���ε��� �����մϴ�.
		 * @return	bool : ���ε� ���� ���
		 */
		virtual bool UnBind() = 0;

	};


} // namespace FZLib

#endif
