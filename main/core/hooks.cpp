#include "hooks.h"
#include "../utils/math.h"
#include "../features/features.h"
#include "../utils/render.h"
#include "../../dependencies/minhook/minhook.h"

bool create_hook(void* target, void* detour,
	void* original)
{
	const int result = MH_CreateHook(static_cast<LPVOID>(target),
		static_cast<LPVOID>(detour), static_cast<LPVOID*>(original));

	return (result == MH_OK);
}


bool hooks::setup()
{
	if (MH_Initialize() != MH_OK)
		return false;

	if (!create_hook(utils::get_virtual<void*>(g_client_mode, 24), &create_move::hooked, &create_move::original))
		return false;

	if (!create_hook(utils::get_virtual<void*>(g_client, 37), &frame_stage_notify::hooked, &frame_stage_notify::original))
		return false;

	if (!create_hook(utils::get_virtual<void*>(g_direct_device, 16), &reset::hooked, &reset::original))
		return false;

	if (!create_hook(utils::get_virtual<void*>(g_direct_device, 42), &end_scene::hooked, &end_scene::original))
		return false;

	if (!create_hook(utils::get_virtual<void*>(g_surface, 67), &lock_cursor::hooked, &lock_cursor::original))
		return false;

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		return false;

	return true;
}

void hooks::restore()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);

	MH_Uninitialize();
}

bool __stdcall hooks::create_move::hooked(float input_sample_time, user_cmd* cmd)
{
	if (!cmd || !cmd->command_number)
		return original(input_sample_time, cmd);

	if (original(input_sample_time, cmd))
		g_prediction->set_local_view_angles(cmd->viewangles);

	auto local = reinterpret_cast<base_player*>(g_entity_list->get_client_entity(g_engine_client->get_local_player()));

	const volatile auto base_address = *reinterpret_cast<uintptr_t*>(reinterpret_cast<std::uintptr_t>(_AddressOfReturnAddress()) - sizeof(uintptr_t));
	bool& send_packet = *reinterpret_cast<bool*>(base_address - 0x1C);

	cmd->viewangles.normalize();

	return false;
}

void __stdcall hooks::frame_stage_notify::hooked(client_frame_stage stage)
{
	if (render::m_initialized)
	render::begin();

	original(stage);
}

long D3DAPI hooks::reset::hooked(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters) {
	ImGui_ImplDX9_InvalidateDeviceObjects();

	const HRESULT reset = original(pDevice, pPresentationParameters);

	if (reset == D3D_OK)
		ImGui_ImplDX9_CreateDeviceObjects();

	return reset;
}

long D3DAPI hooks::end_scene::hooked(IDirect3DDevice9* pDevice) {
	static void* used_address = nullptr;

	if (used_address == nullptr)
	{
		MEMORY_BASIC_INFORMATION info;
		VirtualQuery(_ReturnAddress(), &info, sizeof(MEMORY_BASIC_INFORMATION));

		char module_name[MAX_PATH];
		GetModuleFileName(static_cast<HMODULE>(info.AllocationBase), module_name, MAX_PATH);

		if (strstr(module_name, "gameoverlayrenderer.dll") != nullptr)
			used_address = _ReturnAddress();
	}

	if (_ReturnAddress() == used_address)
	{
		if (!render::m_initialized)
			render::setup(pDevice);

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		menu::get().on_paint();

		render::add_to_draw_list();

		ImGui::EndFrame();
		ImGui::Render();

		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}

	return original(pDevice);
}

void __fastcall hooks::lock_cursor::hooked(surface* thisptr, int edx)
{
	if (menu::get().m_visible)
		g_surface->unlock_cursor();
	else
		original(thisptr, edx);
}