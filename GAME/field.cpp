#include <list>

// system
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"

// gameobject
#include "gameobject.h"
#include "camera.h"
#include "field.h"

// shader
#include "shader3D_Field.h"

// resource
#include "model.h"		// �O��"renderer.h"���K�v
#include "modelanimation.h"
#include "player.h"
#include "enemy.h"
#include "ball.h"

// scene
#include "scene.h"

void CField::Init()
{
	m_pShader3D = new CShader3D_NormalMap();
	m_pShader3D->Init(VS_CSO_FILE_NAME, PS_CSO_FILE_NAME);


	for (int z = 0; z < FIELD_Z; z++)
	{
		for (int x = 0; x < FIELD_X; x++)
		{
			m_Vertex[z * FIELD_X + x].Position.x = (x - FIELD_X / 2) * FILED_SIZE;
			m_Vertex[z * FIELD_X + x].Position.z = (-z + FIELD_Z / 2) * FILED_SIZE;
			m_Vertex[z * FIELD_X + x].Position.y = 0.0f;
			//m_Vertex[z * FIELD_X + x].Position.y = sinf(x * 0.5f) * sinf(z * 0.3f) * 2.0f;
			m_Vertex[z * FIELD_X + x].Binormal = XMFLOAT3(0.0f, 0.0f, 1.0f);
			m_Vertex[z * FIELD_X + x].Tangent = XMFLOAT3(1.0f, 0.0f, 0.0f);
			m_Vertex[z * FIELD_X + x].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			m_Vertex[z * FIELD_X + x].TexCoord = XMFLOAT2(x, z);
		}
	}

	for (int z = 1; z < FIELD_Z - 1; z++)
	{
		for (int x = 1; x < FIELD_X - 1; x++)
		{
			XMFLOAT3 va, vb, n;
			float len;

			va.x = m_Vertex[(z - 1) * FIELD_X + x].Position.x - m_Vertex[(z + 1) * FIELD_X + x].Position.x;
			va.y = m_Vertex[(z - 1) * FIELD_X + x].Position.y - m_Vertex[(z + 1) * FIELD_X + x].Position.y;
			va.z = m_Vertex[(z - 1) * FIELD_X + x].Position.z - m_Vertex[(z + 1) * FIELD_X + x].Position.z;

			vb.x = m_Vertex[z * FIELD_X + (x + 1)].Position.x - m_Vertex[(z - 1) * FIELD_X + (x - 1)].Position.x;
			vb.y = m_Vertex[z * FIELD_X + (x + 1)].Position.y - m_Vertex[(z - 1) * FIELD_X + (x - 1)].Position.y;
			vb.z = m_Vertex[z * FIELD_X + (x + 1)].Position.z - m_Vertex[(z - 1) * FIELD_X + (x - 1)].Position.z;

			n.x = va.y * vb.z - va.z * vb.y;
			n.y = va.z * vb.x - va.x * vb.z;
			n.z = va.x * vb.y - va.y * vb.x;

			len = sqrtf(n.x * n.x + n.y * n.y + n.z * n.z);

			n.x /= len;
			n.y /= len;
			n.z /= len;

			m_Vertex[z * FIELD_X + x].Normal = n;
		}
	}

	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D_NORMALMAP) * FIELD_X * FIELD_Z;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_Vertex;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}


	unsigned short index[(FIELD_X * 2 + 2) * (FIELD_Z - 1) - 2];

	unsigned short i = 0;
	for (int z = 0; z < FIELD_Z - 1; z++)
	{
		for (int x = 0; x < FIELD_X; x++)
		{
			index[i] = (z + 1) * FIELD_X + x;
			i++;
			index[i] = z * FIELD_X + x;
			i++;
		}

		if (z == FIELD_Z - 2)
			break;

		index[i] = z * FIELD_X + FIELD_X - 1;
		i++;
		index[i] = (z + 2) * FIELD_X;
		i++;
	}


	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned short) * ((FIELD_X * 2 + 2) * (FIELD_Z - 1) - 2);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}

	for (int i = 0; i < TEXTURE_MAX; i++) {
		m_pTexture[i] = new CTexture();
	}
	m_pTexture[0]->Load("asset/TEXTURE/field004.tga");
	m_pTexture[1]->Load("asset/TEXTURE/wave.tga");
	//m_pTexture[2]->Load("data/TEXTURE/Rock_Displacement.tga");

	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
}


void CField::Uninit()
{

	m_VertexBuffer->Release();

	for (int i = 0; i < TEXTURE_MAX; i++) {
		m_pTexture[i]->Unload();
		delete m_pTexture[i];
	}

	m_pShader3D->Uninit();
	delete m_pShader3D;

}


void CField::Update()
{

}


void CField::Draw()
{
	if (CInput::GetKeyTrigger('B'))
	{
		Uninit();
		InitB();
	}
	else if (CInput::GetKeyTrigger('I'))
	{
		Uninit();
		Init();
	}

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D_NORMALMAP);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�ݒ�
	CRenderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);


	// �e�N�X�`���ݒ�
	CTexture* pTexture[] = { m_pTexture[0] , m_pTexture[1] };
	//CRenderer::SetTexture(2, pTexture);
	CRenderer::SetTexture(0, m_pTexture[0]);
	CRenderer::SetTexture(1, m_pTexture[1]);
	//CRenderer::SetTexture(2, m_pTexture[2]);

	// �}�g���N�X�ݒ�
	m_World = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	m_World *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_World *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&m_World);

	// 
	m_pCamera = CManager::GetScene()->GetGameObject<CCamera>(LAYER_CAMERA);
	XMMATRIX world, view, proj, WVP;
	world = m_World;			// Tranpose�ς�
	view = m_pCamera->GetViewMatrix();			// Tranpose���ĂȂ��I
	proj = m_pCamera->GetProjectionMatrix();	// Tranpose���ĂȂ��I
	WVP = world * view * proj;
	XMFLOAT4X4 mtxWVP;
	DirectX::XMStoreFloat4x4(&mtxWVP, WVP);
	m_pShader3D->SetWorldViewProjectionMatrix(&mtxWVP);

	//////////////////////////////////////////////////////
