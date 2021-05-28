#pragma once
#include "../../common.h"
#include "../matrix.h"
#include "net_channel.h"

struct player_info
{
	char _pad0;
	union
	{
		int64_t m_xuid;
		struct
		{
			int m_xuidlow;
			int m_xuidhigh;
		};
	};
	char m_name[128];
	int m_userid;
	char m_guid[33];
	unsigned int m_friendsid;
	char m_friendsname[128];
	bool m_fakeplayer;
	bool m_ishltv;
	unsigned int m_customfiles[4];
	unsigned char m_filesdownloaded;
};

class engine_client
{
public:
	void get_screen_size(int& width, int& height)
	{
		utils::get_virtual<void(__thiscall*)(void*, int&, int&)>(this, 5)(this, width, height);
	}

	bool get_player_info(int entity_index, player_info* info)
	{
		return utils::get_virtual<bool(__thiscall*)(void*, int, player_info*)>(this, 8)(this, entity_index, info);
	}
	
	int get_local_player()
	{
		return utils::get_virtual<int(__thiscall*)(void*)>(this, 12)(this);
	}

	void get_view_angles(qangle& view_angles)
	{
		return utils::get_virtual<void(__thiscall*)(void*, qangle&)>(this, 18)(this, view_angles);
	}

	void set_view_angles(qangle& view_angles)
	{
		return utils::get_virtual<void(__thiscall*)(void*, qangle&)>(this, 19)(this, view_angles);
	}

	view_matrix& world_to_screen_matrix()
	{
		return utils::get_virtual<view_matrix&(__thiscall*)(void*)>(this, 37)(this);
	}

	net_channel_info* get_net_channel_info()
	{
		return utils::get_virtual<net_channel_info*(__thiscall*)(void*)>(this, 78)(this);
	}

	void execute_client_cmd(const char* cmd_string)
	{
		return utils::get_virtual<void(__thiscall*)(void*, const char*)>(this, 108)(this, cmd_string);
	}
};