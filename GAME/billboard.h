#pragma once

class CCamera;

class CBillboard
{
public:
	CBillboard();
	~CBillboard();

	void SetBillBoardPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3 &position);

private:
	XMVECTOR m_Positoin;
	XMVECTOR m_Target;
	XMVECTOR m_Up;
	XMMATRIX m_Rotate;
	
	CCamera* m_Camera;

};

CBillboard::CBillboard()
{
	m_Camera = CManager::GetScene()->GetGameObject<CCamera>(LAYER_CAMERA);
	m_Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
}

CBillboard::~CBillboard()
{
}


