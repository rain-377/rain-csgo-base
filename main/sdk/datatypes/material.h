#pragma once
#include "material_var.h"

class material 
{
public:
	virtual const char* get_name() const = 0;
	virtual const char* get_texture_group_name() const = 0;

	material_var* find_var(const char* name, bool* found, bool complain = true)
	{
		return utils::get_virtual<material_var*(__thiscall*)(void*, const char*, bool*, bool)>(this, 11)(this, name, found, complain);
	}

	void alpha_modulate(float alpha)
	{
		utils::get_virtual<void(__thiscall*)(void*, float)>(this, 27)(this, alpha);
	}

	void alpha_modulate(float red, float green, float blue)
	{
		utils::get_virtual<void(__thiscall*)(void*, float, float, float)>(this, 28)(this, red, green, blue);
	}

	void set_flag(int flag, bool value)
	{
		utils::get_virtual<void(__thiscall*)(void*, int, bool)>(this, 29)(this, flag, value);
	}

	bool is_error_material()
	{
		return utils::get_virtual<bool(__thiscall*)(void*)>(this, 42)(this);
	}
};