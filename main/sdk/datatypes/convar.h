#pragma once

#include "../../common.h"
#include "../datatypes/utlvector.h"
#include "../vector.h"

using change_callback0 = void(__cdecl*)();
using change_callback1 = void(__cdecl*)(void*, const char*, float);

class convar
{
public:
	const char* get_name()
	{
		return utils::get_virtual<const char* (__thiscall*)(void*)>(this, 5)(this);
	}

	float get_float()
	{
		uint32_t xored = *reinterpret_cast<uint32_t*>(&m_parent->m_float_value) ^ reinterpret_cast<uint32_t>(this);
		return *reinterpret_cast<float*>(&xored);
	}

	int get_int()
	{
		return static_cast<int>(m_parent->m_int_value ^ reinterpret_cast<int>(this));
	}

	bool get_bool() // idx @ 13
	{
		return !!get_int();
	}

	const char* get_string() const
	{
		char const* szValue = m_parent->m_string;
		return szValue ? szValue : "";
	}

	void set_value(const char* value)
	{
		return utils::get_virtual<void(__thiscall*)(void*, const char*)>(this, 14)(this, value);
	}

	void set_value(float value)
	{
		return utils::get_virtual<void(__thiscall*)(void*, float)>(this, 15)(this, value);
	}

	void set_value(int value)
	{
		return utils::get_virtual<void(__thiscall*)(void*, int)>(this, 16)(this, value);
	}

	void set_value(vector value)
	{
		return utils::get_virtual<void(__thiscall*)(void*, vector)>(this, 17)(this, value);
	}

	char								_pad0[4];
	convar*								m_next;
	int									m_registered;
	char*								m_name;
	char*								m_help_string;
	uint32_t							m_flags;
	change_callback0					m_callback;
	convar*								m_parent;
	char*								m_default_value;
	char*								m_string;
	int									m_string_length;
	float								m_float_value;
	int									m_int_value;
	int									m_has_min;
	float								m_min_value;
	int									m_has_max;
	float								m_max_value;
	utl_vector<change_callback1>		m_callbacks;
};