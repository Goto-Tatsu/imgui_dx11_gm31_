/*==============================================================================

	[polygon.cpp]
														 Author : Katsuma Murase
														 Date   : 2019/06/04
--------------------------------------------------------------------------------
==============================================================================*/

#include "main.h"
#include "gameobject.h"
#include "texture.h"
#include "polygon.h"

// ���_�v�f
struct Vertex {
	float pos[3];
	float col[4];
};

Vertex g_VertexList[]{
	{ { 0.0f,  0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },		// 0
	{ { 0.5f, -0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f } },		// 1
	{ { -0.5f, -0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f } },		// 2
	{ {  0.5f,  0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }  }		// 3
};




void CPolygon::Init()
{
	/* ���_�΂��ӂ��`���� */
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(0.0f, 0.0f, 10.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(0.0f, 0.0f, 10.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(0.0f, 0.0f, 10.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(0.0f, 0.0f, 10.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	// �΂��ӂ��ɂ����Ă�
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;		// ���_�o�b�t�@
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
	/* ���_�΂��ӂ��`��������� */

	// �e�N�X�`����݂���
	m_Texture = new CTexture();
	m_Texture->Load("asset/texture/primals.tga");

}

// Index������(2019/07/02)
void CPolygon::Init(const char * TexName)
{
	// �C���f�b�N�X��
	WORD IndexList[]{
		0, 1, 2,
		2, 3, 1,
	};

	/* ���_�΂��ӂ��`���� */
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(100.0f, 0.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(0.0f, 100.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(100.0f, 100.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	// ���_�o�b�t�@����
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ���_�o�b�t�@
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = vertex;
		if (FAILED(CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pVertexBuffer)))
			return;
	}

	// Index�o�b�t�@�̐���
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * 6;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = IndexList;

		if (FAILED(CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pIndexBuffer)))
			return;
	}
	
	/* �΂��ӂ��`��������� */

	// �e�N�X�`����݂���
	m_Texture = new CTexture();
	m_Texture->Load(TexName);

}

void CPolygon::Init(const float PosX, const float PosY, const short ScaleX, const short ScaleY, const char* TexName)
{
	/* ���_�΂��ӂ��`���� */
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(PosX, PosY, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(PosX + ScaleX, PosY, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(PosX, PosX+ScaleY, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(PosX+ScaleX, PosY+ScaleY, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	// �΂��ӂ��ɂ����Ă�
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ���_�o�b�t�@
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
	/* ���_�΂��ӂ��`��������� */

	// �e�N�X�`����݂���
	m_Texture = new CTexture();
	m_Texture->Load(TexName);
}

void CPolygon::Uninit()
{
	m_pVertexBuffer->Release();	// ���傤�Ă�΂��ӂ��΂��΂�
	m_Texture->Unload();		// ��񂾂Ă�������΂��΂�
	delete m_Texture;			// ������̂΂��΂�
}


void CPolygon::Update()
{

}

void CPolygon::Draw()
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);		// ���_�o�b�t�@�ݒ�
	CRenderer::GetDeviceContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	CRenderer::SetTexture(m_Texture);																// �e�N�X�`���ݒ�
	CRenderer::SetWorldViewProjection2D();															// 2D�pMatrix�ݒ�
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	// �g�|���W�[(�ǂ�����Ĕz�u���邩)�ݒ�
	CRenderer::GetDeviceContext()->DrawIndexed(6, 0, 0);
	//CRenderer::GetDeviceContext()->Draw(4, 0);														// ��غ�ݕ`��(���_��H, 0)
}