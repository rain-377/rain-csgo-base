#include "interfaces.h"

bool interfaces::setup()
{
	g_client = get<client*>(CLIENT, "VClient018");
	if (!g_client)
		return false;

	g_entity_list = get<client_entity_list*>(CLIENT, "VClientEntityList003");
	if (!g_entity_list)
		return false;

	g_client_mode = **(client_mode***)((*(uintptr_t**)g_client)[10] + 0x5);
	if (!g_client_mode)
		return false;

	g_client_state = **reinterpret_cast<client_state***>(utils::find_signature(ENGINE, "A1 ? ? ? ? 8B 88 ? ? ? ? 85 C9 75 07") + 0x1);
	if (!g_client_state)
		return false;

	g_cvar_system = get<cvar_system*>("vstdlib.dll", "VEngineCvar007");
	if (!g_cvar_system)
		return false;

	g_direct_device = **reinterpret_cast<IDirect3DDevice9***>(utils::find_signature("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 0x1);
	if (!g_direct_device)
		return false;

	g_engine_client = get<engine_client*>(ENGINE, "VEngineClient014");
	if (!g_engine_client)
		return false;

	g_engine_trace = get<engine_trace*>(ENGINE, "EngineTraceClient004");
	if (!g_engine_trace)
		return false;

	g_global_vars = **reinterpret_cast<global_vars_base***>(utils::find_signature(CLIENT, "A1 ? ? ? ? 5E 8B 40 10") + 0x1);
	if (!g_global_vars)
		return false;

	g_material_system = get<material_system*>("materialsystem.dll", "VMaterialSystem080");
	if (!g_material_system)
		return false;

	g_model_render = get<model_render*>(ENGINE, "VEngineModel016");
	if (!g_model_render)
		return false;

	g_model_info = get<model_info*>(ENGINE, "VModelInfoClient004");
	if (!g_model_info)
		return false;

	g_prediction = get<prediction*>(CLIENT, "VClientPrediction001");
	if (!g_prediction)
		return false;

	g_studio_render = get<studio_render*>("studiorender.dll", "VStudioRender026");
	if (!g_studio_render)
		return false;

	g_surface = get<surface*>("vguimatsurface.dll", "VGUI_Surface031");
	if (!g_surface)
		return false;

	g_weapon_system = *reinterpret_cast<weapon_system**>(utils::find_signature(CLIENT, "8B 35 ? ? ? ? FF 10 0F B7 C0") + 0x2);
	if (!g_weapon_system)
		return false;

	return true;
}