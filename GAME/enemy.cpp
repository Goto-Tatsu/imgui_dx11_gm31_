#include <list>
#include <time.h>

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "gameobject.h"
#include "polygon.h"
#include "camera.h"
#include "field.h"

#include "model.h"		// ‘O‚É"renderer.h"‚ª•K—v
#include "modelanimation.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "ball.h"

#include "scene.h"

static CModelAnimation* g_pModelAnimation;
static int g_Random = 0;
static unsigned int g_Frame;

void CEnemy::Init()
{
	m_pModelAnimation = new CModelAnimation();
	m_pModelAnimation->Load();
	m_Position = XMFLOAT3(0.0f, 0.f, 0.0f);
	m_Rotation = XMFLOAT3(0.f, 30.f, 0.0f);
	m_Scale = XMFLOAT3(1.f, 1.f, 1.f);

	g_Frame = 0;
}

void CEnemy::Uninit()
{
	m_pModelAnimation->Unload();
	delete m_pModelAnimation;
}

void CEnemy::Update()
{
	if (CInput::GetKeyPress('K'))
	{
		this->m_Position.y += 0.1f;
	}
	if (CInput::GetKeyPress('J'))
	{
		this->m_Position.y -= 0.1f;
	}

	

	if (g_Frame < 300) {
		m_pModelAnimation->Update(PLAYER_ATTACK, g_Frame);
		g_Frame++;
	}
	else if (g_Frame >= 300) {
		g_Frame = 0;
	}
}

void CEnemy::Draw()
{
	// Š|‚¯‡‚¹•û‚ÍyŠg‘å–‰ñ“]–ˆÚ“®z
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);


	m_pModelAnimation->Draw(PLAYER_ATTACK,world);
}

XMFLOAT3 CEnemy::GetPosition() {
	return CEnemy::m_Position;
}
