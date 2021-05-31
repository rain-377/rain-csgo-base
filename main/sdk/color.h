#pragma once
#include "../common.h"

struct col 
{

	std::array<uint8_t, 4> m_color;

	col() = default;

	col(const int r, const int g, const int b) : m_color({ 0,0,0,0 })
	{
		set(r, g, b, 255);
	}

	col(const int r, const int g, const int b, const int a) : m_color({ 0,0,0,0 })
	{
		set(r, g, b, a);
	}

	col(const float r, const float g, const float b) : m_color({ 0,0,0,0 })
	{
		set(static_cast<int>(r * 255),
			static_cast<int>(g * 255),
			static_cast<int>(b * 255), 255);
	}

	col(const float r, const float g, const float b, const float a) : m_color({ 0,0,0,0 })
	{
		set(static_cast<int>(r * 255),
			static_cast<int>(g * 255),
			static_cast<int>(b * 255),
			static_cast<int>(a * 255));
	}

	col(const col& col, const int a) : m_color({ 0,0,0,0 })
	{
		set(col.r(), col.g(), col.b(), a);
	}

	inline void set(const int r, const int g, const int b, const int a)
	{
		m_color[0] = static_cast<uint8_t>(r);
		m_color[1] = static_cast<uint8_t>(g);
		m_color[2] = static_cast<uint8_t>(b);
		m_color[3] = static_cast<uint8_t>(a);
	}

	inline int r() const
	{
		return m_color[0];
	}

	inline int g() const
	{
		return m_color[1];
	}

	inline int b() const
	{
		return m_color[2];
	}

	inline int a() const
	{
		return m_color[3];
	}

	inline col& operator=(const col& in)
	{
		set(in.r(), in.g(), in.b(), in.a());
		return *this;
	}

	inline bool operator==(const col& in) const
	{
		return *const_cast<col*>(this) == *const_cast<col*>(&in);
	}

	inline bool operator!=(const col& in) const
	{
		return !(operator==(in));
	}

	float hue() const
	{
		float r = m_color[0] / 255.0f;
		float g = m_color[1] / 255.0f;
		float b = m_color[2] / 255.0f;

		float mx = max(r, max(g, b));
		float mn = min(r, min(g, b));
		if (mx == mn)
			return 0.f;

		float delta = mx - mn;

		float hue = 0.f;
		if (mx == r)
			hue = (g - b) / delta;
		else if (mx == g)
			hue = 2.f + (b - r) / delta;
		else
			hue = 4.f + (r - g) / delta;

		hue *= 60.f;
		if (hue < 0.f)
			hue += 360.f;

		return hue / 360.f;
	}

	float saturation() const
	{
		float r = m_color[0] / 255.0f;
		float g = m_color[1] / 255.0f;
		float b = m_color[2] / 255.0f;

		float mx = max(r, max(g, b));
		float mn = min(r, min(g, b));

		float delta = mx - mn;

		if (mx == 0.f)
			return delta;

		return delta / mx;
	}

	float brightness() const
	{
		float r = m_color[0] / 255.0f;
		float g = m_color[1] / 255.0f;
		float b = m_color[2] / 255.0f;

		return max(r, max(g, b));
	}

	static col from_hsb(float hue, float saturation, float brightness)
	{
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - (int)h;
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));

		if (h < 1)
		{
			return col(
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255),
				(unsigned char)(p * 255)
			);
		}
		if (h < 2)
		{
			return col(
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255)
			);
		}
		if (h < 3)
		{
			return col(
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255)
			);
		}
		if (h < 4)
		{
			return col(
				(unsigned char)(p * 255),
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255)
			);
		}
		if (h < 5)
		{
			return col(
				(unsigned char)(t * 255),
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255)
			);
		}
		return col(
			(unsigned char)(brightness * 255),
			(unsigned char)(p * 255),
			(unsigned char)(q * 255)
		);
	}

	uint32_t hex(bool rgba = false) const {
		return rgba
			? ((r() & 0xFF) << 24) + ((g() & 0xFF) << 16) + ((b() & 0xFF) << 8) + (a() & 0xFF)
			: ((a() & 0xFF) << 24) + ((b() & 0xFF) << 16) + ((g() & 0xFF) << 8) + (r() & 0xFF);
	}

	static col black(int alpha = 255) { return col(13, 13, 13, alpha); }
	static col light_black(int alpha = 255) { return col(32, 32, 32, alpha); }
	static col dark_grey(int alpha = 255) { return col(44, 44, 44, alpha); }
	static col grey(int alpha = 255) { return col(60, 60, 60, alpha); }
	static col light_grey(int alpha = 255) { return col(77, 77, 77, alpha); }
	static col red(int alpha = 255) { return col(236, 98, 95, alpha); }
};