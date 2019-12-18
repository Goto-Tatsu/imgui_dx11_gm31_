#ifndef SCENE_H_
#define SCENE_H_

#include <typeinfo>	// typeid���g�p���邽��
#include <vector>	// vector���g�p���邽��
#include "main.h"


#define ENEMY_MAX	(1)

enum LAYER
{
	LAYER_CAMERA,	// �J�������C���[
	LAYER_BG,		// �w�i(BackGround)���C���[
	LAYER_3DMODELS,	// 3D���f�����C���[
	LAYER_EFFECTS,	// Effects���C���[
	LAYER_2DPOLYGONS,	// 2D�|���S�����C���[

	LAYER_MAX
};

class CScene {
protected:
	std::list<CGameObject*> m_GameObject[LAYER_MAX];

public:
	// �R���X�g���N�^
	CScene() {};

	// �f�X�g���N�^
	virtual ~CScene() {};

	// �z��p�̊Ǘ��e���v���[�g
	template<typename ClassName>ClassName* AddGameObject(int Layer) {
		ClassName* object = new ClassName();
		object->Init();
		m_GameObject[Layer].push_back(object);
		return object;
	}

	// typeid���g�p�A�����e���v���[�g�@
	template<typename ClassName>ClassName* GetGameObject(int Layer) {
		for (CGameObject* object : m_GameObject[Layer]) {
			if (typeid(*object) == typeid(ClassName)) {
				return (ClassName*)object;
			}
		}
	}

	// �@�̕�����ver
	template<typename ClassName>std::vector<ClassName*> GetGameObjects(int Layer) {
		std::vector<ClassName*> objects;
		for (CGameObject* object : m_GameObject[Layer]) {
			if (typeid(*object) == typeid(ClassName)) {
				objects.push_back((ClassName*)object);
			}
		}
		return objects;
	}


	/////////////////////
	// ����������
	/////////////////////
	virtual void Init() {
		// ���C���[�Ǘ�
		// Camera 
		AddGameObject<CCamera>(LAYER_CAMERA);
		
		// Field
		AddGameObject<CField>(LAYER_BG);
		
		// Player,Enemy,Ball
		//AddGameObject<CPlayer>(LAYER_3DMODELS);
		for (int i = 0; i < ENEMY_MAX; i++) {
			AddGameObject<CEnemy>(LAYER_3DMODELS);
		}
		AddGameObject<CBall>(LAYER_3DMODELS);
		
		// 2Dpolygon

	}

	/////////////////////
	// �I������
	/////////////////////
	virtual void Uninit() {
		for (int i = 0; i < LAYER_MAX; i++) {
			for (CGameObject* object : m_GameObject[i])
			{
				// ���g�̔j��
				object->Uninit();
				delete object;
			}

			// ���ꕨ�̔j��
			m_GameObject[i].clear();
		}
	}

	/////////////////////
	// �X�V����
	/////////////////////
	virtual void Update() {
		for (int i = 0; i < LAYER_MAX; i++) {
			for (CGameObject* object : m_GameObject[i])
			{
				object->Update();
			}

			m_GameObject[i].remove_if([](CGameObject* object) { return object->Destroy(); });
		}
	}


	/////////////////////
	// �`�揈��
	/////////////////////
	virtual void Draw() {
		// �z��Ǘ��pfor�\��
		for (int i = 0; i < LAYER_MAX; i++) {
			for (CGameObject* object : m_GameObject[i]) {
				object->Draw();
			}
		}
	}


	/////////////////////
	// �j�󏈗�
	/////////////////////
	void DestroyGameObject(CGameObject* GameObject) {
		GameObject->SetDestroy();
	}


};

#endif // !SCENE_H_
