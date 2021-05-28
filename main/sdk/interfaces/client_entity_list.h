#pragma once
#include "../client_entity.h"

class client_entity_list {
public:
	virtual client_networkable*		get_client_networkable(int index) = 0;
	virtual client_networkable*		get_client_networkable_handle(base_handle handle) = 0;
	virtual client_unknown*			get_client_unknown_handle(base_handle handle) = 0;
	virtual client_entity*			get_client_entity(int index) = 0;
	virtual client_entity*		 	get_client_entity_from_handle(base_handle handle) = 0;
	virtual int					  	number_of_entities(bool include_non_networkable) = 0;
	virtual int						get_highest_entity_index() = 0;
	virtual void					set_max_entities(int max_ents) = 0;
	virtual int						get_max_entities() = 0;
};