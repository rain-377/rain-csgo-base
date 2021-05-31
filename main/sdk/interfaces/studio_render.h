#pragma once
#include "../../utils/utils.h"
#include "../definitions.h"
#include "../datatypes/material.h"

class studio_render
{
public:
	void set_color_modulation(const float* color)
	{
		return utils::get_virtual<void(__thiscall*)(void*, const float*)>(this, 27)(this, color);
	}

	void set_alpha_modulation(float alpha)
	{
		return utils::get_virtual<void(__thiscall*)(void*, float)>(this, 28)(this, alpha);
	}

	void forced_material_override(material* mat, override_type type = override_type::OVERRIDE_NORMAL, int overrides = 0)
	{
		return utils::get_virtual<void(__thiscall*)(void*, material*, override_type, int)>(this, 33)(this, mat, type, overrides);
	}
};