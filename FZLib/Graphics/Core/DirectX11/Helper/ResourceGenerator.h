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

#include <Graphics/Core/DirectX11/CoreRef.h>
#include <Graphics/gcr.h>

namespace FZLib {
	namespace DirectX11 {
		namespace Helper {
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
				 * @brief		ResourceGenerator의 인스턴스를 생성
				 * @param[in]	device	: 리소스 생성에 사용될 디바이스
				 * @param[in]	deviceContext	: 리소스 생성에 사용될 디바이스 컨텍스트
				 * @return		ResourceGenerator&	: ResourceGenerator의 객체 레퍼런스
				 */
				static ResourceGenerator&	GetInstance(ID3D11Device& device, ID3D11DeviceContext& deviceContext);
				//-----------------------------------------------------------------------------


				//-----------------------------------------------------------------------------
				// Constructor and destructor
			public:
				ResourceGenerator();
				~ResourceGenerator() = default;
				//-----------------------------------------------------------------------------


				//-----------------------------------------------------------------------------
				// Export Interfaces
			public:
				/**
				 * @brief	정점 버퍼를 생성
				 * @param[in]	size	: 생성될 버퍼의 바이트 크기
				 * @param[in]	dynamic	: CPU에서 동적으로 쓸 수 있는 버퍼 타입인지 여부
				 * @param[in]	streamout	: 렌더링된 결과에 출력 대상으로 사용할 지 여부
				 * @param[in]	pData		: 정점 데이터
				 * @return	ID3D11Buffer	: 생성된 정점 버퍼 (실패 시, nullptr를 반환)
				 */
				ID3D11Buffer*		CreateVertexBuffer(unsigned int size, bool dynamic, bool streamout, D3D11_SUBRESOURCE_DATA* pData = nullptr);
				/**
				 * @brief	인덱스 버퍼를 생성
				 * @param[in]	size		: 생성될 버퍼의 바이트 크기
				 * @param[in]	dynamic		: CPU에서 동적으로 쓸 수 있는 버퍼 타입인지 여부
				 * @param[in]	pData		: 인덱스 데이터
				 * @return	ID3D11Buffer	: 생성된 정점 버퍼 (실패 시, nullptr를 반환)
				 */
				ID3D11Buffer*		CreateIndexBuffer(unsigned int size, bool dynamic, D3D11_SUBRESOURCE_DATA* pData = nullptr);
				/**
				 * @brief	상수 버퍼를 생성
				 * @param[in]	size		: 생성될 버퍼의 바이트 크기
				 * @param[in]	dynamic		: CPU에서 동적으로 쓸 수 있는 버퍼 타입인지 여부
				 * @param[in]	CPUupdates	: CPU 권한 활성화 여부
				 * @return	ID3D11Buffer	: 생성된 상수 버퍼 (실패 시, nullptr를 반환)
				 */
				ID3D11Buffer*		CreateConstantBuffer(unsigned int size, bool dynamic, bool CPUupdates, D3D11_SUBRESOURCE_DATA* pData = nullptr);
				/**
				 * @brief	구조적 버퍼를 생성
				 * @param[in]	size		: 생성될 버퍼의 바이트 크기
				 * @param[in]	dynamic		: CPU에서 동적으로 쓸 수 있는 버퍼 타입인지 여부
				 * @param[in]	CPUupdates	: CPU 권한 활성화 여부
				 * @return	ID3D11Buffer	: 생성된 상수 버퍼 (실패 시, nullptr를 반환)
				 */
				ID3D11Buffer*		CreateStructuredBuffer(unsigned int count, unsigned int structSize, bool CPUwritable, bool GPUwritable, D3D11_SUBRESOURCE_DATA* pData = nullptr);
				//-----------------------------------------------------------------------------


				//-----------------------------------------------------------------------------
				// Private member functions
			private:
				/**
				 * @brief		현재 ResourceGenerator에 디바이스와 디바이스 컨텍스트에 대한 상태 객체를 저장
				 * @details		리소스 생성에 필요한 디바이스와 디바이스 컨텍스트를 매 인스턴스 호출 시마다 쿼리합니다.
				 *
				 * @param[in]	device	: 리소스 생성에 사용될 디바이스
				 * @param[in]	deviceContext	: 리소스 생성에 사용될 디바이스 컨텍스트
				 */
				void				SetDeviceAndDeviceContext(ID3D11Device& device, ID3D11DeviceContext& deviceContext);
				//-----------------------------------------------------------------------------

				//-----------------------------------------------------------------------------
				// Member variables
			private:
				static std::unique_ptr<ResourceGenerator>		s_pInstance;
				ID3D11Device*									m_pDevice;
				ID3D11DeviceContext*							m_pDeviceContext;
				//-----------------------------------------------------------------------------
			}; // class ResourceGenerator

		} // namespace Helper
	} // namespace DirectX11
} // namespace FZLib

#endif
