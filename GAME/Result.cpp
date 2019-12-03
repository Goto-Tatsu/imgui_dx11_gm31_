#include <list>

#include "main.h"
#include "renderer.h"
#include "audio_clip.h"
#include "input.h"

#include "gameobject.h"
#include "polygon.h"
#include "camera.h"
#include "field.h"

#include "model.h"		// ‘O‚É"renderer.h"‚ª•K—v
#include "player.h"
#include "enemy.h"
#include "bullet.h"

#include "scene.h"
#include "Game.h"
#include "Title.h"
#include "Result.h"
#include "manager.h"


void CResult::Init()
{
	AddGameObject<CPolygon>("asset/result.tga", LAYER_2DPOLYGONS);
}

void CResult::Uninit()
{
	CScene::Uninit();
}

void CResult::Update()
{
	CScene::Update();
	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		CManager::SetScene<CTitle>();
	}
}
