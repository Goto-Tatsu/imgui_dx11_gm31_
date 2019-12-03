#ifndef FIELD_H_
#define FIELD_H_

class CField:public CGameObject	// CGameObjectÇ©ÇÁåpè≥
{
private:

	ID3D11Buffer* m_pVertexBuffer = NULL;
	ID3D11Buffer* m_pIndexBuffer = NULL;
	CTexture* mTexture = NULL;
	
	static const int FIELD_X = 11;
	static const int FIELD_Z = 11;
	static const int GRID_LENGTH = 1;

	VERTEX_3D* m_pVertex;

	unsigned short* m_pIndex;


	int mGridX;
	int mGridZ;
	int mGridLength;

	int mVertexCount;
	int mIndexCount;
	int mPrimitiveCount;


public:
	void Init(void);

	void Init(const char* TexName);
	void Uninit(void);
	void Update(void) {};
	void Draw(void);
	float GetHeight(XMFLOAT3 Position);
};

#endif // !FIELD_H_