/*********************************************************************
 * @file   Dx11_Renderer2D.h
 * @brief  DirectX11 에서 사용되는 리소스 생성 헬퍼 클래스
 *
 * @author FuJiGraphics
 * @date   2024/03/12
 *********************************************************************/

#pragma once
#ifndef __FZ_LIBRARY_RESOURCE_GENERATOR_DIRECTX11__
#define	__FZ_LIBRARY_RESOURCE_GENERATOR_DIRECTX11__

#include "../CoreRef.h"
#include "../../../gcr.h"
#include "../Device.h"

namespace FZLib {
	namespace DirectX11 {
		namespace Helpers {
			/**
			 * @brief		DirectX11 리소스를 생성하는 헬퍼 클래스
			 * @details		사용하기 위해서는 인스턴스 생성 시 device 및 device context를 제공해야 합니다.
			 */
			class FZLIB_API ResourceGenerator
			{
				//-----------------------------------------------------------------------------
				// Static functions
			public:
				/**
				 * @brief		ResourceGenerator의 인스턴스를 반환
				 * @param[in]	device	: device의 객체
				 * @return		ResourceGenerator&	: ResourceGenerator의 객체 레퍼런스
				 */
				static ResourceGenerator&	GetInstance(Device& device);
				//-----------------------------------------------------------------------------


				//-----------------------------------------------------------------------------
				// Constructor and destructor
			public:
				ResourceGenerator() = default;
				~ResourceGenerator() = default;
				//-----------------------------------------------------------------------------


				//-----------------------------------------------------------------------------
				// Export Interfaces
			public:
				/**
				 * @brief	Vertex Buffer를 생성합니다.
				 * @param[in]	size		: 생성될 버퍼의 바이트 크기
				 * @param[in]	dynamic		: CPU에서 동적으로 쓸 수 있는 버퍼 타입인지 여부
				 * @param[in]	pData		: 정점 데이터
				 * @return	ID3D11Buffer	: 생성된 정점 버퍼 (실패 시, nullptr를 반환)
				 */
				ID3D11Buffer*		CreateVertexBuffer(FZuint size, FZbool dynamic, FZbool streamout, D3D11_SUBRESOURCE_DATA* pData);
				/**
				 * @brief	Static Vertex Buffer를 생성합니다.
				 * @details	
				 * - static 속성으로 해당 버퍼는 할당 이후 재사용이 불가합니다.
				 * @param[in]	vertices	: 버퍼에 담을 float 정점 데이터 배열
				 * @param[in]	size		: vertices의 총 바이트 크기
				 * @param[in]	streamOut	: 스트림 출력 활성화 여부
				 * @return	ID3D11Buffer	: 생성된 정점 버퍼 (실패 시, nullptr를 반환)
				 */
				ID3D11Buffer*		CreateStaticVertexBuffer(FZfloat* vertices, FZuint size, FZbool streamOut = false);
				/**
				 * @brief	Dynamic Vertex Buffer를 생성합니다.
				 * @details	
				 * - dynamic 속성으로 해당 버퍼는 할당 후 재사용 가능합니다.
				 * @param[in]	size		: 생성할 버퍼의 바이트 크기
				 * @param[in]	streamout	: 스트림 출력 활성화 여부
				 * @return	ID3D11Buffer	: 생성된 정점 버퍼 (실패 시, nullptr를 반환)
				 */
				ID3D11Buffer*		CreateDynamicVertexBuffer(FZuint size, FZbool streamOut = false);



				/**
				 * @brief	Index Buffer를 생성합니다.
				 * @param[in]	size		: 생성될 버퍼의 바이트 크기
				 * @param[in]	dynamic		: CPU에서 동적으로 쓸 수 있는 버퍼 타입인지 여부
				 * @param[in]	pData		: 인덱스 데이터
				 * @return	ID3D11Buffer	: 생성된 인덱스 버퍼 (실패 시, nullptr를 반환)
				 */
				ID3D11Buffer*		CreateIndexBuffer(FZuint size, FZbool dynamic, D3D11_SUBRESOURCE_DATA* pData = nullptr);
				/**
				 * @brief	Static Index Buffer를 생성합니다.
				 * @details
				 * - static 속성으로 해당 버퍼는 할당 이후 재사용이 불가합니다.
				 * @param[in]	indices		: 버퍼에 담을 unsigned int index 데이터 배열
				 * @param[in]	size		: index의 총 바이트 크기
				 * @return	ID3D11Buffer	: 생성된 인덱스 버퍼 (실패 시, nullptr를 반환)
				 */
				ID3D11Buffer*		CreateStaticIndexBuffer(FZuint* indices, FZuint size);
				/**
				 * @brief	Dynamic Index Buffer를 생성합니다.
				 * @details
				 * - dynamic 속성으로 해당 버퍼는 할당 후 재사용 가능합니다.
				 * @param[in]	size		: 생성할 버퍼의 바이트 크기
				 * @return	ID3D11Buffer	: 생성된 인덱스 버퍼 (실패 시, nullptr를 반환)
				 */
				ID3D11Buffer*		CreateDynamicIndexBuffer(FZuint size);



				/**
				 * @brief	상수 버퍼를 생성
				 * @param[in]	size		: 생성될 버퍼의 바이트 크기
				 * @param[in]	dynamic		: CPU에서 동적으로 쓸 수 있는 버퍼 타입인지 여부
				 * @param[in]	CPUupdates	: CPU 권한 활성화 여부
				 * @return	ID3D11Buffer	: 생성된 상수 버퍼 (실패 시, nullptr를 반환)
				 */
				ID3D11Buffer*		CreateConstantBuffer(FZuint size, FZbool dynamic, FZbool CPUupdates, D3D11_SUBRESOURCE_DATA* pData = nullptr);
				/**
				 * @brief	구조적 버퍼를 생성
				 * @param[in]	size		: 생성될 버퍼의 바이트 크기
				 * @param[in]	dynamic		: CPU에서 동적으로 쓸 수 있는 버퍼 타입인지 여부
				 * @param[in]	CPUupdates	: CPU 권한 활성화 여부
				 * @return	ID3D11Buffer	: 생성된 상수 버퍼 (실패 시, nullptr를 반환)
				 */
				ID3D11Buffer*		CreateStructuredBuffer(FZuint count, FZuint structSize, FZbool CPUwritable, FZbool GPUwritable, D3D11_SUBRESOURCE_DATA* pData = nullptr);

				ID3D11ShaderResourceView*	CreateBufferShaderResourceView(ID3D11Resource* pResource);
				ID3D11UnorderedAccessView*	CreateBufferUnorderedAccessView(ID3D11Resource* pResource);
				//-----------------------------------------------------------------------------




				//-----------------------------------------------------------------------------
				// static variables
			private:
				static std::unique_ptr<ResourceGenerator>		s_pInstance;
				static ID3D11Device*							s_pCurrUsedDevice;
				static ID3D11DeviceContext*						s_pCurrUsedContext;

				//-----------------------------------------------------------------------------
			}; // class ResourceGenerator

		} // namespace Helper
	} // namespace DirectX11
} // namespace FZLib

#endif
