#pragma once
#include "../bitbuf.h"

#define FLOW_OUTGOING	0		
#define FLOW_INCOMING	1
#define MAX_FLOWS		2

class net_channel_info
{
public:
	enum
	{
		GENERIC = 0,	// must be first and is default group
		LOCALPLAYER,	// bytes for local player entity update
		OTHERPLAYERS,	// bytes for other players update
		ENTITIES,		// all other entity bytes
		SOUNDS,			// game sounds
		EVENTS,			// event messages
		TEMPENTS,		// temp entities
		USERMESSAGES,	// user messages
		ENTMESSAGES,	// entity messages
		VOICE,			// voice data
		STRINGTABLE,	// a stringtable update
		MOVE,			// client move cmds
		STRINGCMD,		// string command
		SIGNON,			// various signondata
		PAINTMAP,		// paintmap data
		ENCRYPTED,		// encrypted data
		TOTAL,			// must be last and is not a real group
	};

	virtual const char* get_name(void) const = 0;	// get channel name
	virtual const char* get_address(void) const = 0; // get channel IP address as string
	virtual float		get_time(void) const = 0;	// current net time
	virtual float		get_time_connected(void) const = 0;	// get connection time in seconds
	virtual int			get_buffer_size(void) const = 0;	// netchannel packet history size
	virtual int			get_data_rate(void) const = 0; // send data rate in byte/sec

	virtual bool		is_loop_back(void) const = 0;	// true if loopback channel
	virtual bool		is_timing_out(void) const = 0;	// true if timing out
	virtual bool		is_play_back(void) const = 0;	// true if demo playback

	virtual float		get_latency(int flow) const = 0;	 // current latency (RTT), more accurate but jittering
	virtual float		get_average_latency(int flow) const = 0; // average packet latency in seconds
	virtual float		get_average_loss(int flow) const = 0;	 // avg packet loss[0..1]
	virtual float		get_average_choke(int flow) const = 0;	 // avg packet choke[0..1]
	virtual float		get_average_data(int flow) const = 0;	 // data flow in bytes/sec
	virtual float		get_average_packets(int flow) const = 0; // avg packets/sec
	virtual int			get_total_data(int flow) const = 0;	 // total flow in/out in bytes
	virtual int			get_total_packets(int flow) const = 0;
	virtual int			get_sequence_number(int flow) const = 0;	// last send seq number
	virtual bool		is_valid_packet(int flow, int frame_number) const = 0; // true if packet was not lost/dropped/chocked/flushed
	virtual float		get_packet_time(int flow, int frame_number) const = 0; // time when packet was send
	virtual int			get_packet_bytes(int flow, int frame_number, int group) const = 0; // group size of this packet
	virtual bool		get_stream_progress(int flow, int* received, int* total) const = 0;  // TCP progress if transmitting
	virtual float		get_since_last_time_recieved(void) const = 0;	// get time since last recieved packet in seconds
	virtual	float		get_command_interpolation_ammount(int flow, int frame_number) const = 0;
	virtual void		get_packet_response_latency(int flow, int frame_number, int* latency_msecs, int* choke) const = 0;
	virtual void		get_remote_framerate(float* frame_time, float* frame_time_std_deviation) const = 0;

	virtual float		get_timeout_seconds() const = 0;
};

class net_channel 
{
public:
	char _pad0[20];
	bool m_processing_messages;
	bool m_should_delete;
	char _pad1[2];
	int	 m_out_sequence_number;
	int	 m_in_sequence_number;
	int  m_out_sequence_number_ack;
	int  m_out_reliable_state;
	int  m_in_reliable_state;
	int  m_choked_packets;
	char _pad2[1044];

	int	send_datagram(bf_write* datagram)
	{
		return utils::get_virtual<int(__thiscall*)(void*, bf_write*)>(this, 46)(this, datagram);
	}

	bool transmit(bool only_reliable = false)
	{
		return utils::get_virtual<bool(__thiscall*)(void*, bool)>(this, 49)(this, only_reliable);
	}
};