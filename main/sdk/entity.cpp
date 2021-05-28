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