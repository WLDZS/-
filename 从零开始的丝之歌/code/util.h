#ifndef UTIL_H
#define UTIL_H

#include <random>
#include<graphics.h>
#include"camera.h"
#include"vector2.h"
#pragma comment(lib,"WINMM.lib")
#pragma comment(lib,"MSIMG32.lib")

struct Rect { int x, y, w, h; };

inline void putimage_ex(Camera* camera, IMAGE* img, const Rect* rect_dst, const Rect* rect_src = nullptr) {
	static BLENDFUNCTION blend_func = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	const Vector2 cam_pos = camera->get_position();
	const Vector2 cam_size = camera->get_size();
	AlphaBlend(GetImageHDC(GetWorkingImage()), rect_dst->x - (cam_pos.x - cam_size.x / 2), rect_dst->y - (cam_pos.y - cam_size.y / 2),
		rect_dst->w, rect_dst->h,
		GetImageHDC(img), rect_src ? rect_src->x : 0, rect_src ? rect_src->y : 0,
		rect_src ? rect_src->w : img->getwidth(), rect_src ? rect_src->h : img->getheight(), blend_func);
}

inline void load_audio(LPCWSTR path, LPCWSTR id) {
	static TCHAR buf[512];
	_stprintf_s(buf, _T("open %s alias %s"), path, id);
	mciSendString(buf, NULL, 0, NULL);
}

inline void play_audio(LPCWSTR id, bool is_loop = false) {
	static TCHAR buf[512];
	_stprintf_s(buf, _T("play %s %sfrom 0"), id, is_loop ? _T("repeat") : _T(""));
	mciSendString(buf, NULL, 0, NULL);
}

inline void stop_audio(LPCWSTR id) {
	static TCHAR buf[512];
	_stprintf_s(buf, _T("stop %s"), id);
	mciSendString(buf, NULL, 0, NULL);
}

#endif // UTIL_H