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
#include "DeviceResource.h"

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
				 * @return		ResourceGenerator&	: ResourceGenerator의 객체 레퍼런스
				 */
				static ResourceGenerator&	GetInstance();
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
				 * @brief		DeviceResource의 객체를 반환
				 * @param[in]	deviceName	: 반환하고자 하는 DeviceResource의 이름
				 * @return		DeviceResource*	: Device Resource의 객체 주소 (실패 시 nullptr)
				 */
				DeviceResource*				GetDeviceResource(const std::string& deviceName);
				/**
				 * @brief	현재 Generator에 설정된 Device를 반환
				 * @return	ID3D11Device*	: 현재 설정된 디바이스의 객체 주소 (실패 시 nullptr) 
				 */
				ID3D11Device*				GetCurrentDevice() const;
				/**
				 * @brief	현재 Generator에 설정된 Device Context를 반환
				 * @return	ID3D11Device*	: 현재 설정된 디바이스 컨텍스트의 객체 주소 (실패 시 nullptr)
				 */
				ID3D11DeviceContext*		GetCurrentDeviceContext() const;
				/**
				 * @brief	특정 이름의 디바이스 리소스를 릴리즈한다.
				 * @param[in]	deviceName	: 릴리즈할 디바이스 리소스 명
				 * @return	bool	: 결과(true/false)
				 */
				bool				ReleaseDeviceResource(const std::string& deviceName);
				/**
				 * @brief	현재 디바이스들을 모두 릴리즈한다.
				 */
				bool				ReleaseDeviceResources();                             
				/**
				 * @brief
				 * @details
				 * @param[in]	deviceName	:
				 * @param[in]	hwnd	:
				 * @param[in]	width	:
				 * @param[in]	height	:
				 * @return	bool	:
				 */
				bool				GenerateDeviceResources(const std::string& deviceName, const HWND& hwnd, int width, int height); 
				/**
				 * @brief
				 * @details
				 * @param[in]	deviceName	:
				 * @return	bool	:
				 */
				bool				ApplyDeviceResources(const std::string& deviceName);
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

				ID3D11ShaderResourceView*	CreateBufferShaderResourceView(ID3D11Resource* pResource);
				ID3D11UnorderedAccessView*	CreateBufferUnorderedAccessView(ID3D11Resource* pResource);
				//-----------------------------------------------------------------------------


				//-----------------------------------------------------------------------------
				// Private member functions
			private:
				/**
				 * @brief		현재 ResourceGenerator에 디바이스와 디바이스 컨텍스트에 대한 상태 객체를 저장
				 * @details		리소스 생성에 필요한 디바이스와 디바이스 컨텍스트를 매 인스턴스 호출 시마다 쿼리합니다.
				 *
				 * @param[in]	deviceResource	: 리소스 생성에 사용될 디바이스 리소스
				 */
				void				SetDeviceResource(DeviceResource& deviceResource);
				//-----------------------------------------------------------------------------

				//-----------------------------------------------------------------------------
				// Member variables
			private:
				static std::unique_ptr<ResourceGenerator>		s_pInstance;
				static std::map<std::string, DeviceResource>	s_mDeviceResources;
				static DeviceResource*							s_CurrDeviceResource;
				static ID3D11Device*							s_CurrDevice;
				static ID3D11DeviceContext*						s_CurrDeviceContext;

				//-----------------------------------------------------------------------------
			}; // class ResourceGenerator

		} // namespace Helper
	} // namespace DirectX11
} // namespace FZLib

#endif
