#ifndef BULLET_H_
#define BULLET_H

class CBullet:public CGameObject
{
private:
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;

	CModel* m_pModel;

public:

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetPosition(XMFLOAT3 position);	// 発射位置を指定する

	XMFLOAT3 GetPosition(void);	 //
};


#endif // !BULLET_H_
