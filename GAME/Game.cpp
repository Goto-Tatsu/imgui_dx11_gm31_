#include <list>

#include "main.h"
#include "renderer.h"
#include "audio_clip.h"
#include "input.h"

#include "gameobject.h"
#include "polygon.h"
#include "camera.h"
#include "field.h"

#include "model.h"		// 前に"renderer.h"が必要
#include "player.h"
#include "enemy.h"
#include "bullet.h"

#include "scene.h"
#include "Game.h"
#include "Title.h"
#include "Result.h"
#include "manager.h"


void CGame::Init()
{
	// レイヤー管理
	// カメラ
	AddGameObject<CCamera>(LAYER_CAMERA);
	AddGameObject<CField>("asset/field004.tga", LAYER_3DMODELS);
	AddGameObject<CPlayer>(LAYER_3DMODELS);
	for (int i = 0; i < ENEMY_MAX; i++) {
		AddGameObject<CEnemy>(LAYER_3DMODELS);
	}
	AddGameObject<CPolygon>("asset/number.tga", LAYER_2DPOLYGONS);

	m_BGM = new CAudioClip();
	m_BGM->Load("asset/Audio/BGM/titan.wav");
	m_BGM->Play(true);
}

void CGame::Uninit()
{
	//m_BGM->Stop();
	m_BGM->Unload();
	delete m_BGM;

	CScene::Uninit();
}

void CGame::Update()
{
	CScene::Update();

	

	if (CInput::GetKeyTrigger(VK_RSHIFT))
	{
		CManager::SetScene<CResult>();
	}
}
