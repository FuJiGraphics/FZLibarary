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
				 * @param[in]	device	: ���ҽ� ������ ���� ����̽�
				 * @param[in]	deviceContext	: ���ҽ� ������ ���� ����̽� ���ؽ�Ʈ
				 * @return		ResourceGenerator&	: ResourceGenerator�� ��ü ���۷���
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
				//-----------------------------------------------------------------------------


				//-----------------------------------------------------------------------------
				// Private member functions
			private:
				/**
				 * @brief		���� ResourceGenerator�� ����̽��� ����̽� ���ؽ�Ʈ�� ���� ���� ��ü�� ����
				 * @details		���ҽ� ������ �ʿ��� ����̽��� ����̽� ���ؽ�Ʈ�� �� �ν��Ͻ� ȣ�� �ø��� �����մϴ�.
				 *
				 * @param[in]	device	: ���ҽ� ������ ���� ����̽�
				 * @param[in]	deviceContext	: ���ҽ� ������ ���� ����̽� ���ؽ�Ʈ
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
