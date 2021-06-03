#include "entity.h"
#include "definitions.h"
#include <array>
#include "../core/interfaces.h"

player_info base_entity::get_info()
{
	player_info info;
	g_engine_client->get_player_info(get_index(), &info);
	return info;
}

std::optional<vector> base_entity::get_bone_position(int bone)
{
	std::array<matrix3x4_t, MAXSTUDIOBONES> bones = { };

	if (this->setup_bones(bones.data(), bones.size(), BONE_FLAG_USED_BY_ANYTHING, 0.f))
		return bones.at(bone).at(3);

	return std::nullopt;
}

base_combat_weapon* base_entity::get_active_weapon()
{
	return reinterpret_cast<base_combat_weapon*>(g_entity_list->get_client_entity_from_handle(this->m_hActiveWeapon()));
}

bool base_entity::is_enemy(base_entity* entity)
{
	static auto mp_teammates_are_enemies = g_cvar_system->find_var("mp_teammates_are_enemies");

	if (mp_teammates_are_enemies != nullptr && mp_teammates_are_enemies->get_bool() && 
		this->m_iTeamNum() == entity->m_iTeamNum() && this != entity)
		return true;

	if (this->m_iTeamNum() != entity->m_iTeamNum())
		return true;

	return false;
}