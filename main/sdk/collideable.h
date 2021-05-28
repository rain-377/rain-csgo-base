#pragma once
#include "../common.h"
#include "vector.h"

class collideable
{
public:
	inline vector& get_obb_mins()
	{
		return utils::get_virtual<vector&(__thiscall*)(void*)>(this, 1)(this);
	}

	inline vector get_obb_maxs()
	{
		return utils::get_virtual<vector&(__thiscall*)(void*)>(this, 2)(this);
	}
};