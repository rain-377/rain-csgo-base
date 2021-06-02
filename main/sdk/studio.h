#pragma once
#include "vector.h"
#include "qangle.h"
#include "matrix.h"
#include "datatypes/utlvector.h"

#define MAXSTUDIOBONECTRLS			4
#define MAXSTUDIOPOSEPARAM			24
#define MAXSTUDIOSKINS				32		// total textures
#define MAXSTUDIOFLEXCTRL			96		// maximum number of flexcontrollers (input sliders)
#define MAXSTUDIOBONES				256		// total bones actually used
#define MAXSTUDIOANIMBLOCKS			256
#define MAXSTUDIOFLEXDESC			1024	// maximum number of low level flexes (actual morph targets)

struct anim_tag 
{
	int		m_index;
	float	m_first_cycle;
	int		m_tag_string_offset_from_this;

	inline const char* get_name() { return reinterpret_cast<const char*>(this) + m_tag_string_offset_from_this; }
};

struct mstudiobbox 
{
	int         m_bone;
	int         m_group;
	vector      m_obb_min;
	vector      m_obb_max;
	int         m_hitbox_name_index;
	qangle		m_rotation;
	float       m_radius;
	char		_pad1[16];

	inline const char* get_name() const
	{
		if (!m_hitbox_name_index)
			return nullptr;

		return reinterpret_cast<const char*>(reinterpret_cast<const uint8_t*>(this) + m_hitbox_name_index);
	}
};

struct mstudiohitboxset
{
	int    m_name_index;
	int    m_hitboxes_count;
	int    m_hitbox_index;

	inline const char* get_name()
	{
		if (!m_name_index)
			return nullptr;

		return reinterpret_cast<const char*>(reinterpret_cast<uint8_t*>(this) + m_name_index);
	}

	inline const mstudiobbox* get_hitbox(int i) const
	{
		if (i > m_hitboxes_count)
			return nullptr;

		return reinterpret_cast<const mstudiobbox*>(reinterpret_cast<const uint8_t*>(this) + m_hitbox_index) + i;
	}
};

struct mstudiobone 
{
	int						m_name_index;
	int						m_parent;
	int						m_bone_controller[6];
	vector					m_pos;
	vector_4d				m_quat;
	vector					m_rot;

	vector					m_pos_scale;
	vector					m_rot_scale;

	matrix3x4_t				m_pose_to_bone;
	vector_4d				m_alignment;
	uint32_t				m_flags;
	int						m_proc_type;
	int						m_proc_index;
	mutable int				m_physics_bone;
	int						m_surface_prop_index;

	int						m_contents;
	int						m_surface_prop_lookup;
	char					_pad0[28];

	inline const char* get_name() const { return reinterpret_cast<const char*>(this) + m_name_index; }
	inline const void* get_procedure() const { return (m_proc_index == 0) ? nullptr : reinterpret_cast<const void*>(reinterpret_cast<const uint8_t*>(this) + m_proc_index); };
	inline const char* get_surface_prop_name() const { return reinterpret_cast<const char*>(this) + m_surface_prop_index; }
	inline int get_surface_prop() const { return m_surface_prop_lookup; }
};

struct mstudioposeparamdesc 
{
	int						m_name_index;
	uint32_t				m_flags;
	float					m_start;
	float					m_end;
	float					m_loop;

	inline const char* get_name() const 
	{
		return reinterpret_cast<const char*>(this) + m_name_index; 
	}
};

struct mstudioactivitymodifier
{
	int					m_name_index;

	inline const char* get_name() const { return m_name_index ? reinterpret_cast<const char*>(reinterpret_cast<const uint8_t*>(this) + m_name_index) : nullptr; }
};

struct mstudioseqdesc 
{
	char					_pad0[4];
	int						m_label_index;
	int						m_activity_name_index;
	uint32_t				m_flags;
	int						m_activity;
	int						m_activity_weight;
	int						m_events_count;
	int						m_event_index;
	vector					m_obb_min;
	vector					m_obb_max;
	int						m_blends_count;
	int						m_anim_index;
	int						m_movement_index;
	int						m_group_size[2];
	int						m_param_index[2];
	float					m_param_start[2];
	float					m_param_end[2];
	int						m_param_parent;
	float					m_fade_in_time;
	float					m_fade_out_time;
	int						m_local_entry_node;
	int						m_local_exit_node;
	uint32_t				m_node_flags;
	float					m_entry_phase;
	float					m_exit_phase;
	float					m_last_frame;
	int						m_next_seq;
	int						m_pose;
	int						m_ik_rules_count;
	int						m_auto_layers_count;
	int						m_auto_layer_index;
	int						m_weight_list_index;
	int						m_pose_key_index;
	int						m_ik_locks_count;
	int						m_ik_lock_index;
	int						m_key_value_index;
	int						m_key_value_size;
	int						m_cycle_pose_index;
	int						m_activity_modifier_index;
	int						m_activity_modifiers_count;
	int						m_anim_tag_index;
	int						m_anim_tags_count;
	char					_pad1[12];

	inline const anim_tag* get_anim_tag(int i) const 
	{ 
		return reinterpret_cast<const anim_tag*>(reinterpret_cast<const uint8_t*>(this) + m_anim_tag_index) + i; 
	}

	inline const mstudioactivitymodifier* get_activity_modifier(int i) const 
	{
		return m_activity_modifier_index != 0 ? reinterpret_cast<const mstudioactivitymodifier*>(reinterpret_cast<const uint8_t*>(this) + m_activity_modifier_index) + i : nullptr;
	}
};

