#pragma once


class CBall :public CGameObject
{
private:
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;

	CModel* m_pModel;
	XMVECTOR m_Quaternion;

public:
	CBall() {};
	~CBall() {};

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

};