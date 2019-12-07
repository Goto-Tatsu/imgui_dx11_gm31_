#include <list>

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "gameobject.h"
#include "input.h"
#include "polygon.h"
#include "camera.h"
#include "field.h"

#include "model.h"		// 前に"renderer.h"が必要
#include "modelanimation.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "ball.h"

#include "scene.h"

#define SPEED	(0.05f)
#define ANGLE	(0.2f)

void CBall::Init()
{
	m_pModel = new CModel();
	m_pModel->Load("asset/model/miku_01.obj");
	m_Position = XMFLOAT3(0.0f, 1.0f, -5.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);


	m_Quaternion = XMQuaternionIdentity();
}


void CBall::Uninit(void)
{
	m_pModel->Unload();
	delete m_pModel;
}


void CBall::Update()
{
	if (CInput::GetKeyPress('K'))
	{
		XMFLOAT3 vz = XMFLOAT3(0.f, 0.f, 1.f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, -ANGLE);

		// 回転を更新してるのがMultiply
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
		m_Position.x += SPEED;
	}
	if (CInput::GetKeyPress('H'))
	{
		XMFLOAT3 vz = XMFLOAT3(0.f, 0.f, 1.f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, ANGLE);

		// 回転を更新してるのがMultiply
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
		m_Position.x -= SPEED;
	}
	if (CInput::GetKeyPress('U'))
	{
		XMFLOAT3 vx = XMFLOAT3(1.f, 0.f, 0.f);
		XMVECTOR axis = XMLoadFloat3(&vx);
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, -ANGLE);

		// 回転を更新してるのがMultiply
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
		m_Position.z += SPEED;

	}
	if (CInput::GetKeyPress('J'))
	{
		XMFLOAT3 vx = XMFLOAT3(1.f, 0.f, 0.f);
		XMVECTOR axis = XMLoadFloat3(&vx);
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, -ANGLE);

		// 回転を更新してるのがMultiply
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
		m_Position.z -= SPEED;
	}

}


void CBall::Draw()
{
	// 更新内容を反映
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationQuaternion(m_Quaternion);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&world);

	////////////////////// new /////////////////////////////////
	CCamera* pCamera;
	pCamera = CManager::GetScene()->GetGameObject<CCamera>(LAYER_CAMERA);
	if (pCamera->GetVisibility(m_Position) == false)
	{
		return;
	}
	/////////////////////////////////////////////////////////////
	else {
		// モデル描画
		m_pModel->Draw();
	}

}