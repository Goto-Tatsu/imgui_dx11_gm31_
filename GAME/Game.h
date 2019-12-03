#pragma once


class CGame : public CScene
{
public:
	void Init();
	void Uninit();
	void Update();

private:
	CAudioClip* m_BGM;


};