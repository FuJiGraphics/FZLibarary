/*********************************************************************
 * @file   gcr.h
 * @brief  그래픽스 라이브러리에서 공통적으로 사용되는 리소스 모음
 *
 * @author FuJiGraphics
 * @date   2024/03/08
 *********************************************************************/

#pragma once
#ifndef __FZ_LIBRARY_GRAPHICS_COMMON_RESOURCES_H_
#define __FZ_LIBRARY_GRAPHICS_COMMON_RESOURCES_H_

 // standard library headers
#include <iostream>
#include <string>
#include <vector>
#include <map>

// DLL Export Macros
#ifdef FZLIB_USAGE_DLL
	#ifdef FZLIB_EXPORTS
		#define FZLIB_API __declspec(dllexport)
	#else
		#define FZLIB_API __declspec(dllimport)
	#endif
#else
	#define FZLIB_API
#endif

namespace FZLib {

	// Custom type info
	using	FZuint		= std::uint32_t;
	using	FZint		= std::int32_t;
	using	FZfloat		= std::float_t;
	using	FZbool		= bool;
	enum {  FZtrue		= true
		 ,	FZfalse		= false
	}; 

	/**
	 * @brief	렌더링을 위한 RGB 구조체
	 * @details	멤버는 모두 float 타입
	 */
	struct RGB {
		float R, G, B;
	};

	/**
	 * @brief	렌더링을 위한 RGBA 구조체
	 * @details 멤버는 모두 float 타입
	 */
	struct RGBA {
		float R, G, B, A;
	};

	/**
	 * @brief	현재 객체의 사양서
	 * @details GraphicsAPI타입 등	
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
