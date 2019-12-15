#pragma once

class CScene;	// �O���錾
class CPlayer;

class CManager
{

private:
	static CScene* m_pScene;
	static CPlayer* m_pPlayer;

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static CScene* GetScene();
	static void Gui_Show();
};