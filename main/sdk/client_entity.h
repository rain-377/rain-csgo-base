#pragma once
#include "collideable.h"
#include "qangle.h"
#include "vector.h"
#include "matrix.h"
#include "bitbuf.h"

using base_handle = unsigned int;
class model_t;
class client_unknown;

class handle_entity
{
public:
	virtual							~handle_entity() = default;
	virtual void					set_ref_handle(const base_handle& handle) = 0;
	virtual const base_handle&		get_handle() const = 0;
};

class client_thinkable 
{
public:
	virtual client_unknown*			get_client_unknown() = 0;
	virtual void					client_think() = 0;
	virtual void*					get_think_handle() = 0;
	virtual void					set_think_handle(void* think) = 0;
	virtual void					release() = 0;
};

class client_networkable
{
public:
	virtual client_unknown*		get_client_unknown() = 0;
	virtual void				release() = 0;
	virtual client_class*		get_client_class() = 0;
	virtual void				notify_should_transmit(int state) = 0;
	virtual void				on_pre_data_changed(int update_type) = 0;
	virtual void				on_data_changed(int update_type) = 0;
	virtual void				pre_data_update(int update_type) = 0;
	virtual void				post_data_update(int update_type) = 0;
	virtual void				unknown0() = 0;
	virtual bool				is_dormant() = 0;
	virtual int					get_index() const = 0;
	virtual void				receive_message(int class_id, bf_read& msg) = 0;
	virtual void*				get_data_table_base_ptr() = 0;
	virtual void				set_destroyed_on_recreate_entities() = 0;
};

class client_renderable 
{
public:
	virtual client_unknown*			get_client_unknown() = 0;
	virtual vector					const& get_render_origin() = 0;
	virtual qangle					const& get_render_angles() = 0;
	virtual bool					should_draw() = 0;
	virtual int						get_render_flags() = 0;
	virtual void					unknown0() const = 0;
	virtual uint16_t				get_shadow_handle() const = 0;
	virtual uint16_t&				 get_render_handle() = 0;
	virtual const					model_t* get_model() const = 0;
	virtual int						draw_model(int flags, uint8_t alpha) = 0;
	virtual int						get_body() = 0;
	virtual void					get_color_modulation(float* color) = 0;
	virtual bool					lod_test() = 0;
	virtual bool					setup_bones(matrix3x4_t* bones, int max, int mask, float time) = 0;
	virtual void					setup_weights(const matrix3x4_t* bones, int count, float* weights, float* delayed_weights) = 0;
	virtual void					do_animation_events() = 0;
	virtual void*					get_pvs_notify_interface() = 0;
	virtual void					get_render_bounds(vector& mins, vector& maxs) = 0;
	virtual void					get_render_bounds_worldspace(vector& mins, vector& maxs) = 0;
	virtual void					get_shadow_render_bounds(vector& mins, vector& maxs, int type) = 0;
	virtual bool					should_receive_projected_textures(int flags) = 0;
	virtual bool					get_shadow_cast_distance(float* dist, int type) const = 0;
	virtual bool					get_shadow_cast_direction(vector* direction, int type) const = 0;
	virtual bool					is_shadow_dirty() = 0;
	virtual void					mark_shadow_dirty(bool dirty) = 0;
	virtual client_renderable*		get_shadow_parent() = 0;
	virtual client_renderable*		first_shadow_child() = 0;
	virtual client_renderable*		next_shadow_peer() = 0;
	virtual int						shadow_cast_type() = 0;
	virtual void					create_model_instance() = 0;
	virtual uint16_t				get_model_instance() = 0;
	virtual const					matrix3x4_t& renderable_to_world_transform() = 0;
	virtual int						lookup_attachment(const char* name) = 0;
	virtual bool					get_attachment(int index, vector& origin, vector& angles) = 0;
	virtual bool					get_attachment(int index, matrix3x4_t& matrix) = 0;
	virtual float*					get_render_clip_plane() = 0;
	virtual int						get_skin() = 0;
	virtual void					on_threaded_draw_setup() = 0;
	virtual bool					uses_flex_delayed_weights() = 0;
	virtual void					record_tool_message() = 0;
	virtual bool					should_draw_for_split_screen_user(int slot) = 0;
	virtual uint8_t					override_alpha_modulation(uint8_t alpha) = 0;
	virtual uint8_t					override_shadow_alpha_modulation(uint8_t alpha) = 0;
};

class base_entity;
class client_entity;
class client_alpha_property;

class client_unknown : public handle_entity 
{
public:
	virtual collideable* get_collideable() = 0;
	virtual client_networkable* get_client_networkable() = 0;
	virtual client_renderable* get_client_renderable() = 0;
	virtual client_entity* get_client_entity() = 0;
	virtual base_entity* get_base_entity() = 0;
	virtual client_thinkable* get_client_thinkable() = 0;
	virtual client_alpha_property* get_client_alpha_property() = 0;
};

class client_entity : public client_unknown, public client_renderable, public client_networkable, public client_thinkable 
{
public:
	virtual const vector& get_abs_origin() const = 0;
	virtual const qangle& get_abs_angles() const = 0;
};