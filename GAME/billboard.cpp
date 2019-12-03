#include "main.h"
#include "manager.h"
#include "gameobject.h"

#include "camera.h"
#include "billboard.h"

#include "scene.h"

inline void CBillboard::SetBillBoardPosition(float x, float y, float z)
{
	XMFLOAT4X4 bill;
	XMMATRIX camView = m_Camera->GetViewMatrix();	
	XMMATRIX camProj = m_Camera->GetProjectionMatrix();
	XMStoreFloat4x4(&bill, camView);
	bill._41 = bill._42 = bill._43 = 0.0f;

	XMVECTOR pos = XMVectorSet(x, y + 1.0f, z, 0.0f);
	XMVector3TransformCoord(pos, camView);	// ƒrƒ…[•ÏŠ·
	XMVector3TransformCoord(pos, camProj);	// “§‹“Š‰e•ÏŠ·

	XMMATRIX ortho;

	
}