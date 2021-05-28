#pragma once
#include "../../common.h"
#include "../qangle.h"

class prediction
{
public:
	inline void set_local_view_angles(const qangle& view_angles)
	{
		return utils::get_virtual<void(__thiscall*)(void*, const qangle&)>(this, 13)(this, view_angles);
	}
};