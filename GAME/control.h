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

	float Wheel = 0;
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

	float Wheel = 0.0f;
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

	XMVECTOR At = XMVectorSet(0, 5, 0, 0);
	float RotH = XM_PI;
	float RotV = -0.5f;
	float Dist = 50.0f;

	float SpeedRotH = 1.5f;
	float SpeedRotV = 1.0f;
	float LimitRotV = 89.0f / 180.0f * XM_PI;
	float DistMin = 0.5f;
	float DistMax = 200.0f;
	float SpeedDist = 20.0f;
	float SpeedMove = 20.0f;
	float SpeedMouseRot = 0.01f;
	float SpeedWheelMove = 3.0f;
	float SpeedMouseSlide = 0.15f;

	XMVECTOR IniAt = XMVectorSet(0, 5, 0, 0);
	float IniRotH = XM_PI;
	float IniRotV = -0.5f;
	float IniDist = 50.0f;

	bool bCharaMode = false;
	XMVECTOR vCharaPos = XMVectorSet(0, 0, 0, 1);
	XMVECTOR vCharaRot = XMVectorSet(0, 0, 0, 0);

	void Reset();
	void Ctrl(const KeyInput& key, FLOAT elapsed_time_sec);

	XMMATRIX GetViewMatrix();

};


#endif // !CONTROL_H
