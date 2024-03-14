/*********************************************************************
 * @file   Dx11_Renderer2D.h
 * @brief  DirectX11 ���� ���Ǵ� ���ҽ� ���� ���� Ŭ����
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
			 * @brief		DirectX11 ���ҽ��� �����ϴ� ���� Ŭ����
			 * @details		����ϱ� ���ؼ��� �ν��Ͻ� ���� �� device �� device context�� �����ؾ� �մϴ�.
			 */
			class FZLIB_API ResourceGenerator
			{
				//-----------------------------------------------------------------------------
				// Static functions
			public:
				/**
				 * @brief		ResourceGenerator�� �ν��Ͻ��� ����
				 * @return		ResourceGenerator&	: ResourceGenerator�� ��ü ���۷���
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
				 * @brief		DeviceResource�� ��ü�� ��ȯ
				 * @param[in]	deviceName	: ��ȯ�ϰ��� �ϴ� DeviceResource�� �̸�
				 * @return		DeviceResource*	: Device Resource�� ��ü �ּ� (���� �� nullptr)
				 */
				DeviceResource*				GetDeviceResource(const std::string& deviceName);
				/**
				 * @brief	���� Generator�� ������ Device�� ��ȯ
				 * @return	ID3D11Device*	: ���� ������ ����̽��� ��ü �ּ� (���� �� nullptr) 
				 */
				ID3D11Device*				GetCurrentDevice() const;
				/**
				 * @brief	���� Generator�� ������ Device Context�� ��ȯ
				 * @return	ID3D11Device*	: ���� ������ ����̽� ���ؽ�Ʈ�� ��ü �ּ� (���� �� nullptr)
				 */
				ID3D11DeviceContext*		GetCurrentDeviceContext() const;
				/**
				 * @brief	Ư�� �̸��� ����̽� ���ҽ��� �������Ѵ�.
				 * @param[in]	deviceName	: �������� ����̽� ���ҽ� ��
				 * @return	bool	: ���(true/false)
				 */
				bool				ReleaseDeviceResource(const std::string& deviceName);
				/**
				 * @brief	���� ����̽����� ��� �������Ѵ�.
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
				 * @brief	���� ���۸� ����
				 * @param[in]	size	: ������ ������ ����Ʈ ũ��
				 * @param[in]	dynamic	: CPU���� �������� �� �� �ִ� ���� Ÿ������ ����
				 * @param[in]	streamout	: �������� ����� ��� ������� ����� �� ����
				 * @param[in]	pData		: ���� ������
				 * @return	ID3D11Buffer	: ������ ���� ���� (���� ��, nullptr�� ��ȯ)
				 */
				ID3D11Buffer*		CreateVertexBuffer(unsigned int size, bool dynamic, bool streamout, D3D11_SUBRESOURCE_DATA* pData = nullptr);
				/**
				 * @brief	�ε��� ���۸� ����
				 * @param[in]	size		: ������ ������ ����Ʈ ũ��
				 * @param[in]	dynamic		: CPU���� �������� �� �� �ִ� ���� Ÿ������ ����
				 * @param[in]	pData		: �ε��� ������
				 * @return	ID3D11Buffer	: ������ ���� ���� (���� ��, nullptr�� ��ȯ)
				 */
				ID3D11Buffer*		CreateIndexBuffer(unsigned int size, bool dynamic, D3D11_SUBRESOURCE_DATA* pData = nullptr);
				/**
				 * @brief	��� ���۸� ����
				 * @param[in]	size		: ������ ������ ����Ʈ ũ��
				 * @param[in]	dynamic		: CPU���� �������� �� �� �ִ� ���� Ÿ������ ����
				 * @param[in]	CPUupdates	: CPU ���� Ȱ��ȭ ����
				 * @return	ID3D11Buffer	: ������ ��� ���� (���� ��, nullptr�� ��ȯ)
				 */
				ID3D11Buffer*		CreateConstantBuffer(unsigned int size, bool dynamic, bool CPUupdates, D3D11_SUBRESOURCE_DATA* pData = nullptr);
				/**
				 * @brief	������ ���۸� ����
				 * @param[in]	size		: ������ ������ ����Ʈ ũ��
				 * @param[in]	dynamic		: CPU���� �������� �� �� �ִ� ���� Ÿ������ ����
				 * @param[in]	CPUupdates	: CPU ���� Ȱ��ȭ ����
				 * @return	ID3D11Buffer	: ������ ��� ���� (���� ��, nullptr�� ��ȯ)
				 */
				ID3D11Buffer*		CreateStructuredBuffer(unsigned int count, unsigned int structSize, bool CPUwritable, bool GPUwritable, D3D11_SUBRESOURCE_DATA* pData = nullptr);

				ID3D11ShaderResourceView*	CreateBufferShaderResourceView(ID3D11Resource* pResource);
				ID3D11UnorderedAccessView*	CreateBufferUnorderedAccessView(ID3D11Resource* pResource);
				//-----------------------------------------------------------------------------


				//-----------------------------------------------------------------------------
				// Private member functions
			private:
				/**
				 * @brief		���� ResourceGenerator�� ����̽��� ����̽� ���ؽ�Ʈ�� ���� ���� ��ü�� ����
				 * @details		���ҽ� ������ �ʿ��� ����̽��� ����̽� ���ؽ�Ʈ�� �� �ν��Ͻ� ȣ�� �ø��� �����մϴ�.
				 *
				 * @param[in]	deviceResource	: ���ҽ� ������ ���� ����̽� ���ҽ�
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
