#include "netvars.h"
#include "../../core/interfaces.h"

bool netvars::setup() 
{
	auto list = g_client->get_all_classes();

	if (!list)
		return false;

	m_file.open( "netvars.txt", std::ios::out | std::ios::trunc);

	while (list != nullptr) {

		store(list->recv_table->m_net_table_name, list->recv_table);

		list = list->next;
		
	}

	m_file.close( );

	return true;

}

void netvars::store(std::string_view name, recv_table* table, std::size_t offset) 
{
	for (auto i = 0; i < table->m_props; ++i) 
	{

		recv_prop* prop = &table->m_props_pointer[i];
		recv_table* child = prop->m_data_table;

		if (child && child->m_props > 0)
			store(name, child, prop->m_offset + offset);

		auto variable = prop->m_var_name;

		std::string netvar = std::string(name.data()) + "->" + variable;
		uint32_t hash = fnv1a::hash_rt(netvar.c_str());

		if (!m_offsets[hash]) {

			m_offsets[hash] = prop->m_offset + offset;

			m_file << netvar << " = 0x" << std::hex << m_offsets[hash] << std::endl;

		}

	}
}

uintptr_t netvars::find_in_data_map(data_map* map, const uint32_t field_name)
{
	while (map != nullptr)
	{
		for (int i = 0; i < map->m_data_fields; i++)
		{
			if (map->m_data_description[i].m_field_name == nullptr)
				continue;

			if (fnv1a::hash_ct(map->m_data_description[i].m_field_name) == field_name)
				return map->m_data_description[i].m_field_offset[TD_OFFSET_NORMAL];

			if (map->m_data_description[i].m_field_type == FIELD_EMBEDDED)
			{
				if (map->m_data_description[i].m_type_description != nullptr)
				{
					if (const auto offset = find_in_data_map(map->m_data_description[i].m_type_description, field_name); offset != 0u)
						return offset;
				}
			}
		}

		map = map->m_base_map;
	}

	return 0u;
}