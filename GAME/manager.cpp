
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
#include "model.h"		// �O��"renderer.h"���K�v
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
	// Renderer�̏�����
	CRenderer::Init();

	// input������
	CInput::Init();

	// imgui�̏�����
	ImguiManager::Init();

	// Scene�̏�����
	m_pScene = new CScene();
	m_pScene->Init();
	
}

void CManager::Uninit()		// Init�̒��g�Ƌt�ɏI���L�q���āI
{

	// Scene�̃V���E�����E�V����
	m_pScene->Uninit();
	delete m_pScene;

	// ImGui Cleanup 
	ImguiManager::Uninit();

	// Input�̏I��
	CInput::Uninit();

	// Renderer�̏I������
	CRenderer::Uninit();
}

void CManager::Update()
{
	// input�X�V
	CInput::Update();

	// Scene��Update
	m_pScene->Update();

	// imgui�X�V
	ImguiManager::Set();
}

void CManager::Draw()
{
	// Renderer�͂���
	CRenderer::Begin();

	// Scene�̕`��
	m_pScene->Draw();

	// IMGUI�̕`��(Render)
	ImguiManager::Draw();
	
	// Renderer�����
	CRenderer::End();
}

CScene* CManager::GetScene()
{
	return m_pScene;
}