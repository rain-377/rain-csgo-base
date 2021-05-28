#pragma once
#include "../../common.h"

class surface
{
public:
	inline void unlock_cursor()
	{
		return utils::get_virtual<void(__thiscall*)(void*)>(this, 66)(this);
	}

	inline void lock_cursor()
	{
		return utils::get_virtual<void(__thiscall*)(void*)>(this, 67)(this);
	}
};