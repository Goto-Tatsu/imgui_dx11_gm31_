#ifndef ENEMY_H_
#define ENEMY_H_

class CEnemy : public CGameObject
{
private:
	CModel* m_pModel;
	CModelAnimation* m_pModelAnimation;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	XMFLOAT3 GetPosition();
};

#endif // !ENEMY_H_
