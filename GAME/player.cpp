#include <list>

// system
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

// shader
#include "shader3D_player.h"

// gameobjects
#include "gameobject.h"
#include "polygon.h"
#include "camera.h"
#include "field.h"

// resource
#include "model.h"		// �O��"renderer.h"���K�v
#include "modelanimation.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "ball.h"

#include "scene.h"

#define SPEED	(0.05f);
#define ANGLE	(0.2f);

static unsigned int g_Frame;
static bool g_bAttack;

void CPlayer::Init()
{
	// shader
	m_pShader3D = new Shader3D_Player();
	m_pShader3D->Init("vertexShader3D_player.cso", "pixelShader3D_player.cso");

	//m_pModelAnimation = new CModelAnimation();
	//m_pModelAnimation->Load();

	m_pModel = new CModel();
	m_pModel->Load("asset/model/miku_01.obj");

	m_Position = XMFLOAT3(0.0f, 1.0f, -5.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	g_bAttack = false;
}

void CPlayer::Uninit()
{
	//m_pModelAnimation->Unload();
	//delete m_pModelAnimation;

	m_pModel->Unload();
	delete m_pModel;

	m_pShader3D->Uninit();
	delete m_pShader3D;
}

void CPlayer::Update()
{
	// �e
	if (CInput::GetKeyTrigger(VK_SPACE)) {
		CScene* scene = CManager::GetScene();
		CBullet* bullet = scene->AddGameObject<CBullet>(LAYER_3DMODELS);
		bullet->SetPosition(m_Position);
	}

	//
	if (CInput::GetKeyPress(VK_SPACE)) {
		g_bAttack = true;
	}
	else {
		g_bAttack = false;
	}

	// �ړ�
	if (CInput::GetKeyPress('A')) {		// ��
		m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Position.x -= 0.5f;
	}
	if (CInput::GetKeyPress('D')) {		// �E
		m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Position.x += 0.5f;
	}
	if (CInput::GetKeyPress('W')) {		// �O��
		m_Position.z += 0.5f;
	}
	if (CInput::GetKeyPress('S')) {		// ���
		m_Position.z -= 0.5f;
	}

	// ����
	if (CInput::GetKeyPress(VK_RIGHT)) {
		m_Rotation.y += 0.01f;
		//m_fCameraAngle += 0.01f;
	}
	else if (CInput::GetKeyPress(VK_LEFT)) {
		m_Rotation.y -= 0.01f;
		//m_fCameraAngle -= 0.01f;
	}

	// �������󂯕t����
	//CField* field = CManager::GetScene()->GetGameObject<CField>(LAYER_BG);
	//m_Position.y = field->GetHeight(m_Position);
	/*if (m_Position.y >= field->GetHeight(m_Position))
	{
		m_Position.y--;
	}*/

	/*if (!g_bAttack) {
		if (g_Frame < 60) {
			m_pModelAnimation->Update(PLAYER_WALK, g_Frame);
			g_Frame++;
		}
		else if (g_Frame >= 60) {
			g_Frame = 0;
		}
	}
	else {
		if (g_Frame < 300) {
			m_pModelAnimation->Update(PLAYER_ATTACK, g_Frame);
			g_Frame++;
		}
		else if (g_Frame >= 300) {
			g_Frame = 0;
		}
	}*/
}

void CPlayer::Draw()
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
	
	m_pModel->Draw();
	//if (!g_bAttack) {
	//	m_pModelAnimation->Draw(PLAYER_WALK, world);
	//}
	//else{
	//	m_pModelAnimation->Draw(PLAYER_ATTACK, world);
	//}
}