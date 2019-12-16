#pragma once

class Shader3D_Model;

class CBall :	public CGameObject
{
private:
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;

	CModel* m_pModel;
	XMVECTOR m_Quaternion;

	Shader3D_Model* m_pShader3D;
	CCamera* m_pCamera;
	
	XMMATRIX m_World;

public:
	CBall() {};
	~CBall() {};

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

};