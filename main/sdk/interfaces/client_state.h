#pragma once
#include "../../common.h"
#include "net_channel.h"
#include "../datatypes/client_class.h"
#include "../qangle.h"

class event_info
{
public:
	int				m_class_id;
	float			m_delay;
	char			_pad1[4];
	client_class*	m_client_class;
	char			_pad2[40];
	event_info*		m_next;
};

class client_state
{
public:
	char			_pad0[0x9C];			// 0x0000
	net_channel*	m_net_channel;			// 0x009C
	int				m_challenge_number;		// 0x00A0
	char			pad1[0x64];				// 0x00A4
	int				m_signon_state;			// 0x0108
	char			pad2[0x8];				// 0x010C
	float			m_next_cmd_time;		// 0x0114
	int				m_server_count;			// 0x0118
	int				m_current_sequence;		// 0x011C
	char			_pad3[0x54];			// 0x0120
	int				m_delta_tick;			// 0x0174
	bool			m_paused;				// 0x0178
	char			_pad4[0x7];				// 0x0179
	int				m_view_entity;			// 0x0180
	int				m_player_slot;			// 0x0184
	char			m_level_name[MAX_PATH];	// 0x0188
	char			m_level_name_short[80];	// 0x028C
	char			m_map_group_name[80];	// 0x02DC
	char			m_last_level_name_short[80]; // 0x032C
	char			_pad5[0xC];				// 0x037C
	int				m_max_clients;			// 0x0388 
	char			_pad6[0x498C];			// 0x038C
	float			m_last_server_tick_time; // 0x4D18
	bool			m_in_simulation;		// 0x4D1C
	char			_pad7[0x3];				// 0x4D1D
	int				m_old_tick_count;		// 0x4D20
	float			m_tick_remainder;		// 0x4D24
	float			m_frame_time;			// 0x4D28
	int				m_last_outgoing_command; // 0x4D2C
	int				m_choked_commands;		// 0x4D30
	int				m_last_command_ack;		// 0x4D34
	int				m_command_ack;			// 0x4D38
	int				m_sound_sequence;		// 0x4D3C
	char			_pad8[0x50];			// 0x4D40
	qangle			m_view_angles;			// 0x4D90
	char			_pad9[0xD0];			// 0x4D9C
	event_info*		m_events;				// 0x4E6C
}; // Size: 0x4E70