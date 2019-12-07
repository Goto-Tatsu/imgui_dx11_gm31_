#include <list>

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "gameobject.h"
#include "polygon.h"
#include "camera.h"
#include "field.h"

#include "model.h"		// 前に"renderer.h"が必要
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
	m_pModelAnimation = new CModelAnimation();
	m_pModelAnimation->Load();
	m_Position = XMFLOAT3(0.0f, 1.0f, -5.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	m_Quaternion = XMQuaternionIdentity();
	g_bAttack = false;
}

void CPlayer::Uninit()
{
	m_pModelAnimation->Unload();
	delete m_pModelAnimation;
}

void CPlayer::Update()
{
	// 弾
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

	// 移動
	if (CInput::GetKeyPress('A')) {		// 左
		m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Position.x -= 0.5f;
	}
	if (CInput::GetKeyPress('D')) {		// 右
		m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Position.x += 0.5f;
	}
	if (CInput::GetKeyPress('W')) {		// 前方
		m_Position.z += 0.5f;
	}
	if (CInput::GetKeyPress('S')) {		// 後方
		m_Position.z -= 0.5f;
	}

	// 旋回
	if (CInput::GetKeyPress(VK_RIGHT)) {
		m_Rotation.y += 0.01f;
		//m_fCameraAngle += 0.01f;
	}
	else if (CInput::GetKeyPress(VK_LEFT)) {
		m_Rotation.y -= 0.01f;
		//m_fCameraAngle -= 0.01f;
	}

	// 高さを受け付ける
	//CField* field = CManager::GetScene()->GetGameObject<CField>(LAYER_2DPOLYGONS);
	//m_Position.y = field->GetHeight(m_Position);
	/*if (m_Position.y >= field->GetHeight(m_Position))
	{
		m_Position.y--;
	}*/

	if (!g_bAttack) {
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
	}
}

void CPlayer::Draw()
{
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	//CRenderer::SetWorldMatrix(&world);
	
	if (!g_bAttack) {
		m_pModelAnimation->Draw(PLAYER_WALK, world);
	}
	else{
		m_pModelAnimation->Draw(PLAYER_ATTACK, world);
	}
}