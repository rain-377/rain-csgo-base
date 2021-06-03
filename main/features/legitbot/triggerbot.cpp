#include "triggerbot.h"
#include "../../utils/config.h"

void triggerbot::on_create_move(user_cmd* cmd)
{
	if (!csgo::m_local || !csgo::m_local->is_alive() || !config::get<bool>(HASH_CT("legitbot.triggerbot.enabled")))
		return;

	auto weapon = csgo::m_local->get_active_weapon();
	if (!weapon)
		return;

	auto weapon_data = g_weapon_system->get_weapon_data(weapon->m_iItemDefinitionIndex());
	if (!weapon_data)
		return;

	static auto weapon_recoil_scale = g_cvar_system->find_var("weapon_recoil_scale");

	qangle view = cmd->viewangles;
	view += csgo::m_local->m_aimPunchAngle() * weapon_recoil_scale->get_float();
	vector start, end, forward;

	math::angle_vectors(view, &forward);

	start = csgo::m_local->get_eye_position();
	forward *= weapon_data->m_range;
	end = start + forward;

	game_trace trace;

	ray ray(start, end);
	c_trace_filter filter(csgo::m_local);

	g_engine_trace->trace_ray(ray, MASK_SHOT, &filter, &trace);
	const auto entity = reinterpret_cast<base_entity*>(trace.m_hit_entity);

	if (!entity
		|| entity->is_dormant()
		|| !entity->is_player())
		return;

	const auto player = reinterpret_cast<cs_player*>(entity);

	if (!player->is_alive()
		|| !player->is_enemy(csgo::m_local))
		return;

	cmd->buttons |= IN_ATTACK;
}