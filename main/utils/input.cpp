#include "input.h"
#include "../core/menu.h"
#include "../core/interfaces.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool input::setup() 
{
	auto creation_parameters = D3DDEVICE_CREATION_PARAMETERS();

	g_direct_device->GetCreationParameters(&creation_parameters);

	m_hwnd = creation_parameters.hFocusWindow;

	m_original_wnd_proc = reinterpret_cast<WNDPROC>(SetWindowLongA(m_hwnd, GWL_WNDPROC, reinterpret_cast<long>(wnd_proc)));

	return true;
}

void input::restore()
{ 
	SetWindowLongPtrA(m_hwnd, GWL_WNDPROC, reinterpret_cast<long>(m_original_wnd_proc));
}

long D3DAPI input::wnd_proc(HWND hwnd, uint32_t msg, uint32_t w_param, uint32_t l_param)
{
	if (menu::get().m_visible) {
		ImGui_ImplWin32_WndProcHandler(hwnd, msg, w_param, l_param);
		return 1;
	}

	return CallWindowProcA(m_original_wnd_proc, hwnd, msg, w_param, l_param);
}