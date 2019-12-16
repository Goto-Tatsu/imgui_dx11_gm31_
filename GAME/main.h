#ifndef MAIN_H_
#define MAIN_H_

#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX

/* ====== DEFAULT =================== */
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <iostream>
#include <map>

#include <d3d11.h>
#include <DirectXMath.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "xaudio2.lib")
using namespace DirectX;

/* ================================ */


/* ====== IMGUI =================== */
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
/* ================================ */


/* ====== ASSIMP =================== */
#pragma comment(lib, "assimp.lib")
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
/* ================================ */

// 
#include "imgui_manager.h"

#define SCREEN_WIDTH	(1280)			// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(780)			// �E�C���h�E�̍���


HWND GetWindow();
HINSTANCE GetHInstance();


#endif // !MAIN_H_