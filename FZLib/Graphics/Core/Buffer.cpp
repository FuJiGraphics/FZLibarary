/*********************************************************************
 * @file   Buffer.cpp
 * @brief  ���������� ���Ǵ� ���� ����
 * 
 * @author FuJiGraphics
 * @date   2024/03/08
 *********************************************************************/

#include <pch.h>
#include "Buffer.h"

// TODO : Include
#include <Graphics/Core/DirectX11/Dx11_Buffer.h>

namespace FZLib {

	VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size)
	{
		return nullptr;
	}

	VertexBuffer* VertexBuffer::Create(unsigned int size)
	{
		return new Dx11_VertexBuffer(size);
	}

} // namespace FZLib
