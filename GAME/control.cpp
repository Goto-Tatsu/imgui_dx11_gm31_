#include "control.h"
#include "stdio.h"

using namespace DirectX;

void KeyInput::Reset()
{
	for (int i = 0; i < KEY_ARRAY_NUM; ++i) {
		aKeyboard[i] = 0;
		aKeyboardOld[i] = 0;
	}
}

bool KeyInput::Update(const MouseCapture& mouse)
{
	BYTE keyary[KEY_ARRAY_NUM];
	if (!GetKeyboardState(keyary)) {
		for (int i = 0; i < KEY_ARRAY_NUM; ++i) { keyary[i] = 0; }
		return false;
	}
	return Update(mouse, keyary);
}

bool KeyInput::Update(const MouseCapture& mouse, BYTE keyary[KEY_ARRAY_NUM])
{
	for (int i = 0; i < KEY_ARRAY_NUM; ++i) {
		aKeyboardOld[i] = aKeyboard[i];
	}
	for (int i = 0; i < KEY_ARRAY_NUM; ++i) { aKeyboard[i] = keyary[i]; }

	Wheel = mouse.Wheel;
	LastPt = CursorPt;
	CursorPt = mouse.CursorPt;
	if (KeyDown(VK_LBUTTON))LClickPt = CursorPt;
	if (KeyDown(VK_MBUTTON))MClickPt = CursorPt;
	if (KeyDown(VK_RBUTTON))RClickPt = CursorPt;

	return true;
}


bool KeyInput::KeyDown(int vk) const
{
	if ((unsigned)vk >= KEY_ARRAY_NUM)return false;
	bool now = (aKeyboard[vk] & 0x80) != 0;
	bool old = (aKeyboardOld[vk] & 0x80) != 0;
	return now && !old;
}

bool KeyInput::KeyOn(int vk) const
{
	if ((unsigned)vk >= KEY_ARRAY_NUM)return false;
	return (aKeyboard[vk] & 0x80) != 0;
}

bool KeyInput::KeyUp(int vk) const
{
	if ((unsigned)vk >= KEY_ARRAY_NUM)return false;
	bool now = (aKeyboard[vk] & 0x80) != 0;
	bool old = (aKeyboardOld[vk] & 0x80) != 0;
	return !now && old;
}

//======================================================================
DirectX::XMMATRIX CameraCtrl::GetViewMatrix()
{
	XMVECTOR campos = { 0,0,Dist, 1 };
	XMMATRIX camrot = XMMatrixRotationRollPitchYaw(RotV, RotH, 0);
	campos = XMVector4Transform(campos, camrot);
	XMVECTOR lookat = At;
	if (bCharaMode) {
		lookat += vCharaPos;
	}

	XMVECTOR Eye = XMVectorAdd(campos, lookat);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	return XMMatrixLookAtLH(Eye, lookat, Up);
}


//-----------------------------
void CameraCtrl::Reset()
{
	At = IniAt;
	RotH = IniRotH;
	RotV = IniRotV;
	Dist = IniDist;
	vCharaPos = DirectX::XMVectorSet(0, 0, 0, 1);
	vCharaRot = DirectX::XMVectorSet(0, 0, 0, 0);

}

namespace {

