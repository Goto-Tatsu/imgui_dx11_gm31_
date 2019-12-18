#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX

#include <list>
#include <io.h>
// system
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

// gameobject
#include "gameobject.h"
#include "camera.h"
#include "field.h"

// shader
#include "shader3D_player.h"

// resource
#include "model.h"		// 前に"renderer.h"が必要
#include "modelanimation.h"
#include "player.h"
#include "enemy.h"
#include "ball.h"

// scene
#include "scene.h"


void Shader3D_Player::Init(const char* vertex_shader, const char* pixel_shader)
{
	// 頂点シェーダ生成
	{
		FILE* file;
		long int fsize;

		file = fopen(vertex_shader, "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		CRenderer::GetDevice()->CreateVertexShader(buffer, fsize, NULL, &m_VertexShader);


		// 入力レイアウト生成
		// GPU(VRAM)に流し込む
		// 頂点データ1個分の構成
		{
			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,		0,	0,			D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL",		0,	DXGI_FORMAT_R32G32B32_FLOAT,		0,	4 * 3,		D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR",		0,	DXGI_FORMAT_R32G32B32A32_FLOAT,		0,	4 * 6,		D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT,			0,	4 * 10,		D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};

			UINT numElements = ARRAYSIZE(layout);

			CRenderer::GetDevice()->CreateInputLayout(layout,
				numElements,
				buffer,
				fsize,
				&m_VertexLayout);
		}

		delete[] buffer;
	}



	// ピクセルシェーダ生成
	{
		FILE* file;
		long int fsize;

		file = fopen(pixel_shader, "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		CRenderer::GetDevice()->CreatePixelShader(buffer, fsize, NULL, &m_PixelShader);

		delete[] buffer;
	}



	// 定数バッファ生成
	{
		D3D11_BUFFER_DESC hBufferDesc;
		hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		hBufferDesc.CPUAccessFlags = 0;
		hBufferDesc.MiscFlags = 0;
		hBufferDesc.StructureByteStride = sizeof(float);

		hBufferDesc.ByteWidth = sizeof(CONSTANT3D_PLAYER);
		CRenderer::GetDevice()->CreateBuffer(&hBufferDesc, NULL, &m_ConstantBuffer);
	}
}

void Shader3D_Player::Uninit(void)
{
	if (m_ConstantBuffer)	m_ConstantBuffer->Release();
	if (m_VertexLayout)		m_VertexLayout->Release();
	if (m_VertexShader)		m_VertexShader->Release();
	if (m_PixelShader)		m_PixelShader->Release();

}

void Shader3D_Player::Set(void)
{
	// シェーダ設定
	CRenderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	CRenderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	// 入力レイアウト設定
	CRenderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);


	// 定数バッファ更新
	CRenderer::GetDeviceContext()->UpdateSubresource(m_ConstantBuffer, 0, NULL, &m_Constant3D, 0, 0);


	// 定数バッファ設定
	CRenderer::GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_ConstantBuffer);

	CRenderer::GetDeviceContext()->PSSetConstantBuffers(0, 1, &m_ConstantBuffer);
}
