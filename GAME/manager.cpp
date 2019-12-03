
#include <list>

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "gameobject.h"
#include "polygon.h"
#include "camera.h"
#include "field.h"

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

// Our state
bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

CScene* CManager::m_pScene = NULL;
//CScene* g_Scene = NULL;
CPlayer* player;
CModelAnimation* animModel;



void CManager::Init()
{
	// Renderer�̏�����
	CRenderer::Init();

	// Input�̏�����
	CInput::Init();

	// Scene�̏�����
	m_pScene = new CScene();
	m_pScene->Init();
	
}

void CManager::Uninit()		// Init�̒��g�Ƌt�ɏI���L�q���āI
{
	// Cleanup 
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();


	// Scene�̃V���E�����E�V����
	m_pScene->Uninit();
	delete m_pScene;

	// Renderer�̏I������
	CRenderer::Uninit();
}

void CManager::Update()
{
	// Input����
	CInput::Update();

	// Scene��Update
	m_pScene->Update();

}

void CManager::Draw()
{
	// Renderer�͂���
	CRenderer::Begin();


	// Scene�̕`��
	m_pScene->Draw();

	// IMGUI�̕`��(Render)
	ImGui::Render();										// �ݒ肵��IMGUI�̏��X��`�悵�Ă���閽�߁B
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());	// �����悭�킩��Ȃ�
	
	// Renderer�����
	CRenderer::End();
}

CScene* CManager::GetScene()
{
	return m_pScene;
}

void CManager::Gui_Show()
{
	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)& clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Player position show");

		ImGui::Text("position X : %.1f", player->GetPositionX());

		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}
	/* ================================================================================================ */

}
