#pragma once
#include "netvars/netvars.h"
#include "studio.h"
#include "animations.h"
#include "client_entity.h"
#include "interfaces/engine_client.h"

#define OFFSET(name, type, offset) [[nodiscard]] type& name \
{ \
return *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(this) + offset); \
}

class base_entity : public client_entity
{
public:
	NETVAR(vector, m_vecOrigin, "DT_BaseEntity->m_vecOrigin")
	NETVAR(int, m_iTeamNum, "DT_BaseEntity->m_iTeamNum")
	NETVAR(float, m_flSimulationTime, "DT_BaseEntity->m_flSimulationTime")
	NETVAR_OFFSET(float, get_old_simulation_time, "DT_BaseEntity->m_flSimulationTime", 0x4)

	inline bool is_player()
	{
		return utils::get_virtual<bool(__thiscall*)(void*)>(this, 157)(this);
	}

	player_info get_info();
	std::optional<vector> get_bone_position(int bone);
};

class base_attributable_item : public base_entity 
{
public:
	NETVAR(short, m_iItemDefinitionIndex, "DT_BaseAttributableItem->m_iItemDefinitionIndex")
	NETVAR(int, m_iAccountID, "DT_BaseAttributableItem->m_iAccountID")
	NETVAR(int, m_iEntityQuality, "DT_BaseAttributableItem->m_iEntityQuality")
	NETVAR(int, m_iItemIDHigh, "DT_BaseAttributableItem->m_iItemIDHigh")
	NETVAR(int, m_iItemIDLow, "DT_BaseAttributableItem->m_iItemIDLow")
	NETVAR(int, m_nFallbackPaintKit, "DT_BaseAttributableItem->m_nFallbackPaintKit")
	NETVAR(int, m_nFallbackSeed, "DT_BaseAttributableItem->m_nFallbackSeed")
	NETVAR(float, m_flFallbackWear, "DT_BaseAttributableItem->m_flFallbackWear")
	NETVAR(float, m_nFallbackStatTrak, "DT_BaseAttributableItem->m_nFallbackStatTrak")
};

class base_combat_character : public base_entity 
{
public:
	PNETVAR(base_handle, m_hMyWeapons, "DT_BaseCombatCharacter->m_hMyWeapons")
	PNETVAR(base_handle, m_hMyWearables, "DT_BaseCombatCharacter->m_hMyWearables")
	NETVAR(base_handle, m_hActiveWeapon, "DT_BaseCombatCharacter->m_hActiveWeapon")
};

class base_player : public base_combat_character
{
public:
	NETVAR(uint32_t, m_fFlags, "DT_BasePlayer->m_fFlags")
	NETVAR(int, m_iHealth, "DT_BasePlayer->m_iHealth")
	NETVAR(vector, m_vecVelocity, "DT_BasePlayer->m_vecVelocity[0]")
	NETVAR(uint32_t, m_nTickBase, "DT_BasePlayer->m_nTickBase")
	NETVAR(vector, m_vecViewOffset, "DT_BasePlayer->m_vecViewOffset[0]")
	NETVAR(bool, m_bIsScoped, "DT_CSPlayer->m_bIsScoped")

	inline bool is_alive() { return m_iHealth() > 0; }
	inline vector get_eye_position() { return m_vecOrigin() + m_vecViewOffset(); }
};

class base_animating : public base_player
{
public:
	NETVAR(bool, m_bClientSideAnimation, "DT_BaseAnimating->m_bClientSideAnimation")

	OFFSET(get_animation_layers(), anim_layer*, 0x2980)
	OFFSET(get_animation_state(), anim_state*, 0x3914)
};