class studiohdr_t 
{
public:
	int						m_id;
	int						m_version;
	long					m_checksum;
	char					m_name[64];
	int						m_length;
	vector					m_eye_pos;
	vector					m_illum_pos;
	vector					m_hull_min;
	vector					m_hull_max;
	vector					m_obb_min;
	vector					m_obb_max;
	uint32_t				m_flags;
	int						m_bones_count;
	int						m_bone_index;
	int						m_bone_controllers_count;
	int						m_bone_controller_index;
	int						m_hitbox_sets_count;
	int						m_hitbox_set_index;
	int						m_local_anim_count;
	int						m_local_anim_index;
	int						m_local_seq_count;
	int						m_local_seq_index;
	int						m_activity_list_version;
	int						m_events_indexed;
	int						m_textures_count;
	int						m_texture_index;
	int						m_cd_textures_count;
	int						m_cd_texture_index;
	int						m_skin_ref_count;
	int						m_skin_families_count;
	int						m_skin_index;
	int						m_body_parts_count;
	int						m_body_part_index;
	int						m_local_attachments_count;
	int						m_local_attachment_index;
	int						m_local_nodes_count;
	int						m_local_node_index;
	int						m_local_node_name_index;
	int						m_flex_desc_count;
	int						m_flex_desc_index;
	int						m_flex_controllers_count;
	int						m_flex_controller_index;
	int						m_flex_rules_count;
	int						m_flex_rule_index;
	int						m_ik_chains_count;
	int						m_ik_chain_index;
	int						m_mouths_count;
	int						m_mouth_index;
	int						m_local_pose_parameters_count;
	int						m_local_pose_param_index;
	int						m_surface_prop_index;
	int						m_key_value_index;
	int						m_key_value_size;
	int						m_local_ik_auto_play_locks_count;
	int						m_local_ik_auto_play_lock_index;
	float					m_mass;
	int						m_contents;
	int						m_include_models_count;
	int						m_include_model_index;
	mutable void* m_virtual_model;
	int						m_anim_block_name_index;
	int						m_anim_blocks_count;
	int						m_anim_block_index;
	mutable void* m_anim_block_model;
	int						m_bone_table_by_name_index;
	void* m_vertex_base;
	void* m_index_base;
	uint8_t					m_const_directional_light_dot;
	uint8_t					m_root_lod;
	uint8_t					m_allowed_root_lods_count;
	char					_pad0[5];
	int						m_flex_controller_ui_count;
	int						m_flex_controller_ui_index;
	float					m_vert_anim_fixed_point_scale;
	mutable int				m_surface_prop_lookup;
	int						m_studio_hdr_index;
	char					_pad1[4];

	inline const mstudiohitboxset* get_hitbox_set(int i) const 
	{
		return i <= m_hitbox_sets_count ? reinterpret_cast<const mstudiohitboxset*>(reinterpret_cast<const uint8_t*>(this) + m_hitbox_set_index) + i : nullptr;
	}

	inline const mstudiobone* get_bone(int i) const 
	{
		return i <= m_bones_count ? reinterpret_cast<const mstudiobone*>(reinterpret_cast<const uint8_t*>(this) + m_bone_index) + i : nullptr;
	}

	inline const mstudioseqdesc* get_local_seqdesc(int i) const
	{
		if (i < 0
			|| i >= m_local_seq_count) {
			i = 0;
		}

		return reinterpret_cast<const mstudioseqdesc*>(reinterpret_cast<const uint8_t*>(this) + sizeof(mstudioseqdesc) * i + m_local_seq_index);
	};

	inline const mstudioposeparamdesc* get_local_pose_parameter(int i) const 
	{
		return reinterpret_cast<const mstudioposeparamdesc*>(reinterpret_cast<const uint8_t*>(this) + m_local_pose_param_index) + i;
	}
};

class virtualgroup 
{
public:
	inline studiohdr_t* get_studio_hdr() const { return reinterpret_cast<studiohdr_t*>(m_cache); }

	void* m_cache;
	utl_vector<int>	m_bone_map;
	utl_vector<int>	m_master_bone;
	utl_vector<int>	m_master_seq;
	utl_vector<int>	m_master_anim;
	utl_vector<int>	m_master_attachment;
	utl_vector<int>	m_master_pose;
	utl_vector<int>	m_master_node;
};

struct virtualsequence 
{
	uint32_t				m_flags;
	int						m_activity;
	int						m_group;
	int						m_index;
};

struct virtualgeneric
{
	int m_group;
	int m_index;
};

struct virtualmodel 
{
	char							_pad0[8];
	utl_vector<virtualsequence>		m_seq;
	utl_vector<virtualgeneric>		m_anim;
	utl_vector<virtualgeneric>		m_attachment;
	utl_vector<virtualgeneric>		m_pose;
	utl_vector<virtualgroup>		m_group;
	utl_vector<virtualgeneric>		m_node;
	utl_vector<virtualgeneric>		m_ik_lock;
	utl_vector<uint16_t>			m_auto_play_sequences;
};

class c_studio_hdr;

class c_studio_hdr 
{
public:
	mutable studiohdr_t*					m_studio_hdr;
	mutable virtualmodel*					m_v_model;
	char									_pad0[4];
	mutable utl_vector<const studiohdr_t*>	m_studio_hdr_cache;
	mutable int								m_frame_unlock_count;
	int*									m_frame_unlock_counter;
	char									_pad1[8];
	utl_vector<uint32_t>					m_bone_flags;
	utl_vector<int>							m_bone_parent;
	void*									m_activity_to_sequence;


	inline int get_pose_params_count() const { return m_v_model ? m_v_model->m_pose.size() : m_studio_hdr->m_local_pose_parameters_count; }
};