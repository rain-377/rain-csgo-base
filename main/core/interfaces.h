#pragma once
#include "../common.h"
#include "../sdk/interfaces/client.h"
#include "../sdk/interfaces/client_entity_list.h"
#include "../sdk/interfaces/client_mode.h"
#include "../sdk/interfaces/client_state.h"
#include "../sdk/interfaces/cvar_system.h"
#include "../sdk/interfaces/engine_client.h"
#include "../sdk/interfaces/global_vars_base.h"
#include "../sdk/interfaces/material_system.h"
#include "../sdk/interfaces/model_render.h"
#include "../sdk/interfaces/net_channel.h"
#include "../sdk/interfaces/prediction.h"
#include "../sdk/interfaces/studio_render.h"
#include "../sdk/interfaces/surface.h"

namespace interfaces
{
	bool setup();

	template <class t> 
	inline t get(std::string_view module_name, std::string_view interface_name)
	{
		HMODULE module = GetModuleHandleA(module_name.data());

		if (!module)
			return t();

		auto create_interface = GetProcAddress(module, "CreateInterface");

		if (!create_interface)
			return t();

		auto create_interface_fn = reinterpret_cast<t(*)(const char*, int*)>(create_interface);

		if (!create_interface_fn)
			return t();

		auto interface_address = create_interface_fn(interface_name.data(), nullptr);

		if (!interface_address)
			return t();

		return interface_address;
	}
};

inline client* g_client;
inline client_entity_list* g_entity_list;
inline client_mode* g_client_mode;
inline client_state* g_client_state;
inline cvar_system* g_cvar_system;
inline IDirect3DDevice9* g_direct_device;
inline engine_client* g_engine_client;
inline global_vars_base* g_global_vars;
inline material_system* g_material_system;
inline model_render* g_model_render;
inline net_channel* g_net_channel;
inline prediction* g_prediction;
inline studio_render* g_studio_render;
inline surface* g_surface;