#pragma once
#include "../../common.h"
#include "../datatypes/client_class.h"

namespace netvars 
{
	bool setup();
	void store(std::string_view name, recv_table* table, std::size_t offset = 0);

	inline std::unordered_map<std::size_t, std::size_t> m_offsets;
	inline std::ofstream m_file;
};

#define NETVAR( type, func, string ) [[nodiscard]] type& func() \
{\
	static auto offset = netvars::m_offsets[ fnv1a::hash_rt( string ) ];\
    return *reinterpret_cast<type*>(reinterpret_cast<std::size_t>(this) + offset);\
}

#define PNETVAR( type, func, string ) [[nodiscard]] type* func() \
{\
	static auto offset = netvars::m_offsets[ fnv1a::hash_rt( string ) ];\
    return reinterpret_cast<type*>(reinterpret_cast<std::size_t>(this) + offset);\
}

#define NETVAR_OFFSET( type, func, string, add ) [[nodiscard]] type& func() \
{\
	static auto offset = netvars::m_offsets[ fnv1a::hash_rt( string ) ];\
    return *reinterpret_cast<type*>(reinterpret_cast<std::size_t>(this) + offset + add);\
}