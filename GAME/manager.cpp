
#include <list>

// systems
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

// gameobjects
#include "gameobject.h"
#include "polygon.h"
#include "camera.h"
#include "field.h"

// resources
#include "model.h"		// 前に"renderer.h"が必要
#include "modelanimation.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "ball.h"

#include "scene.h"

#define POLYGON_TEXTURE_MAX	(1)
#define FIELD_TEXTURE_MAX	(1)
#define MODEL_MAX			(1)

CScene*			CManager::m_pScene = NULL;

void CManager::Init()
{
	// Rendererの初期化
	CRenderer::Init();

	// input初期化
	CInput::Init();

	// imguiの初期化
	ImguiManager::Init();

	// Sceneの初期化
	m_pScene = new CScene();
	m_pScene->Init();
	
}

void CManager::Uninit()		// Initの中身と逆に終了記述して！
{

	// Sceneのシュウリョウショリ
	m_pScene->Uninit();
	delete m_pScene;

	// ImGui Cleanup 
	ImguiManager::Uninit();

	// Inputの終了
	CInput::Uninit();

	// Rendererの終了処理
	CRenderer::Uninit();
}

void CManager::Update()
{
	// input更新
	CInput::Update();

	// SceneのUpdate
	m_pScene->Update();

	// imgui更新
	ImguiManager::Set();
}

void CManager::Draw()
{
	// Rendererはじめ
	CRenderer::Begin();

	// Sceneの描画
	m_pScene->Draw();

	// IMGUIの描画(Render)
	ImguiManager::Draw();
	
	// Rendererおわり
	CRenderer::End();
}

CScene* CManager::GetScene()
{
	return m_pScene;
}