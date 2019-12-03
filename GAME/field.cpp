/*==============================================================================


														 Author : Tatsuki Goto
														 Date   : 2019/06/04
--------------------------------------------------------------------------------
==============================================================================*/

#include "main.h"
#include "gameobject.h"
#include "texture.h"
#include "field.h"

float g_FieldHeight[11][11] =
{
	{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
};


void CField::Init()
{
	/* 頂点ばっふぁ～生成 */
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(300.0f, 300.0f, 10.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(300.0f, 300.0f, 10.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(300.0f, 300.0f, 2.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(300.0f, 300.0f, 2.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	// ばっふぁにもってく
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// 頂点バッファ
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
	/* 頂点ばっふぁ～生成おわり */

	// テクスチャよみこみ
	mTexture = new CTexture();
	mTexture->Load("asset/number.tga");

}

void CField::Init(const char* TexName)
{
	/*{
		mGridX = 11 / GRID_LENGTH;

		mGridZ = 11 / GRID_LENGTH;

		mGridLength = GRID_LENGTH;

		mVertexCount = (mGridX + 1) * (mGridZ + 1);

		//mIndexCount = ((mGridX + 1) * (mGridZ * 2)) + (mGridZ - 1) * 2;
		mIndexCount = (2 + (mGridX * 2)) * 2 + (mGridZ - 1) * 2;

		mPrimitiveCount = mGridX * mGridZ * 2 + 4 * (mGridZ - 1);

		float g_FieldHeight[11][11] =
		{
			{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
		};

		m_pVertex = new VERTEX_3D[mVertexCount];

		m_pIndex = new unsigned short[mIndexCount];

		//Position
		for (int z = 0; z < mGridZ + 1; z++)
		{
			for (int x = 0; x < mGridX + 1; x++)
			{
				m_pVertex[z * (mGridX + 1) + x].Position = XMFLOAT3(0.5f * -x + GRID_LENGTH * x, 0.0f, 0.5f * z - GRID_LENGTH * x);

				m_pVertex[z * (mGridX + 1) + x].Position.y = g_FieldHeight[z][x];
			}
		}

		for (int v = 0; v < mVertexCount; v++)
		{
			//Color
			m_pVertex[v].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

			//Normal
			m_pVertex[v].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		}

		//Normal
		for (int z = 1; z < mGridZ; z++)
		{
			for (int x = 1; x < mGridX; x++)
			{
				XMFLOAT3 fa;

				fa.x = m_pVertex[(z + 1) * (mGridZ + 1) + x].Position.x - m_pVertex[(z - 1) * (mGridZ + 1) + x].Position.x;
				fa.y = m_pVertex[(z + 1) * (mGridZ + 1) + x].Position.y - m_pVertex[(z - 1) * (mGridZ + 1) + x].Position.y;
				fa.z = m_pVertex[(z + 1) * (mGridZ + 1) + x].Position.z - m_pVertex[(z - 1) * (mGridZ + 1) + x].Position.z;

				XMFLOAT3 fb;

				fb.x = m_pVertex[z * (mGridX + 1) + (x - 1)].Position.x - m_pVertex[z * (mGridZ + 1) + (x + 1)].Position.x;
				fb.y = m_pVertex[z * (mGridX + 1) + (x - 1)].Position.y - m_pVertex[z * (mGridZ + 1) + (x + 1)].Position.y;
				fb.z = m_pVertex[z * (mGridX + 1) + (x - 1)].Position.z - m_pVertex[z * (mGridZ + 1) + (x + 1)].Position.z;

				XMVECTOR va = XMLoadFloat3(&fa);
				XMVECTOR vb = XMLoadFloat3(&fb);

				XMVECTOR vn = XMVector3Normalize(XMVector3Cross(va, vb));

				XMStoreFloat3(&m_pVertex[z * (mGridX + 1) + x].Normal, vn);

				//pV[40].Normal.x *= -1;
				//pV[40].Normal.y *= -1;
				//pV[40].Normal.z *= -1;
			}
		}

		//Texcoord
		for (int z = 0; z < mGridZ + 1; z++)
		{
			for (int x = 0; x < mGridX + 1; x++)
			{
				m_pVertex[z * (mGridX + 1) + x].TexCoord = XMFLOAT2(1.0f / mGridX * x, 1.0f / mGridZ * z);
			}
		}

		//Index
		for (int z = 0; z < mGridZ; z++)
		{
			for (int x = 0; x < mGridX + 1; x++)
			{
				m_pIndex[((mGridX + 2) * 2 * z + 2 * x) + 1] = (mGridX + 1) * z + x;

				m_pIndex[(mGridX + 2) * 2 * z + 2 * x] = (mGridX + 1) * (z + 1) + x;
			}
		}

		for (int z = 0; z < mGridZ - 1; z++)
		{
			m_pIndex[(mGridX + 2) * 2 * (z + 1) - 2] = mGridX * (1 + z) + z;
			m_pIndex[(mGridX + 2) * 2 * (z + 1) - 1] = (mGridX * (1 + z) + z) + (mGridX + 2);
		}

		//VertexBuffer
		{
			D3D11_BUFFER_DESC bd;

			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(VERTEX_3D) * mVertexCount;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = m_pVertex;
			CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
		}

		//IndexBuffer
		{
			D3D11_BUFFER_DESC bd;

			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(unsigned short) * mIndexCount;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = m_pIndex;

			CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pIndexBuffer);
		}

		//Texture
		mTexture = new CTexture();
		mTexture->Load(TexName);
	}*/

	mVertexCount = FIELD_X * FIELD_Z;
	m_pVertex = new VERTEX_3D[mVertexCount];

	for (int z = 0; z < FIELD_Z; z++)
	{
		for (int x = 0; x < FIELD_X; x++)
		{
			/*
			m_pVertex[z * FIELD_X + x].Position.x = x - FIELD_X / 2;
			m_pVertex[z * FIELD_X + x].Position.z = -z + FIELD_Z / 2;
			m_pVertex[z * FIELD_X + x].Position.y = sinf(x * 0.5f) * sinf(z * 0.3f) * 2.0f;
			m_pVertex[z * FIELD_X + x].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			m_pVertex[z * FIELD_X + x].TexCoord = XMFLOAT2(x, z);
			m_pVertex[z * FIELD_X + x].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			*/
		}
	}
	
	for (int z = 1; z < FIELD_Z - 1; z++)
	{
		for (int x = 1; x < FIELD_X - 1; x++)
		{
			XMFLOAT3 va, vb, n;
			float len;
	
			va.x = m_pVertex[(z - 1) * FIELD_X + x].Position.x - m_pVertex[(z + 1) * FIELD_X + x].Position.x;
			va.y = m_pVertex[(z - 1) * FIELD_X + x].Position.y - m_pVertex[(z + 1) * FIELD_X + x].Position.y;
			va.z = m_pVertex[(z - 1) * FIELD_X + x].Position.z - m_pVertex[(z + 1) * FIELD_X + x].Position.z;
	
			vb.x = m_pVertex[z * FIELD_X + (x + 1)].Position.x - m_pVertex[(z - 1) * FIELD_X + (x - 1)].Position.x;
			vb.y = m_pVertex[z * FIELD_X + (x + 1)].Position.y - m_pVertex[(z - 1) * FIELD_X + (x - 1)].Position.y;
			vb.z = m_pVertex[z * FIELD_X + (x + 1)].Position.z - m_pVertex[(z - 1) * FIELD_X + (x - 1)].Position.z;
	
			n.x = va.y * vb.z - va.z * vb.y;
			n.y = va.z * vb.x - va.x * vb.z;
			n.z = va.x * vb.y - va.y * vb.x;
	
			len = sqrtf(n.x * n.x + n.y * n.y + n.z * n.z);
	
			n.x /= len;
			n.y /= len;
			n.z /= len;
	
			m_pVertex[z * FIELD_X + x].Normal = n;
		}
	}
	
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * FIELD_X * FIELD_Z;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
	
		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_pVertex;
	
		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
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
	
		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pIndexBuffer);
	}
	
	mTexture = new CTexture();
	mTexture->Load(TexName);
	
	
	
	/*m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);*/

}

void CField::Uninit()
{
	if (m_pVertexBuffer) {
		m_pVertexBuffer->Release();	// ちょうてんばっふぁばいばい
	}

	if (m_pIndexBuffer) {
		m_pIndexBuffer->Release();
	}

	mTexture->Unload();		// よんだてくすちゃばいばい
	delete mTexture;			// いれものばいばい
}


void CField::Draw()
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);		// 頂点バッファ設定
	CRenderer::GetDeviceContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, offset);
	CRenderer::SetTexture(mTexture);

	// SetWorldViewProjection2Dの代わり
	XMMATRIX world;
	world = XMMatrixScaling(1.0f, 1.0f, 1.0f);					// 拡大縮小
	world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);	// 回転(ラジアン角度)
	world *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);				// 移動
	
	CRenderer::SetWorldMatrix(&world);	

	// 頂点ばっふぁせってい
	CRenderer::SetVertexBuffers(m_pVertexBuffer);

	// Indexばっふぁせってい
	CRenderer::SetIndexBuffer(m_pIndexBuffer);

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	// トポロジー(どうやって配置するか)設定
	CRenderer::GetDeviceContext()->DrawIndexed(mIndexCount, 0, 0);
}

