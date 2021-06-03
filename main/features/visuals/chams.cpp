#include "chams.h"
#include "../../sdk/entity.h"
#include "../../sdk/color.h"
#include "../../core/hooks.h"
#include "../../global.h"

void override_material(const col& clr, bool ignore_z)
{
	auto material = g_material_system->find_material("debug/debugambientcube", nullptr);

	material->alpha_modulate(clr.a() / 255.f);
	material->color_modulate(clr.r() / 255.f, clr.g() / 255.f, clr.b() / 255.f);
	material->set_flag(MATERIAL_VAR_IGNOREZ, ignore_z);

	if (const auto $envmaptint = material->find_var("$envmaptint", nullptr, false)) 
	{
		$envmaptint->set_value(vector(clr.r() / 255.f, clr.g() / 255.f, clr.b() / 255.f));
	}

	g_model_render->forced_material_override(material);
}

bool chams::on_draw_model(model_render* ecx, void* edx, void* context, const draw_model_state& state, const model_render_info& info,
	matrix3x4_t* bone_to_world)
{
	static auto o_draw_model_execute = hooks::draw_model_execute::original;

	if (strstr(info.m_model->m_name, "models/player") != nullptr)
	{
		auto player = reinterpret_cast<cs_player*>(g_entity_list->get_client_entity(info.m_index));
		if (!player || !player->is_alive())
			return true;

		if (player != csgo::m_local)
		{
			override_material(col(0, 100, 255), true);

			o_draw_model_execute(ecx, edx, context, state, info, bone_to_world);

			override_material(col(0, 100, 255), false);
		}
		else
		{
			override_material(col(0, 100, 255, player->m_bIsScoped() ? 180 : 255), false);
		}
	}

	return true;
}