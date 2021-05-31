#pragma once
#include "../../utils/utils.h"
#include "../definitions.h"
#include "../qangle.h"
#include "../matrix.h"
#include "../datatypes/material.h"

class studiohdr;
struct studiohwdata;
class client_renderable;
class key_values;

struct model
{
	char			_pad0[4];
	char			m_name[260];
	int				m_load_flags;
	int				m_server_count;
	int				m_type;
	int				m_flags;
	vector			m_mins;
	vector		    m_maxs;
	float			m_radius;
	key_values*     m_key_values;
	char			_pad1[24];
};

struct model_render_info 
{
	vector					 m_origin;
	qangle					 m_angles;
	char					 _pad[4];
	client_renderable*		 m_renderable;
	const model*			 m_model;
	const matrix3x4_t*	     m_model_to_world;
	const matrix3x4_t*		 m_lighting_offset;
	const vector*			 m_lighting_origin;
	uint32_t           	     m_flags;
	int						 m_index;
	int					 	 m_skin;
	int					 	 m_body;
	int						 m_hitboxset;
	uint16_t			     m_instance;
};

struct draw_model_state 
{
	studiohdr*			 m_studio_hdr;
	studiohwdata*		 m_studio_hw_data;
	client_renderable*	 m_renderable;
	const matrix3x4_t*   m_bones;
};

class model_render 
{
public:
	void forced_material_override(material* mat, override_type type = override_type::OVERRIDE_NORMAL, int overrides = 0)
	{
		return utils::get_virtual<void(__thiscall*)(void*, material*, override_type, int)>(this, 1)(this, mat, type, overrides);
	}

	bool is_forced_material_override()
	{
		return utils::get_virtual<bool(__thiscall*)(void*)>(this, 2)(this);
	}
};