#pragma once
#include "../common.h"
#include "vector.h"
#include "qangle.h"

class base_combat_weapon;
class base_entity;
class base_animating;
class studio_hdr;

struct anim_layer
{
	float			m_anim_time;
	float			m_fade_out_time;
	studio_hdr*     m_studio_hdr;
	int				m_dispatched_src;
	int				m_dispatched_dst;
	int				m_order;
	int				m_sequence;
	float			m_prev_cycle;
	float			m_weight;
	float			m_weight_delta_rate;
	float			m_playback_rate;
	float			m_cycle;
	base_entity*    m_owner;
	int				m_invalidate_physics_bits;
};

using anim_layer_array = std::array <anim_layer, 15u>;

class anim_state 
{
public:
	__forceinline void update(qangle angle)
	{
		using update_animation_state_fn = void(__vectorcall*)(void*, void*, float, float, float, void*);
		static auto update = reinterpret_cast<update_animation_state_fn>(utils::find_signature("client.dll", "55 8B EC 83 E4 F8 83 EC 18 56 57 8B F9 F3 0F 11 54 24"));
		if (!update)
			return;

		update(this, nullptr, 0.f, angle.y, angle.x, nullptr);
	}

	char					_pad0[4];
	bool					m_reset;
	char					_pad1[3];
	int						m_tick_count;
	char					_pad2[84];
	base_animating*			m_base_entity;
	base_combat_weapon*		m_active_weapon;
	base_combat_weapon*		m_last_active_weapon;
	float					m_last_cur_time;
	int						m_last_frame_count;
	float					m_delta_time;
	float					m_eye_yaw;
	float					m_eye_pitch;
	float					m_foot_yaw;
	float					m_last_foot_yaw;
	float					m_move_yaw;
	float					m_move_yaw_ideal;
	float					m_move_yaw_cur_to_ideal;
	char					_pad3[4];
	float					m_feet_cycle;
	float					m_feet_weight;
	char					_pad4[4];
	float					m_duck_amount;
	float					m_duck_additional;
	char					_pad5[4];
	vector					m_origin;
	vector					m_last_origin;
	vector					m_velocity;
	vector					m_velocity_normalized;
	vector					m_velocity_normalized_non_zero;
	float					m_speed_2d;
	float					m_up_velocity;
	float					m_speed_as_portion_of_run_speed;
	float					m_speed_as_portion_of_walk_speed;
	float					m_speed_as_portion_of_crouch_speed;
	float					m_time_since_started_moving;
	float					m_time_since_stopped_moving;
	bool					m_on_ground;
	bool					m_landing;
	char					_pad6[6];
	float					m_time_since_in_air;
	float					m_left_ground_height;
	float					m_land_anim_multiplier;
	float					m_walk_to_run_transition;
	char					_pad7[4];
	float					m_in_air_smooth_value;
	bool					m_on_ladder;
	char					_pad8[47];
	float					m_last_velocity_test_time;
	vector					m_last_velocity;
	vector					m_dst_acceleration;
	vector					m_acceleration;
	float					m_acceleration_weight;
	char					_pad9[12];
	float					m_strafe_weight;
	char					_pad10[4];
	float					m_strafe_cycle;
	int						m_strafe_sequence;
	char					_pad11[388];
	float					m_adjusted_eye_pos_height;
	bool					m_should_adjust_eye_pos_height;
	char					_pad12[7];
	float					m_min_body_yaw;
	float					m_max_body_yaw;
	float					m_min_body_pitch;
	float					m_max_body_pitch;
	int						m_anim_set_version;
};
