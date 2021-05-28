#pragma once
#include "../common.h"

enum key_mode 
{
	ON_KEY,
	TOGGLE,
	AWAY_KEY
};

namespace input 
{
	bool setup();
	void restore();

	long D3DAPI wnd_proc(HWND hwnd, uint32_t msg, uint32_t w_param, uint32_t l_param);

	template <key_mode M>
	__declspec(noinline) static bool get_key(uint32_t key) {
		switch (M) {
		case ON_KEY: return HIWORD(GetKeyState(key)); break;
		case TOGGLE: return LOWORD(GetKeyState(key)); break;
		case AWAY_KEY: return !HIWORD(GetKeyState(key)); break;
		}

		return false;
	}

	inline HWND m_hwnd;
	inline WNDPROC m_original_wnd_proc;
};