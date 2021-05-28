#pragma once
#include "../common.h"

class bf_write
{
public:
	bf_write() = default;

	// the current buffer
	unsigned long*	m_data;
	int				m_data_bytes;
	int				m_data_bits;

	// where we are in the buffer
	int				m_current_bits;
};

class bf_read
{
public:
	std::uintptr_t m_base_address;
	std::uintptr_t m_current_offset;

	bf_read(std::uintptr_t address) : m_base_address(address), m_current_offset(0U) {}

	void set_offset(std::uintptr_t offset)
	{
		m_current_offset = offset;
	}

	void skip(std::uintptr_t length)
	{
		m_current_offset += length;
	}

	int read_byte()
	{
		char value = *reinterpret_cast<char*>(m_base_address + m_current_offset);
		++m_current_offset;
		return value;
	}

	bool read_bool()
	{
		bool value = *reinterpret_cast<bool*>(m_base_address + m_current_offset);
		++m_current_offset;
		return value;
	}

	const char* read_string()
	{
		char buffer[256];
		char length = *reinterpret_cast<char*>(m_base_address + m_current_offset);
		++m_current_offset;
		memcpy(buffer, reinterpret_cast<void*>(m_base_address + m_current_offset), length > 255 ? 255 : length);
		buffer[length > 255 ? 255 : length] = '\0';
		m_current_offset += length + 1;
		return buffer;
	}
};