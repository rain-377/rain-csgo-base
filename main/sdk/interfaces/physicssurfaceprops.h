#pragma once

struct surfacephysicsparams 
{
	float    m_friction;
	float    m_elasticity;
	float    m_density;
	float    m_thickness;
	float    m_dampening;
};

struct surfaceaudioparams 
{
	float    m_reflectivity;
	float    m_hardness_factor;
	float    m_roughness_factor;
	float    m_rough_threshold;
	float    m_hard_threshold;
	float    m_hard_velocity_threshold;
	float    m_high_pitch_occlusion;
	float    m_mid_pitch_occlusion;
	float    m_low_pitch_occlusion;
};

struct surfacesoundnames 
{
	uint16_t    m_walk_step_left;
	uint16_t    m_walk_step_right;
	uint16_t		m_run_step_left;
	uint16_t		m_run_step_right;
	uint16_t    m_impact_soft;
	uint16_t    m_impact_hard;
	uint16_t    m_scrape_smooth;
	uint16_t    m_scrape_rough;
	uint16_t    m_bullet_impact;
	uint16_t    m_rolling;
	uint16_t    m_break_sound;
	uint16_t    m_strain_sound;
};

struct surfacegameprops 
{
	float		m_max_speed_factor;
	float		m_jump_factor;
	float		m_penetration_modifier;
	float		m_damage_modifier;
	uint16_t	m_material;
	uint8_t	m_climbable;
};

struct surfacedata 
{
	surfacephysicsparams	m_physics;
	surfaceaudioparams	m_audio;
	surfacesoundnames		m_sounds;
	surfacegameprops		m_game;
	char					_pad[48];
};

class physics_surface_props {
public:
	virtual					~physics_surface_props() { }
	virtual int				parse_surface_data(const char* filename, const char* textfile) = 0;
	virtual int				surface_prop_count() const = 0;
	virtual int				get_surface_index(const char* name) const = 0;
	virtual void			get_physics_properties(int index, float* density, float* thickness, float* friction, float* elasticity) const = 0;
	virtual surfacedata*	get_surface_data(int index) = 0;
	virtual const char*		get_string(unsigned short index) const = 0;
	virtual const char*		get_prop_name(int index) const = 0;
	virtual void			set_world_material_index_table(int* map, int size) = 0;
	virtual void			get_physics_parameters(int index, surfacephysicsparams* out) const = 0;
};