	// -ƒÎ`+ƒÎ@ŒÀ’è 
	FLOAT SubAngle(FLOAT a0, FLOAT a1)
	{
		FLOAT sub = a0 - a1;
		if (sub > XM_PI)sub -= XM_2PI;
		if (sub < -XM_PI)sub += XM_2PI;
		return sub;
	}
	FLOAT AngleLimit(FLOAT a)
	{
		int i = (int)(a / XM_2PI);
		a = a - FLOAT(i) * XM_2PI;
		if (a > XM_PI)a -= XM_2PI;
		if (a < -XM_PI)a += XM_2PI;
		return a;
	}

}
//-----------------------------
void CameraCtrl::Ctrl(const KeyInput& key_input, FLOAT elapsed_time_sec)
{
	static bool last_move_camera = false;

	bool move_camera = false;
	if (key_input.KeyOn(VK_RBUTTON)) {
		move_camera = true;
		FLOAT dx = static_cast<FLOAT>(key_input.CursorPt.x - key_input.LastPt.x);
		FLOAT dy = static_cast<FLOAT>(key_input.CursorPt.y - key_input.LastPt.y);
		RotH += SpeedMouseRot * dx;
		RotV -= SpeedMouseRot * dy;
		if (RotH > XM_PI)RotH -= XM_2PI;
		if (RotH < -XM_PI)RotH += XM_2PI;
		if (RotV > LimitRotV)RotV = LimitRotV;
		if (RotV < -LimitRotV)RotV = -LimitRotV;
	}
	if (key_input.Wheel != 0.0f) {
		move_camera = true;
		Dist -= SpeedWheelMove * key_input.Wheel;
		if (Dist < DistMin)Dist = DistMin;
		if (Dist > DistMax)Dist = DistMax;
	}
	if (key_input.KeyOn(VK_MBUTTON)) {
		move_camera = true;
		XMMATRIX view = GetViewMatrix();
		view = XMMatrixInverse(nullptr, view);
		FLOAT dx = static_cast<FLOAT>(key_input.CursorPt.x - key_input.LastPt.x);
		FLOAT dy = static_cast<FLOAT>(key_input.CursorPt.y - key_input.LastPt.y);
		At -= view.r[0] * dx * SpeedMouseSlide;
		At += view.r[1] * dy * SpeedMouseSlide;
	}

	if (key_input.KeyOn(VK_RIGHT)) {
		move_camera = true;
		RotH += SpeedRotH * elapsed_time_sec;
		if (RotH > XM_PI)RotH -= XM_2PI;
	}
	if (key_input.KeyOn(VK_LEFT)) {
		move_camera = true;
		RotH -= SpeedRotH * elapsed_time_sec;
		if (RotH < -XM_PI)RotH += XM_2PI;
	}
	if (key_input.KeyOn(VK_DOWN)) {
		move_camera = true;
		RotV += SpeedRotV * elapsed_time_sec;
		if (RotV > LimitRotV)RotV = LimitRotV;
	}
	if (key_input.KeyOn(VK_UP)) {
		move_camera = true;
		RotV -= SpeedRotV * elapsed_time_sec;
		if (RotV < -LimitRotV)RotV = -LimitRotV;
	}
	if (key_input.KeyOn(VK_PRIOR)) {//PageUp
		move_camera = true;
		Dist -= SpeedDist * elapsed_time_sec;
		if (Dist < DistMin)Dist = DistMin;
	}
	if (key_input.KeyOn(VK_NEXT)) {//PageDown
		move_camera = true;
		Dist += SpeedDist * elapsed_time_sec;
		if (Dist > DistMax)Dist = DistMax;
	}

	XMVECTOR move = { 0,0,0,0 };
	if (key_input.KeyOn('W'))move = XMVectorSetZ(move, -1.0f);
	if (key_input.KeyOn('S'))move = XMVectorSetZ(move, 1.0f);
	if (key_input.KeyOn('D'))move = XMVectorSetX(move, -1.0f);
	if (key_input.KeyOn('A'))move = XMVectorSetX(move, 1.0f);
	if (key_input.KeyOn('C'))move = XMVectorSetY(move, -1.0f);
	if (key_input.KeyOn('E'))move = XMVectorSetY(move, 1.0f);
	if (XMVectorGetX(XMVector3Length(move)) > 0.0f) {
		move_camera = true;
		move = XMVector3Normalize(move);
		move = XMVectorScale(move, SpeedMove * elapsed_time_sec);
		move = XMVector3Transform(move, XMMatrixRotationY(RotH));
		if (key_input.KeyOn(VK_LSHIFT))move *= 2.0f;
		if (bCharaMode) {
			vCharaPos += move;

			FLOAT move_ang = atan2f(-XMVectorGetX(move), -XMVectorGetZ(move));
			FLOAT now_ang = XMVectorGetY(vCharaRot);
			FLOAT sub_ang = SubAngle(move_ang, now_ang);
			const FLOAT rot_speed = 0.25f;
			if (sub_ang > rot_speed)sub_ang = rot_speed;
			if (sub_ang < -rot_speed)sub_ang = -rot_speed;
			now_ang = AngleLimit(now_ang + sub_ang);
			//kari
			vCharaRot = XMVectorSet(0, now_ang, 0, 0);
		}
		else {
			At = XMVectorAdd(At, move);
		}
	}
#if 0
	if (!move_camera && last_move_camera) {
		//‘€ìI‚í‚è
		char camera[256];
		sprintf_s(camera, "\tINI_ROT %f, %f;\n\tINI_LOOKAT %f, %f, %f;\n\tINI_DIST %f;\n//-----\n",
			RotH, RotV,
			//RotH*180.0f / XM_PI, RotV*180.0f / XM_PI,
			XMVectorGetX(At), XMVectorGetY(At), XMVectorGetZ(At),
			Dist);
		OutputDebugStringA(camera);
	}
	last_move_camera = move_camera;
#endif

}

