#ifndef CONTROL_H_
#define CONTROL_H_

#include <windows.h>
#include <directxmath.h>

struct MouseCapture
{
	struct POINT {
		POINT(int a = 0, int b = 0) : x(a), y(b) {}
		int x, y;
	};

	FLOAT Wheel = 0;
	POINT CursorPt = POINT(-10000, -10000);
};

//-------------------
// キーボード入力
struct KeyInput
{
	typedef MouseCapture::POINT POINT;
	static const int KEY_ARRAY_NUM = 256;
	BYTE aKeyboard[KEY_ARRAY_NUM];
	BYTE aKeyboardOld[KEY_ARRAY_NUM];

	FLOAT Wheel = 0.0f;
	POINT CursorPt = POINT(-10000, -10000);	//現在の位置
	POINT LastPt = POINT(-10000, -10000);	//1つ前の位置
	POINT LClickPt = POINT(-10000, -10000);	//Lクリック位置
	POINT MClickPt = POINT(-10000, -10000);	//Mクリック位置
	POINT RClickPt = POINT(-10000, -10000);	//Rクリック位置

	KeyInput() {
		Reset();
	}

	void Reset();
	bool Update(const MouseCapture& mouse);
	bool Update(const MouseCapture& mouse, BYTE keyary[KEY_ARRAY_NUM]);
	bool KeyDown(int vk) const;
	bool KeyOn(int vk) const;
	bool KeyUp(int vk) const;
};


//-------------------
// カメラ操作
struct CameraCtrl
{

	DirectX::XMVECTOR At = DirectX::XMVectorSet(0, 5, 0, 0);
	FLOAT RotH = DirectX::XM_PI;
	FLOAT RotV = -0.5f;
	FLOAT Dist = 50.0f;

	FLOAT SpeedRotH = 1.5f;
	FLOAT SpeedRotV = 1.0f;
	FLOAT LimitRotV = 89.0f / 180.0f * DirectX::XM_PI;
	FLOAT DistMin = 0.5f;
	FLOAT DistMax = 200.0f;
	FLOAT SpeedDist = 20.0f;
	FLOAT SpeedMove = 20.0f;
	FLOAT SpeedMouseRot = 0.01f;
	FLOAT SpeedWheelMove = 3.0f;
	FLOAT SpeedMouseSlide = 0.15f;

	DirectX::XMVECTOR IniAt = DirectX::XMVectorSet(0, 5, 0, 0);
	FLOAT IniRotH = DirectX::XM_PI;
	FLOAT IniRotV = -0.5f;
	FLOAT IniDist = 50.0f;

	bool bCharaMode = false;
	DirectX::XMVECTOR vCharaPos = DirectX::XMVectorSet(0, 0, 0, 1);
	DirectX::XMVECTOR vCharaRot = DirectX::XMVectorSet(0, 0, 0, 0);

	void Reset();
	void Ctrl(const KeyInput& key, FLOAT elapsed_time_sec);

	DirectX::XMMATRIX GetViewMatrix();

};


#endif // !CONTROL_H
