#include "triggerbot.h"

void triggerbot::on_create_move(user_cmd* cmd)
{
	if (!csgo::m_local || !csgo::m_local->is_alive())
		return;

	auto weapon = reinterpret_cast<base_combat_weapon*>(g_entity_list->get_client_entity_from_handle(csgo::m_local->m_hActiveWeapon()));
	if (!weapon)
		return;

	auto weapon_data = g_weapon_system->get_weapon_data(weapon->m_iItemDefinitionIndex());
	if (!weapon_data)
		return;

	static auto weapon_recoil_scale = g_cvar_system->find_var("weapon_recoil_scale");

	qangle view = csgo::m_cmd->viewangles;
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

	const auto player = reinterpret_cast<base_player*>(entity);

	if (!player->is_alive()
		|| !player->m_iTeamNum() == csgo::m_local->m_iTeamNum())
		return;

	csgo::m_cmd->buttons |= IN_ATTACK;
}