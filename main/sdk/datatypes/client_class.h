#pragma once
#include "recv.h"

using create_client_class = void* ( __cdecl* )(int index, int serial);
using create_event = void* ( __cdecl* )( );

struct client_class 
{
	create_client_class create_fn;
	create_event create_event; 
	char* network_name;
	recv_table* recv_table;
	client_class* next;
	int class_id;
};