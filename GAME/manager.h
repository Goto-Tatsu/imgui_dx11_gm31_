#pragma once

class CScene;	// �O���錾

class CManager
{

private:
	static CScene* m_pScene;

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static CScene* GetScene();
};