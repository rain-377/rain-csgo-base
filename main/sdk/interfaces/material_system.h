#pragma once
#include "../../utils/utils.h"
#include "../datatypes/material.h"

class key_values;
using material_handle = uint16_t;

class material_system 
{
public:
	material* find_material(const char* name, const char* group, bool complain = true, const char* complain_prefix = nullptr)
	{
		return utils::get_virtual<material*(__thiscall*)(void*, const char*, const char*, bool, const char*)>(this, 84)(this, name, group, complain, complain_prefix);
	}

	material_handle first_material()
	{
		return utils::get_virtual<material_handle(__thiscall*)(void*)>(this, 86)(this);
	}

	material_handle next_material(material_handle handle)
	{
		return utils::get_virtual<uint16_t(__thiscall*)(void*, material_handle handle)>(this, 87)(this, handle);
	}

	material_handle invalid_material()
	{
		return utils::get_virtual<material_handle(__thiscall*)(void*)>(this, 88)(this);
	}

	material* get_material(material_handle handle)
	{
		return utils::get_virtual<material*(__thiscall*)(void*, material_handle handle)>(this, 89)(this, handle);
	}

	int get_num_materials(material_handle handle)
	{
		return utils::get_virtual<int(__thiscall*)(void*)>(this, 90)(this);
	}
};