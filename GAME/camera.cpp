
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "gameobject.h"
#include "camera.h"


void CCamera::Init()
{
	//m_DefaultForward = XMVectorSet(0.f, 0.f, 1.f, 0.f);
	//m_DefaultRight = XMVectorSet(1.f, 0.f, 0.f, 0.f);
	//m_CamForward = XMVectorSet(0.f, 0.f, 1.f, 0.f);
	//m_CamRight = XMVectorSet(1.f, 0.f, 0.f, 0.f);
	
	m_Position = XMFLOAT3(0.0f, 10.0f, -15.0f);
	m_Rotation = XMFLOAT3(0.5f, 0.0f, 0.0f);


	m_Viewport.left = 0;
	m_Viewport.top = 0;
	m_Viewport.right = SCREEN_WIDTH;
	m_Viewport.bottom = SCREEN_HEIGHT;

}


void CCamera::Uninit()
{

}


void CCamera::Update()
{
	// �ړ�
	if (CInput::GetKeyPress('A')) {		// ��
		m_Position.x -= 0.1f;
	}
	if (CInput::GetKeyPress('D')) {		// �E
		m_Position.x += 0.1f;
	}
	if (CInput::GetKeyPress('W')) {		// �O��
		m_Position.z += 0.1f;
	}
	if (CInput::GetKeyPress('S')) {		// ���
		m_Position.z -= 0.1f;
	}

	// ����
	if (CInput::GetKeyPress(VK_RIGHT)) {
		m_Rotation.y += 0.01f;
	}
	else if (CInput::GetKeyPress(VK_LEFT)) {
		m_Rotation.y -= 0.01f;
	}
	else if (CInput::GetKeyPress(VK_UP)) {
		m_Rotation.x -= 0.01f;
	}
	else if (CInput::GetKeyPress(VK_DOWN)) {
		m_Rotation.x += 0.01f;
	}

	// �㏸���~
	if (CInput::GetKeyPress(VK_LSHIFT)) {		// ��
		m_Position.y -= 0.5f;
	}
	else if (CInput::GetKeyPress(VK_RSHIFT)) {		// ��
		m_Position.y += 0.5f;
	}

}


void CCamera::Draw()
{

	// �r���[�|�[�g�ݒ�
	D3D11_VIEWPORT dxViewport;
	dxViewport.Width = (float)(m_Viewport.right - m_Viewport.left);
	dxViewport.Height = (float)(m_Viewport.bottom - m_Viewport.top);
	dxViewport.MinDepth = 0.0f;
	dxViewport.MaxDepth = 100.0f;
	dxViewport.TopLeftX = (float)m_Viewport.left;
	dxViewport.TopLeftY = (float)m_Viewport.top;

	CRenderer::GetDeviceContext()->RSSetViewports(1, &dxViewport);



	// �r���[�}�g���N�X�ݒ�(�ړ��͂����œ���Ă�)
	m_InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);	// ����
	m_InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);			// �ړ�	// ���[�p�Ɋ|���Z���Ă�

	XMVECTOR det;
	m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);	// �t�s��

	CRenderer::SetViewMatrix(&m_ViewMatrix);	// �r���[�s���n���Ă�����

	// �v���W�F�N�V�����}�g���N�X�ݒ�
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, dxViewport.Width / dxViewport.Height, 1.0f, 1000.0f);

	CRenderer::SetProjectionMatrix(&m_ProjectionMatrix);

	{
		ImGui::Begin("Camera Move");

		ImGui::Text("X:%.2f", m_Position.x); ImGui::SameLine();
		ImGui::Text("Y:%.2f", m_Position.y); ImGui::SameLine();
		ImGui::Text("Z:%.2f", m_Position.z);

		ImGui::End();
	}

}


// �ȒP�ȃJ�����O�A�X�N���[���J�����O
bool CCamera::GetVisibility(XMFLOAT3 Position)
{
	XMVECTOR worldPos, viewPos, projPos;
	XMFLOAT3 projPosF;
	worldPos = XMLoadFloat3(&Position);
	viewPos = XMVector3TransformCoord(worldPos, m_ViewMatrix);
	projPos = XMVector3TransformCoord(viewPos, m_ProjectionMatrix);
	XMStoreFloat3(&projPosF, projPos);

	if (-1.0f < projPosF.x && projPosF.x < 1.0f && -1.0f < projPosF.y && projPosF.y < 1.0f && 0 < projPosF.z && projPosF.z < 1.0f)
	{
		return true;
	}
	return false;

}