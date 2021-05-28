#pragma once
#include "../common.h"

namespace config 
{
	struct item
	{
		template<typename T>
		T& get() { return *reinterpret_cast<T*>(std::any_cast<T>(&m_var)); }

		template<typename T>
		void set(T val) { m_var.emplace<T>(val); }

		uint32_t m_type;

		std::any m_var;
	};

	bool setup();

	void save();

	void load();

	extern std::string m_name;
	extern std::string m_folder;

	extern std::unordered_map<uint32_t, item> m_items;

	template<typename T>
	T& get(uint32_t hash) 
	{ 
		return m_items.at(hash).get<T>(); 
	}
}

#define ADD_ITEM(type, name, def) m_items[fnv1a::hash_ct(name)] = { fnv1a::hash_ct(#type), std::make_any<type>(def) };
#define ADD_ITEM_FLOAT_VEC(name, ...) m_items[fnv1a::hash_ct(name)] = { fnv1a::hash_ct("std::vector<float>"), std::make_any<std::vector<float>>({ __VA_ARGS__ }) };
#define ADD_ITEM_INT_VEC(name, ...) m_items[fnv1a::hash_ct(name)] = { fnv1a::hash_ct("std::vector<int>"), std::make_any<std::vector<int>>({ __VA_ARGS__ }) };
#define ADD_ITEM_BOOL_VEC(name, ...) m_items[fnv1a::hash_ct(name)] = { fnv1a::hash_ct("std::vector<bool>"), std::make_any<std::vector<bool>>({ __VA_ARGS__ }) };