// ���[���h�ϊ��s��t�s��
	XMMATRIX mtxWIT;
	mtxWIT = XMMatrixInverse(nullptr, world);	// �t�s��
	mtxWIT = XMMatrixTranspose(mtxWIT);			// �]�u
	XMFLOAT4X4 witf;
	DirectX::XMStoreFloat4x4(&witf, mtxWIT);
	m_pShader3D->SetWorldInverseTranspose(&witf);
	// ���̂��ƃV�F�[�_�[���W�X�^�[�ɃZ�b�g�X���B
	///////////////////////////////////////////////////////

	XMFLOAT4X4 mtxWorld;
	DirectX::XMStoreFloat4x4(&mtxWorld, world);
	m_pShader3D->SetWorldTranspose(&mtxWorld);
	m_pShader3D->GetCameraPos(m_pCamera->GetPosition());

	m_pShader3D->Set();

	// �v���~�e�B�u�g�|���W�ݒ�
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	// �|���S���`��
	CRenderer::GetDeviceContext()->DrawIndexed(((FIELD_X * 2 + 2) * (FIELD_Z - 1) - 2), 0, 0);


}

void CField::InitB()
{
	m_pShader3D = new CShader3D_NormalMap();
	m_pShader3D->Init(VS_CSO_FILE_NAME, PS_CSO_FILE_NAME);


	for (int z = 0; z < FIELD_Z; z++)
	{
		for (int x = 0; x < FIELD_X; x++)
		{
			m_Vertex[z * FIELD_X + x].Position.x = (x - FIELD_X / 2) * FILED_SIZE;
			m_Vertex[z * FIELD_X + x].Position.z = (-z + FIELD_Z / 2) * FILED_SIZE;
			m_Vertex[z * FIELD_X + x].Position.y = 0.0f;
			//m_Vertex[z * FIELD_X + x].Position.y = sinf(x * 0.5f) * sinf(z * 0.3f) * 2.0f;
			m_Vertex[z * FIELD_X + x].Binormal = XMFLOAT3(1.0f, 0.0f, 0.0f);
			m_Vertex[z * FIELD_X + x].Tangent = XMFLOAT3(1.0f, 0.0f, 0.0f);
			m_Vertex[z * FIELD_X + x].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			m_Vertex[z * FIELD_X + x].TexCoord = XMFLOAT2(x, z);
		}
	}

	for (int z = 1; z < FIELD_Z - 1; z++)
	{
		for (int x = 1; x < FIELD_X - 1; x++)
		{
			XMFLOAT3 va, vb, n;
			float len;

			va.x = m_Vertex[(z - 1) * FIELD_X + x].Position.x - m_Vertex[(z + 1) * FIELD_X + x].Position.x;
			va.y = m_Vertex[(z - 1) * FIELD_X + x].Position.y - m_Vertex[(z + 1) * FIELD_X + x].Position.y;
			va.z = m_Vertex[(z - 1) * FIELD_X + x].Position.z - m_Vertex[(z + 1) * FIELD_X + x].Position.z;

			vb.x = m_Vertex[z * FIELD_X + (x + 1)].Position.x - m_Vertex[(z - 1) * FIELD_X + (x - 1)].Position.x;
			vb.y = m_Vertex[z * FIELD_X + (x + 1)].Position.y - m_Vertex[(z - 1) * FIELD_X + (x - 1)].Position.y;
			vb.z = m_Vertex[z * FIELD_X + (x + 1)].Position.z - m_Vertex[(z - 1) * FIELD_X + (x - 1)].Position.z;

			n.x = va.y * vb.z - va.z * vb.y;
			n.y = va.z * vb.x - va.x * vb.z;
			n.z = va.x * vb.y - va.y * vb.x;

			len = sqrtf(n.x * n.x + n.y * n.y + n.z * n.z);

			n.x /= len;
			n.y /= len;
			n.z /= len;

			m_Vertex[z * FIELD_X + x].Normal = n;
		}
	}

	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D_NORMALMAP) * FIELD_X * FIELD_Z;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_Vertex;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}


	unsigned short index[(FIELD_X * 2 + 2) * (FIELD_Z - 1) - 2];

	unsigned short i = 0;
	for (int z = 0; z < FIELD_Z - 1; z++)
	{
		for (int x = 0; x < FIELD_X; x++)
		{
			index[i] = (z + 1) * FIELD_X + x;
			i++;
			index[i] = z * FIELD_X + x;
			i++;
		}

		if (z == FIELD_Z - 2)
			break;

		index[i] = z * FIELD_X + FIELD_X - 1;
		i++;
		index[i] = (z + 2) * FIELD_X;
		i++;
	}


	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned short) * ((FIELD_X * 2 + 2) * (FIELD_Z - 1) - 2);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}

	for (int i = 0; i < TEXTURE_MAX; i++) {
		m_pTexture[i] = new CTexture();
	}
	m_pTexture[0]->Load("asset/TEXTURE/field004.tga");
	m_pTexture[1]->Load("asset/TEXTURE/wave.tga");
	//m_pTexture[2]->Load("data/TEXTURE/Rock_Displacement.tga");

	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);



}
