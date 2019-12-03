/*==============================================================================


														 Author : Tatsuki Goto
														 Date   : 2019/09/03
--------------------------------------------------------------------------------
==============================================================================*/

#include "main.h"
#include "renderer.h"
#include "input.h"
#include "gameobject.h"
#include "texture.h"
#include "modelanimation.h"


void CModelAnimation::Update(int Animation, int Frame)
{
	aiAnimation* animation = m_Scene[Animation]->mAnimations[0];	// ���Ԗڂ̃A�j���[�V�����ĂԁH

	// ��]�̓��e
	for (auto c = 0; c < animation->mNumChannels; c++)
	{
		aiNodeAnim* nodeAnim = animation->mChannels[c];
		int f = Frame % nodeAnim->mNumRotationKeys;
		m_NodeRotation[nodeAnim->mNodeName.C_Str()] = nodeAnim->mRotationKeys[Frame].mValue;
	}

	// �ړ��̓��e
	for (auto c = 0; c < animation->mNumChannels; c++)
	{
		aiNodeAnim* nodeAnim = animation->mChannels[c];
		int f = Frame % nodeAnim->mNumPositionKeys;
		m_NodePostion[nodeAnim->mNodeName.C_Str()] = nodeAnim->mPositionKeys[Frame].mValue;
	}

	// �g�k�̓��e
}

void CModelAnimation::Draw(int Animation, XMMATRIX Matrix)	// ������Matrix��Player�Ȃǂ̍s����󂯎��
{
	// �K�w�\���ɂ��ċA�֐��Ăяo��
	DrawMesh(m_Scene[Animation]->mRootNode, Matrix);
}

void CModelAnimation::DrawMesh(aiNode* Node, XMMATRIX Matrix)
{
	/* ���s��v�Z�̏��Ԃ́yRotation��Translate��Scale�z *

	/* Rotation */
	/* RotAnimation */
	aiQuaternion aiQuat = m_NodeRotation[Node->mName.C_Str()];
	XMVECTOR quat = XMLoadFloat4(&XMFLOAT4(aiQuat.x, aiQuat.y, aiQuat.z, aiQuat.w));
	XMMATRIX world = XMMatrixRotationQuaternion(quat);
	
	/* Translate */
	aiVector3D aiVec = m_NodePostion[Node->mName.C_Str()];
	XMVECTOR vec = XMLoadFloat3(&XMFLOAT3(aiVec.x, aiVec.y, aiVec.z));
	world *= XMMatrixTranslationFromVector(vec);

	world *= Matrix;					// �e�̍s��(Matrix)�A�e���猩���V�����s��ɕϊ������B
	CRenderer::SetWorldMatrix(&world);	// �e���猩���ʒu�ɃZ�b�g

	for (int n = 0; n < Node->mNumMeshes; n++)
	{
		unsigned int m = Node->mMeshes[n];	// m�̓��b�V���ԍ�

		/* ���b�V���`��(�O���Draw(void)�֐��̒��g) */
		CRenderer::SetVertexBuffers(m_Mesh[m].VertexBuffer);
		CRenderer::SetIndexBuffer(m_Mesh[m].IndexBuffer);
		CRenderer::DrawIndexed(m_Mesh[m].IndexNum, 0, 0);
		/* ======================================== */
	}

	for (int i=0; i < Node->mNumChildren; i++)
	{
		DrawMesh(Node->mChildren[i], world);
	}

}

void CModelAnimation::Load()
{
	unsigned int texture;

	// Assimp�̍\���̂�p����
	m_Scene[PLAYER_WALK] = aiImportFile("asset/model/Player/machine_Walk.fbx", aiProcess_Triangulate);
	m_Scene[PLAYER_ATTACK] = aiImportFile("asset/model/Player/machine_Attack.fbx", aiProcess_Triangulate);

	m_MeshNum = m_Scene[PLAYER_WALK]->mNumMeshes;
	m_Mesh = new MESH[m_MeshNum];

	for (auto i = 0; i < PLAYER_MAX; i++) {
		for (int m = 0; m < m_MeshNum; m++) {
			aiMesh* mesh = m_Scene[i]->mMeshes[m];

			// ���_�o�b�t�@�̐ݒ�
			VERTEX_3D* vertex = new VERTEX_3D[mesh->mNumVertices];	// ���_��ۑ�

			for (int i = 0; i < mesh->mNumVertices; i++) {
				vertex[i].Position = XMFLOAT3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
				vertex[i].Diffuse = XMFLOAT4(1, 1, 1, 1);
				vertex[i].Normal = XMFLOAT3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			}

			// ���_�o�b�t�@�̐���
			{
				D3D11_BUFFER_DESC bd;
				ZeroMemory(&bd, sizeof(bd));
				bd.Usage = D3D11_USAGE_DEFAULT;
				bd.ByteWidth = sizeof(VERTEX_3D) * mesh->mNumVertices;
				bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				//bd.CPUAccessFlags = 0;

				D3D11_SUBRESOURCE_DATA sd;
				ZeroMemory(&sd, sizeof(sd));
				sd.pSysMem = vertex;

				// �o�b�t�@����邽�߂̔ėp�I�Ȋ֐�
				CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_Mesh[m].VertexBuffer);
			}
			delete[] vertex;


			// Index�΂��ӂ������Ă�
			unsigned short* index;
			index = new unsigned short[mesh->mNumFaces * 3];
			m_Mesh[m].IndexNum = mesh->mNumFaces * 3;				// �ő咸�_�����Z�o
			for (int i = 0; i < mesh->mNumFaces; i++) {				// �ʂ̐�����for���[�v
				index[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
				index[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
				index[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
			}
			// Index�΂��ӂ�����
			{	// �����ȃX�R�[�v�Ō��肷��
				D3D11_BUFFER_DESC bd;
				ZeroMemory(&bd, sizeof(bd));
				bd.Usage = D3D11_USAGE_DEFAULT;
				bd.ByteWidth = sizeof(unsigned short) * mesh->mNumFaces * 3;
				bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
				//bd.CPUAccessFlags = 0;

				D3D11_SUBRESOURCE_DATA sd;
				ZeroMemory(&sd, sizeof(sd));
				sd.pSysMem = index;

				// �o�b�t�@����邽�߂̔ėp�I�Ȋ֐�
				CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_Mesh[m].IndexBuffer);
			}
			delete[] index;



		}
	}
}

void CModelAnimation::Unload()
{
	for (auto m = 0; m < m_MeshNum; m++)
	{
		m_Mesh[m].VertexBuffer->Release();
		m_Mesh[m].IndexBuffer->Release();
	}

	for (auto i = 0; i < PLAYER_MAX; i++) {
		aiReleaseImport(m_Scene[i]);
	}
}
