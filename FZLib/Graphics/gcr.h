/*********************************************************************
 * @file   gcr.h
 * @brief  �׷��Ƚ� ���̺귯������ ���������� ���Ǵ� ���ҽ� ����
 *
 * @author FuJiGraphics
 * @date   2024/03/08
 *********************************************************************/

#pragma once
#ifndef __FZ_LIBRARY_GRAPHICS_COMMON_RESOURCES_H_
#define __FZ_LIBRARY_GRAPHICS_COMMON_RESOURCES_H_

 // standard library headers
#include <string>
#include <vector>
#include <map>

// DLL Export Macros
#ifdef FZLIB_EXPORTS
#define FZLIB_API __declspec(dllexport)
#else
#define FZLIB_API __declspec(dllimport)
#endif


// Constant Variables
namespace FZLib {
	/**
	 * @brief	�������� ���� RGB ����ü
	 * @details	����� ��� float Ÿ��
	 */
	struct RGB {
		float R, G, B;
	};

	/**
	 * @brief	�������� ���� RGBA ����ü
	 * @details ����� ��� float Ÿ��
	 */
	struct RGBA {
		float R, G, B, A;
	};

	/**
	 * @brief	���� ��ü�� ��缭
	 * @details GraphicsAPIŸ�� ��	
	 */
	struct Specification
	{
		// Graphics API Types
		inline static const std::string&&
			OpenGL		= "OpenGL",
			Vulkan		= "Vulkan",
			DirectX11	= "DirectX11",
			DirectX12	= "DirectX12",
			WebGPU		= "WebGPU",
			None		= "None";
	};
}

#endif