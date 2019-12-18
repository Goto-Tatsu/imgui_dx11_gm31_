#ifndef PLAYER_H_
#define PLAYER_H_

class Shader3D_Player;

class CPlayer:public CGameObject
{

private:
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;

	CModel* m_pModel;
	CModelAnimation* m_pModelAnimation;
	XMVECTOR m_Quaternion;

	Shader3D_Player* m_pShader3D;
	CCamera* m_pCamera;

	XMMATRIX m_World;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	XMFLOAT3 GetPosition(void) { return m_Position; };
	float GetPositionX(void) { return m_Position.x; };
	float GetPositionY(void) { return m_Position.y; };
	float GetPositionZ(void) { return m_Position.z; };
};

#endif // !PLAYER_H_
