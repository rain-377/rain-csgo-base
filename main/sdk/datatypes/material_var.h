#pragma once
#include "../../utils/utils.h"
#include "../vector.h"

class material_var {
public:
	void set_value(float value)
	{
		utils::get_virtual<void(__thiscall*)(void*, float)>(this, 4)(this, value);
	}

	void set_value(int value)
	{
		utils::get_virtual<void(__thiscall*)(void*, int)>(this, 5)(this, value);
	}
	void set_value(const char* value)
	{
		utils::get_virtual<void(__thiscall*)(void*, const char*)>(this, 6)(this, value);
	}

	void set_value(const vector& value)
	{
		utils::get_virtual<void(__thiscall*)(void*, float, float, float)>(this, 11)(this, value.x, value.y, value.z);
	}
};