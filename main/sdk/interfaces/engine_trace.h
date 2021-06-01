#pragma once
#include "../vector.h"
#include "../matrix.h"
#include "../definitions.h"
#include "../client_entity.h"

struct surface_t 
{
	const char* m_name;
	short		m_surface_props;
	uint16_t	m_flags;
};

struct m_plane 
{
	vector		m_normal;
	float		m_distance;
	char		m_type;
	char		m_signbits;
	char		_pad0[2];
};

class i_trace_filter {
public:
	virtual bool should_hit_entity(handle_entity* handle, int mask) = 0;
	virtual e_trace_type get_trace_type() const = 0;
};

class c_trace_filter : public i_trace_filter 
{
public:
	c_trace_filter() = default;
	c_trace_filter(handle_entity* skip, e_trace_type type = TRACE_EVERYTHING) {
		m_skip = skip;
		m_type = type;
	}

	__forceinline bool should_hit_entity(handle_entity* handle, int mask) { return handle != m_skip; }

	__forceinline e_trace_type get_trace_type() const { return m_type; }

	handle_entity* m_skip = nullptr;
	e_trace_type     m_type = TRACE_EVERYTHING;
};

class trace_filter_skip_two_entities : public i_trace_filter 
{
public:
	trace_filter_skip_two_entities() = default;
	trace_filter_skip_two_entities(handle_entity* skip0, handle_entity* skip1) {
		m_skip0 = skip0;
		m_skip1 = skip1;
	}

	__forceinline bool should_hit_entity(handle_entity* handle, int mask) { return handle != m_skip0 && handle != m_skip1; }

	__forceinline e_trace_type get_trace_type() const { return TRACE_EVERYTHING; }

	handle_entity* m_skip0 = nullptr;
	handle_entity* m_skip1 = nullptr;
};

class trace_filter_world_only : public i_trace_filter 
{
public:
	__forceinline bool should_hit_entity(handle_entity* handle, int mask) { return false; }

	__forceinline e_trace_type get_trace_type() const { return TRACE_WORLD_ONLY; }
};

class trace_filter_world_and_props_only : public i_trace_filter 
{
public:
	__forceinline bool should_hit_entity(handle_entity* handle, int mask) { return false; }

	__forceinline e_trace_type get_trace_type() const { return TRACE_EVERYTHING; }
};

class trace_filter_no_players : public c_trace_filter 
{
public:
	__forceinline bool should_hit_entity(handle_entity* handle, int mask) override { return false; }
};

class trace_entity : public i_trace_filter 
{
public:
	trace_entity() = default;
	trace_entity(handle_entity* hit) { m_hit = hit; }

	__forceinline bool should_hit_entity(handle_entity* handle, int mask) { return handle == m_hit; }

	__forceinline e_trace_type get_trace_type() const { return TRACE_ENTITIES_ONLY; }

	handle_entity* m_hit = nullptr;
};

struct ray
{
	ray(const vector& start, const vector& end) :
		m_start(start), m_delta(end - start), m_world_axis_transform(nullptr), m_is_ray(true)
	{
		this->m_is_swept = (this->m_delta.length_sqr() != 0.f);
	}

	ray(const vector& start, const vector& end, const vector& mins, const vector& maxs)
	{
		this->m_delta = end - start;

		this->m_world_axis_transform = nullptr;
		this->m_is_swept = (this->m_delta.length_sqr() != 0.f);

		this->m_extents = maxs - mins;
		this->m_extents *= 0.5f;
		this->m_is_ray = (this->m_extents.length_sqr() < 1e-6);

		this->m_start_offset = mins + maxs;
		this->m_start_offset *= 0.5f;
		this->m_start = start + this->m_start_offset;
		this->m_start_offset *= -1.0f;
	}

	vector_aligned		m_start;
	vector_aligned		m_delta;
	vector_aligned		m_start_offset;
	vector_aligned		m_extents;
	const matrix3x4_t*  m_world_axis_transform;
	bool				m_is_ray;
	bool				m_is_swept;
};

class base_trace
{
public:
	base_trace() { }

	vector			m_start;		// start position
	vector			m_end;			// final position
	m_plane       	m_plane;		// surface normal at impact
	float			m_fraction;		// time completed, 1.0 = didn't hit anything
	int				m_contents;		// contents on other side of surface hit
	std::uint16_t	m_disp_flags;	// displacement flags for marking surfaces with data
	bool			m_all_solid;	// if true, m_plane is not valid
	bool			m_start_solid;	// if true, the initial point was in a solid area
};

class game_trace : public base_trace 
{
public:
	game_trace() : m_hit_entity(nullptr) { }

	float				m_fraction_left_solid;	// time we left a solid, only valid if we started in solid
	surface_t			m_surface;				// surface hit (impact surface)
	int					m_hitgroup;				// 0 == generic, non-zero is specific body part
	short				m_physics_bone;			// physics bone hit by trace in studio
	uint16_t			m_world_surface_index;	// index of the msurface2_t, if applicable
	client_entity*      m_hit_entity;			// entity hit by trace
	int					m_hitbox;				// box hit by trace in studio

	inline bool did_hit() const
	{
		return (m_fraction < 1.0f || m_all_solid || m_start_solid);
	}

	inline bool is_visible() const
	{
		return (m_fraction > 0.97f);
	}

private:
	game_trace(const game_trace& other)
	{
		this->m_start = other.m_start;
		this->m_end = other.m_end;
		this->m_plane = other.m_plane;
		this->m_fraction = other.m_fraction;
		this->m_contents = other.m_contents;
		this->m_disp_flags = other.m_disp_flags;
		this->m_all_solid = other.m_all_solid;
		this->m_start_solid = other.m_start_solid;
		this->m_fraction_left_solid = other.m_fraction_left_solid;
		this->m_surface = other.m_surface;
		this->m_hitgroup = other.m_hitgroup;
		this->m_physics_bone = other.m_physics_bone;
		this->m_world_surface_index = other.m_world_surface_index;
		this->m_hit_entity = other.m_hit_entity;
		this->m_hitbox = other.m_hitbox;
	}
};

class engine_trace 
{
public:
	virtual int	get_point_contents(const vector& pos, int mask = MASK_ALL, handle_entity** entity = 0) = 0;
	virtual int	get_point_contents_world_only(const vector& pos, int mask = MASK_ALL) = 0;
	virtual int	get_point_contents_collideable(collideable* collideable, const vector& pos) = 0;
	virtual void clip_ray_to_entity(const ray& ray, uint32_t mask, handle_entity* entity, game_trace* trace) = 0;
	virtual void clip_ray_to_collideable(const ray& ray, uint32_t mask, collideable* collideable, game_trace* trace) = 0;
	virtual void trace_ray(const ray& ray, uint32_t mask, i_trace_filter* filter, game_trace* trace) = 0;
};