#pragma once
#include "../common.h"

class qangle
{
public:
	constexpr qangle(float x = 0.f, float y = 0.f, float z = 0.f) :
		x(x), y(y), z(z) { }

	constexpr qangle(const float* angles) :
		x(angles[0]), y(angles[1]), z(angles[2]) { }

	bool operator==(const qangle& base) const
	{
		return this->is_equal(base);
	}

	bool operator!=(const qangle& base) const
	{
		return !this->is_equal(base);
	}

	constexpr qangle& operator=(const qangle& base)
	{
		this->x = base.x; this->y = base.y; this->z = base.z;
		return *this;
	}

	constexpr qangle& operator+=(const qangle& base)
	{
		this->x += base.x; this->y += base.y; this->z += base.z;
		return *this;
	}

	constexpr qangle& operator-=(const qangle& base)
	{
		this->x -= base.x; this->y -= base.y; this->z -= base.z;
		return *this;
	}

	constexpr qangle& operator*=(const qangle& base)
	{
		this->x *= base.x; this->y *= base.y; this->z *= base.z;
		return *this;
	}

	constexpr qangle& operator/=(const qangle& base)
	{
		this->x /= base.x; this->y /= base.y; this->z /= base.z;
		return *this;
	}

	constexpr qangle& operator+=(const float flAdd)
	{
		this->x += flAdd; this->y += flAdd; this->z += flAdd;
		return *this;
	}

	constexpr qangle& operator-=(const float flSubtract)
	{
		this->x -= flSubtract; this->y -= flSubtract; this->z -= flSubtract;
		return *this;
	}

	constexpr qangle& operator*=(const float flMultiply)
	{
		this->x *= flMultiply; this->y *= flMultiply; this->z *= flMultiply;
		return *this;
	}

	constexpr qangle& operator/=(const float flDivide)
	{
		this->x /= flDivide; this->y /= flDivide; this->z /= flDivide;
		return *this;
	}

	qangle operator+(const qangle& angAdd) const
	{
		return qangle(this->x + angAdd.x, this->y + angAdd.y, this->z + angAdd.z);
	}

	qangle operator-(const qangle& angSubtract) const
	{
		return qangle(this->x - angSubtract.x, this->y - angSubtract.y, this->z - angSubtract.z);
	}

	qangle operator*(const qangle& angMultiply) const
	{
		return qangle(this->x * angMultiply.x, this->y * angMultiply.y, this->z * angMultiply.z);
	}

	qangle operator/(const qangle& angDivide) const
	{
		return qangle(this->x / angDivide.x, this->y / angDivide.y, this->z / angDivide.z);
	}

	qangle operator+(const float flAdd) const
	{
		return qangle(this->x + flAdd, this->y + flAdd, this->z + flAdd);
	}

	qangle operator-(const float flSubtract) const
	{
		return qangle(this->x - flSubtract, this->y - flSubtract, this->z - flSubtract);
	}

	qangle operator*(const float flMultiply) const
	{
		return qangle(this->x * flMultiply, this->y * flMultiply, this->z * flMultiply);
	}

	qangle operator/(const float flDivide) const
	{
		return qangle(this->x / flDivide, this->y / flDivide, this->z / flDivide);
	}

	[[nodiscard]] bool is_equal(const qangle& angEqual, const float flErrorMargin = std::numeric_limits<float>::epsilon()) const
	{
		return (std::fabsf(this->x - angEqual.x) < flErrorMargin &&
			std::fabsf(this->y - angEqual.y) < flErrorMargin &&
			std::fabsf(this->z - angEqual.z) < flErrorMargin);
	}

	[[nodiscard]] bool is_zero() const
	{
		return (std::fpclassify(this->x) == FP_ZERO &&
			std::fpclassify(this->y) == FP_ZERO &&
			std::fpclassify(this->z) == FP_ZERO);
	}

	void clamp()
	{
		this->x = std::clamp(this->x, -89.f, 89.f);
		this->y = std::clamp(this->y, -180.f, 180.f);
		this->z = std::clamp(this->z, -50.f, 50.f);
	}

	qangle normalize()
	{
		this->x = std::isfinite(this->x) ? std::remainderf(this->x, 360.f) : 0.f;
		this->y = std::isfinite(this->y) ? std::remainderf(this->y, 360.f) : 0.f;
		this->z = std::clamp(this->z, -50.f, 50.f);
		return *this;
	}

	qangle mod(const float flValue)
	{
		this->x = std::fmodf(this->x, flValue);
		this->y = std::fmodf(this->y, flValue);
		this->z = std::fmodf(this->z, flValue);
		return *this;
	}

public:
	float x, y, z;
};