#pragma once
#include "../../common.h"
#include "../datatypes/client_class.h"
#include "../datatypes/datamap.h"

namespace netvars 
{
	bool setup();
	void store(std::string_view name, recv_table* table, std::size_t offset = 0);

	uintptr_t find_in_data_map(data_map* map, const uint32_t field_name);

	inline std::unordered_map<std::size_t, std::size_t> m_offsets;
	inline std::ofstream m_file;
};

#define NETVAR( type, func, string ) [[nodiscard]] type& func() \
{\
	static auto offset = netvars::m_offsets[ fnv1a::hash_ct( string ) ];\
    return *reinterpret_cast<type*>(reinterpret_cast<std::size_t>(this) + offset);\
}

#define PNETVAR( type, func, string ) [[nodiscard]] type* func() \
{\
	static auto offset = netvars::m_offsets[ fnv1a::hash_ct( string ) ];\
    return reinterpret_cast<type*>(reinterpret_cast<std::size_t>(this) + offset);\
}

#define NETVAR_OFFSET( type, func, string, add ) [[nodiscard]] type& func() \
{\
	static auto offset = netvars::m_offsets[ fnv1a::hash_ct( string ) ];\
    return *reinterpret_cast<type*>(reinterpret_cast<std::size_t>(this) + offset + add);\
}

#define DATAFIELD( type, func, map, data_field ) [[nodiscard]] type& func() \
{\
	static constexpr uint32_t hash = fnv1a::hash_ct(data_field);\
	static auto offset = netvars::find_in_data_map(map, hash);\
    return *reinterpret_cast<type*>(reinterpret_cast<std::size_t>(this) + offset);\
}

#define PDATAFIELD( type, func, map, data_field ) [[nodiscard]] type* func() \
{\
	static constexpr uint32_t hash = fnv1a::hash_ct(data_field);\
	static auto offset = netvars::find_in_data_map(map, hash);\
    return reinterpret_cast<type*>(reinterpret_cast<std::size_t>(this) + offset);\
}