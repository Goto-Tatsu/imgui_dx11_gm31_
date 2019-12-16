#ifndef CAMERA_H_
#define CAMERA_H_

class CCamera : public CGameObject	// CGameObject����p��
{
private:

	XMVECTOR camPosition;
	XMVECTOR camAt;
	XMVECTOR camUp;

	RECT						m_Viewport;	// 
	float						m_fCameraAngle;// �J�����A���O��

	XMMATRIX	m_ViewMatrix;			// �r���[���W�s��
	XMMATRIX	m_InvViewMatrix;		// �r���[�t�s��ϊ��p�i�[�s��
	XMMATRIX	m_ProjectionMatrix;		// �v���W�F�N�V�����s��

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	XMMATRIX GetViewMatrix(void) { return m_ViewMatrix; };
	XMMATRIX GetProjectionMatrix(void) { return m_ProjectionMatrix; };


	XMFLOAT3					m_Position;	// �J�����̈ʒu(���W)
	XMFLOAT3					m_Rotation;	// �J�����̉�]�v�f
	XMFLOAT3					m_Target;	// �����_

	bool GetVisibility(XMFLOAT3 Position);
};

#endif // !CAMERA_H_