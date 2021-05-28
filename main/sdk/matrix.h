#pragma once
#include "vector.h"

struct view_matrix
{
	view_matrix() = default;

	float* operator[](const int index)
	{
		return data[index];
	}

	const float* operator[](const int index) const
	{
		return data[index];
	}

	float data[4][4] = { };
};

using matrix3x3_t = float[3][3];
struct matrix3x4_t
{
	matrix3x4_t() = default;

	matrix3x4_t(
		const float m00, const float m01, const float m02, const float m03,
		const float m10, const float m11, const float m12, const float m13,
		const float m20, const float m21, const float m22, const float m23)
	{
		data[0][0] = m00; data[0][1] = m01; data[0][2] = m02; data[0][3] = m03;
		data[1][0] = m10; data[1][1] = m11; data[1][2] = m12; data[1][3] = m13;
		data[2][0] = m20; data[2][1] = m21; data[2][2] = m22; data[2][3] = m23;
	}

	matrix3x4_t(const vector& xAxis, const vector& yAxis, const vector& zAxis, const vector& vecOrigin)
	{
		Init(xAxis, yAxis, zAxis, vecOrigin);
	}

	constexpr void Init(const vector& vecForward, const vector& vecLeft, const vector& vecUp, const vector& vecOrigin)
	{
		set_forward(vecForward);
		set_left(vecLeft);
		set_up(vecUp);
		set_origin(vecOrigin);
	}

	constexpr void set_forward(const vector& vecForward)
	{
		this->data[0][0] = vecForward.x;
		this->data[1][0] = vecForward.y;
		this->data[2][0] = vecForward.z;
	}

	constexpr void set_left(const vector& vecLeft)
	{
		this->data[0][1] = vecLeft.x;
		this->data[1][1] = vecLeft.y;
		this->data[2][1] = vecLeft.z;
	}

	constexpr void set_up(const vector& vecUp)
	{
		this->data[0][2] = vecUp.x;
		this->data[1][2] = vecUp.y;
		this->data[2][2] = vecUp.z;
	}

	constexpr void set_origin(const vector& vecOrigin)
	{
		this->data[0][3] = vecOrigin.x;
		this->data[1][3] = vecOrigin.y;
		this->data[2][3] = vecOrigin.z;
	}

	constexpr void invalidate()
	{
		for (auto& arrSubData : data)
		{
			for (auto& data : arrSubData)
				data = std::numeric_limits<float>::infinity();
		}
	}

	float* operator[](const int index)
	{
		return data[index];
	}

	const float* operator[](const int index) const
	{
		return data[index];
	}

	[[nodiscard]] constexpr vector at(const int index) const
	{
		return vector(data[0][index], data[1][index], data[2][index]);
	}

	float* base()
	{
		return &data[0][0];
	}

	[[nodiscard]] const float* base() const
	{
		return &data[0][0];
	}

	float data[3][4] = { };
};

__declspec(align(16)) class matrix3x4a_t : public matrix3x4_t
{
public:
	matrix3x4a_t& operator=(const matrix3x4_t& source)
	{
		std::copy_n(source.base(), sizeof(float) * 3U * 4U, this->base());
		return *this;
	}
};