float CField::GetHeight(XMFLOAT3 Position)
{
	// ローカル変数宣言
	int x, z;
	XMFLOAT3 p0, p1, p2, v01, v02, n, v, hp, va, vb;
	float  dvn, dp0n, dpn, t;

	// 要素
	v = XMFLOAT3(0.0f, -1.0f, 0.0f);
	x = Position.x;
	z = -Position.z;

	// va,vb
	va.x = m_pVertex[(z + 1) * 5 + (x + 1)].Position.x - m_pVertex[z * 5 + x].Position.x;
	va.y = m_pVertex[(z + 1) * 5 + (x + 1)].Position.y - m_pVertex[z * 5 + x].Position.y;
	va.z = m_pVertex[(z + 1) * 5 + (x + 1)].Position.z - m_pVertex[z * 5 + x].Position.z;
	vb.x = Position.x - m_pVertex[z * 5 + x].Position.x;
	vb.y = Position.y - m_pVertex[z * 5 + x].Position.y;
	vb.z = Position.z - m_pVertex[z * 5 + x].Position.z;

	// yベクトルがどっちに向いてるか？
	float vab = va.z * vb.x - va.x * vb.z;	// va×vb(外積)のy成分算出
	if (vab > 0.0f)
	{
		p0 = m_pVertex[(z + 1) * 5 + x].Position;
		p1 = m_pVertex[z * 5 + x].Position;
		p2 = m_pVertex[(z + 1) * 5 + (x + 1)].Position;
	}
	else
	{
		p0 = m_pVertex[z * 5 + (x + 1)].Position;
		p1 = m_pVertex[(z + 1) * 5 + (x + 1)].Position;
		p2 = m_pVertex[z * 5 + x].Position;
	}

	// v01,v02の設定
	v01.x = p1.x - p0.x;
	v01.y = p1.y - p0.y;
	v01.z = p1.z - p0.z;
	v02.x = p2.x - p0.x;
	v02.y = p2.y - p0.y;
	v02.z = p2.z - p0.z;

	// n
	n.x = v01.y * v02.z - v01.z * v02.y;
	n.y = v01.z * v02.x - v01.x * v02.z;
	n.z = v01.y * v02.x - v01.x * v02.y;

	// dvn
	dvn = (v.x * n.x) + (v.y * n.y) + (v.z * n.z);

	// dp0n
	dp0n = (p0.x * n.x) + (p0.y * n.y) + (p0.z * n.z);

	// dpn
	dpn = (Position.x * n.x) + (Position.y * n.y) + (Position.z * n.z);

	// t
	t = (dp0n - dpn) / dvn;

	// hp
	hp.x = Position.x + (v.x * t);
	hp.y = Position.y + (v.y * t);
	hp.z = Position.y + (v.y * t);

	// return
	return hp.y;
}
