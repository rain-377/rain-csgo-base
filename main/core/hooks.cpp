#include "hooks.h"
#include "../utils/math.h"
#include "../features/features.h"
#include "../utils/render.h"
#include "../global.h"
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

	if (!create_hook(utils::get_virtual<void*>(g_model_render, 21), &draw_model_execute::hooked, &draw_model_execute::original))
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
	csgo::m_cmd = cmd;
	csgo::m_local = reinterpret_cast<base_animating*>(g_entity_list->get_client_entity(g_engine_client->get_local_player()));
	
	if (!cmd || !cmd->command_number)
		return original(input_sample_time, cmd);

	if (original(input_sample_time, cmd))
		g_prediction->set_local_view_angles(cmd->viewangles);

	const volatile auto base_address = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(_AddressOfReturnAddress()) - sizeof(uintptr_t));
	bool& send_packet = *reinterpret_cast<bool*>(base_address - 0x1C);

	static auto cl_forwardspeed = g_cvar_system->find_var("cl_forwardspeed");
	static auto cl_sidespeed = g_cvar_system->find_var("cl_sidespeed");
	static auto cl_upspeed = g_cvar_system->find_var("cl_upspeed");

	cmd->forwardmove = std::clamp(cmd->forwardmove, -cl_forwardspeed->get_float(), cl_forwardspeed->get_float());
	cmd->sidemove = std::clamp(cmd->sidemove, -cl_sidespeed->get_float(), cl_sidespeed->get_float());
	cmd->upmove = std::clamp(cmd->upmove, -cl_upspeed->get_float(), cl_upspeed->get_float());

	cmd->viewangles.normalize();

	return false;
}

void __stdcall hooks::frame_stage_notify::hooked(client_frame_stage stage)
{
	if (render::m_initialized)
	render::begin();

	original(stage);
}

void __fastcall hooks::draw_model_execute::hooked(model_render* ecx, void* edx, void* context, const draw_model_state& state,
	const model_render_info& info, matrix3x4_t* bone_to_world)
{
	if (chams::get().on_draw_model(ecx, edx, context, state, info, bone_to_world)) 
	{
		original(ecx, edx, context, state, info, bone_to_world);
	}

	g_model_render->forced_material_override(nullptr);
}


long D3DAPI hooks::reset::hooked(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters) 
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	const HRESULT reset = original(pDevice, pPresentationParameters);

	if (reset == D3D_OK)
		ImGui_ImplDX9_CreateDeviceObjects();

	return reset;
}

long D3DAPI hooks::end_scene::hooked(IDirect3DDevice9* pDevice) 
{
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