/*==============================================================================


														 Author : TATSUKI GOTO
														 Date   : 2019/06/04
--------------------------------------------------------------------------------
==============================================================================*/

#include "main.h"
#include "manager.h"
#include "renderer.h"

const char* CLASS_NAME = "DX11AppClass";
const char* WINDOW_NAME = "DX11";


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


HWND g_Window;
HINSTANCE g_hInstance;



HWND GetWindow()
{
	return g_Window;
}

HINSTANCE GetHInstance()
{
	return g_hInstance;
}

//=============================================================================
// �E�B���h�E�̐ݒ肨��ю��s
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	// hInstance�i�[
	g_hInstance = hInstance;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	g_Window = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
		(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
		NULL,
		NULL,
		hInstance,
		NULL);


	// ����������(�E�B���h�E���쐬���Ă���s��)
	CManager::Init();


	// �E�C���h�E�̕\��(�����������̌�ɍs��)
	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);

	//�t���[���J�E���g������
	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;


	// ���b�Z�[�W���[�v
	MSG msg;
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				CManager::Update();

				// �`�揈��
				CManager::Draw();
			}
		}
	}

	timeEndPeriod(1);				// ����\��߂�

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	CManager::Uninit();

	return (int)msg.wParam;
}


//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================
// Win32 message handler
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//	IMGUI�p�̃E�B���h�E�����邩�m�F
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	// �Q�[���E�B���h�E�ɑ΂��鉞��
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
