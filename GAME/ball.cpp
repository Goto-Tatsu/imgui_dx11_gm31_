#include <list>

// system
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

// gameobject
#include "gameobject.h"
#include "camera.h"
#include "field.h"

// shader
#include "shader3D_model.h"

// resource
#include "model.h"		// �O��"renderer.h"���K�v
#include "modelanimation.h"
#include "player.h"
#include "enemy.h"
#include "ball.h"

// scene
#include "scene.h"

#define SPEED	(0.05f)
#define ANGLE	(0.2f)

void CBall::Init()
{
	m_pShader3D = new Shader3D_Model();
	m_pShader3D->Init("vertexShader3D_model.cso", "pixelShader3D_model.cso");

	m_pModel = new CModel();
	m_pModel->Load("asset/model/miku_01.obj");
	
	m_Position = XMFLOAT3(0.0f, 1.0f, -5.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);


	m_Quaternion = XMQuaternionIdentity();
}


void CBall::Uninit(void)
{
	m_pModel->Unload();
	delete m_pModel;

	m_pShader3D->Uninit();
	delete m_pShader3D;
}


void CBall::Update()
{
	if (CInput::GetKeyPress('K'))
	{
		XMFLOAT3 vz = XMFLOAT3(0.f, 0.f, 1.f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, -ANGLE);

		// ��]���X�V���Ă�̂�Multiply
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
		m_Position.x += SPEED;
	}
	if (CInput::GetKeyPress('H'))
	{
		XMFLOAT3 vz = XMFLOAT3(0.f, 0.f, 1.f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, ANGLE);

		// ��]���X�V���Ă�̂�Multiply
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
		m_Position.x -= SPEED;
	}
	if (CInput::GetKeyPress('U'))
	{
		XMFLOAT3 vx = XMFLOAT3(1.f, 0.f, 0.f);
		XMVECTOR axis = XMLoadFloat3(&vx);
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, -ANGLE);

		// ��]���X�V���Ă�̂�Multiply
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
		m_Position.z += SPEED;

	}
	if (CInput::GetKeyPress('J'))
	{
		XMFLOAT3 vx = XMFLOAT3(1.f, 0.f, 0.f);
		XMVECTOR axis = XMLoadFloat3(&vx);
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, -ANGLE);

		// ��]���X�V���Ă�̂�Multiply
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
		m_Position.z -= SPEED;
	}


}


void CBall::Draw()
{
	// �X�V���e�𔽉f
	m_World = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	m_World *= XMMatrixRotationQuaternion(m_Quaternion);
	m_World *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&m_World);

	m_pCamera = CManager::GetScene()->GetGameObject<CCamera>(LAYER_CAMERA);
	XMMATRIX world, view, proj, WVP;
	world = m_World;
	view = m_pCamera->GetViewMatrix();			// Tranpose���ĂȂ��I
	proj = m_pCamera->GetProjectionMatrix();	// Tranpose���ĂȂ��I
	WVP = m_World * view * proj;

	XMFLOAT4X4 mtxWVP;
	DirectX::XMStoreFloat4x4(&mtxWVP, WVP);
	m_pShader3D->SetWorldViewProjectionMatrix(&mtxWVP);

	//////////////////////////////////////////////////////
// ���[���h�ϊ��s��t�s��
	XMMATRIX mtxWIT;
	mtxWIT = XMMatrixInverse(nullptr, m_World);	// �t�s��
	mtxWIT = XMMatrixTranspose(mtxWIT);			// �]�u
	XMFLOAT4X4 witf;
	DirectX::XMStoreFloat4x4(&witf, mtxWIT);
	m_pShader3D->SetWorldInverseTranspose(&witf);
	// ���̂��ƃV�F�[�_�[���W�X�^�[�ɃZ�b�g�X���B
	///////////////////////////////////////////////////////

	XMFLOAT4X4 mtxWorld;
	DirectX::XMStoreFloat4x4(&mtxWorld, world);
	m_pShader3D->SetWorldTranspose(&mtxWorld);
	m_pShader3D->GetCameraPos(m_pCamera->GetPosition());

	m_pShader3D->Set();


	// �`��Ɣ�`�揈��
	////////////////////// new /////////////////////////////////
	CCamera* pCamera;
	pCamera = CManager::GetScene()->GetGameObject<CCamera>(LAYER_CAMERA);
	if (pCamera->GetVisibility(m_Position) == false)
	{
		return;
	}
	/////////////////////////////////////////////////////////////
	else {
		// ���f���`��
		m_pModel->Draw();
	}

}