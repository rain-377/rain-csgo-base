#pragma once

#include "../../common.h"
#include "../datatypes/convar.h"

using create_interface_fn = uintptr_t*(__cdecl*)(const char* name, int* code);

class app_system 
{
public:
	virtual bool            connect(create_interface_fn factory) = 0;
	virtual void            disconnect() = 0;
	virtual void*			query_interface(const char* name) = 0;
	virtual int				init() = 0;
	virtual void            shutdown() = 0;
	virtual const void*		get_dependencies() = 0;
	virtual int				get_tier() = 0;
	virtual void            reconnect(create_interface_fn factory, const char* name) = 0;
};

class cvar_system : app_system
{
public:
	convar* find_var(const char* variable_name)
	{
		return utils::get_virtual<convar* (__thiscall*)(void*, const char*)>(this, 15)(this, variable_name);
	}
};