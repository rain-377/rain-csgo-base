#pragma once
#include "../../utils/utils.h"

class cs_weapon_data
{
public:
	char		_pad0[0x14];				    // 0x0000
	int			m_max_clip1;				    // 0x0014
	int			m_max_clip2;				    // 0x0018
	int			m_default_clip1;		    	// 0x001C
	int			m_default_clip2;			    // 0x0020
	int			m_primary_reserve_ammo_max;	    // 0x0024
	int			m_secondary_reserve_ammo_max;   // 0x0028
	char*		m_world_model;					// 0x002C
	char*		m_view_model;					// 0x0030
	char*		m_dropped_model;				// 0x0034
	char	    _pad1[0x50];					// 0x0038
	char*		m_hud_name;						// 0x0088
	char*		m_weapon_name;					// 0x008C
	char		_pad2[0x2];						// 0x0090
	bool		m_is_melee_weapon;				// 0x0092
	char		_pad3[0x9];						// 0x0093
	float		m_weapon_weight;				// 0x009C
	char		_pad4[0x28];					// 0x00A0
	int			m_weapon_type;					// 0x00C8
	char		_pad5[0x4];						// 0x00CC
	int			m_weapon_price;					// 0x00D0
	int			m_kill_award;					// 0x00D4
	char		_pad6[0x4];						// 0x00D8
	float		m_cycle_time;					// 0x00DC
	float		m_cycle_time_alt;				// 0x00E0
	char		_pad7[0x8];						// 0x00E4
	bool		m_full_auto;					// 0x00EC
	char		_pad8[0x3];						// 0x00ED
	int			m_damage;						// 0x00F0
	float		m_armor_ratio;					// 0x00F4
	int			m_bullets;						// 0x00F8
	float		m_penetration;					// 0x00FC
	char		_pad9[0x8];						// 0x0100
	float		m_range;						// 0x0108
	float		m_range_modifier;				// 0x010C
	float		m_throw_velocity;				// 0x0110
	char		_pad10[0xC];					// 0x0114
	bool		m_has_silencer;					// 0x0120
	char		_pad11[0xB];					// 0x0121
	char*		m_bullet_type;					// 0x012C
	float		m_max_speed;					// 0x0130
	float		m_max_speed_alt;				// 0x0134
	float		m_spread;						// 0x0138
	float		m_spread_alt;					// 0x013C
	char		_pad12[0x44];					// 0x0180
	int			m_recoil_seed;					// 0x0184
	char		_pad13[0x20];					// 0x0188
};

class weapon_system
{
public:
	cs_weapon_data* get_weapon_data(short item_definition_index)
	{
		return utils::get_virtual<cs_weapon_data*(__thiscall*)(void*, short)>(this, 2)(this, item_definition_index);
	}
};