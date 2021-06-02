#pragma once
#include "../studio.h"

class model_info {
public:
	model* get_model(int index)
	{
		return utils::get_virtual<model*(__thiscall*)(void*, int)>(this, 1)(this, index);
	}

	int get_model_index(const char* name)
	{
		return utils::get_virtual<int(__thiscall*)(void*, const char*)>(this, 2)(this, name);
	}

	const char* get_model_name(const model_t* model)
	{
		return utils::get_virtual<const char*(__thiscall*)(void*, const model_t*)>(this, 3)(this, model);
	}

	studiohdr_t* get_studio_model(const model_t* model)
	{
		return utils::get_virtual<studiohdr_t*(__thiscall*)(void*, const model_t*)>(this, 32)(this, model);
	}

	void set_view_angles(qangle& view_angles)
	{
		return utils::get_virtual<void(__thiscall*)(void*, qangle&)>(this, 19)(this, view_angles);
	}
};