#pragma once
#include "../common.h"

namespace fnv1a
{
	constexpr auto m_basis = 0x811C9DC5;
	constexpr auto m_prime = 0x1000193;

	constexpr uint32_t hash_ct(const char* str, const uint32_t value = m_basis) noexcept
	{
		return !*str ? value : hash_ct(&str[1], (value ^ uint32_t(str[0])) * m_prime);
	}

	inline const uint32_t hash_rt(const char* str)
	{
		auto hashed = m_basis;

		for (std::size_t i = 0U; i < strlen(str); ++i)
		{
			hashed ^= str[i];
			hashed *= m_prime;
		}

		return hashed;
	}
}

#define HASH_CT( str ) fnv1a::hash_ct(str)

#define HASH_RT( str ) fnv1a::hash_rt(str)