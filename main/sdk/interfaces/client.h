#pragma once
#include "../../common.h"
#include "../datatypes/client_class.h"

enum client_frame_stage 
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};

class client
{
public:
	inline client_class* get_all_classes()
	{
		return utils::get_virtual<client_class*(__thiscall*)(void*)>(this, 8)(this);
	}

	inline bool dispatch_user_message(int message_type, int arg, int arg1, void* data)
	{
		return utils::get_virtual<bool(__thiscall*)(void*, int, int, int, void*)>(this, 38)(this, message_type, arg, arg1, data);
	}
};