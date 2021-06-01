#pragma once
#include "../common.h"

class vector_2d
{
public:
	constexpr vector_2d(float x = 0.f, float y = 0.f) :
		x(x), y(y) { }

	[[nodiscard]] bool is_zero() const
	{
		return (std::fpclassify(this->x) == FP_ZERO &&
			std::fpclassify(this->y) == FP_ZERO);
	}

public:
	float x, y;
}; 

class vector
{
public:
	constexpr vector(float x = 0.f, float y = 0.f, float z = 0.f) :
		x(x), y(y), z(z) { }

	constexpr vector(const float* arrvector) :
		x(arrvector[0]), y(arrvector[1]), z(arrvector[2]) { }

	constexpr vector(const vector_2d& base2D) :
		x(base2D.x), y(base2D.y), z(0.0f) { }

	[[nodiscard]] bool is_valid() const
	{
		return std::isfinite(this->x) && std::isfinite(this->y) && std::isfinite(this->z);
	}

	constexpr void invalidate()
	{
		this->x = this->y = this->z = std::numeric_limits<float>::infinity();
	}

	[[nodiscard]] float* data()
	{
		return reinterpret_cast<float*>(this);
	}

	[[nodiscard]] const float* data() const
	{
		return reinterpret_cast<float*>(const_cast<vector*>(this));
	}

	float& operator[](const std::size_t i)
	{
		return this->data()[i];
	}

	const float& operator[](const std::size_t i) const
	{
		return this->data()[i];
	}

	bool operator==(const vector& base) const
	{
		return this->is_equal(base);
	}

	bool operator!=(const vector& base) const
	{
		return !this->is_equal(base);
	}

	constexpr vector& operator=(const vector& base)
	{
		this->x = base.x; this->y = base.y; this->z = base.z;
		return *this;
	}

	constexpr vector& operator=(const vector_2d& base2D)
	{
		this->x = base2D.x; this->y = base2D.y; this->z = 0.0f;
		return *this;
	}

	constexpr vector& operator+=(const vector& base)
	{
		this->x += base.x; this->y += base.y; this->z += base.z;
		return *this;
	}

	constexpr vector& operator-=(const vector& base)
	{
		this->x -= base.x; this->y -= base.y; this->z -= base.z;
		return *this;
	}

	constexpr vector& operator*=(const vector& base)
	{
		this->x *= base.x; this->y *= base.y; this->z *= base.z;
		return *this;
	}

	constexpr vector& operator/=(const vector& base)
	{
		this->x /= base.x; this->y /= base.y; this->z /= base.z;
		return *this;
	}

	constexpr vector& operator+=(const float add)
	{
		this->x += add; this->y += add; this->z += add;
		return *this;
	}

	constexpr vector& operator-=(const float subtract)
	{
		this->x -= subtract; this->y -= subtract; this->z -= subtract;
		return *this;
	}

	constexpr vector& operator*=(const float multiply)
	{
		this->x *= multiply; this->y *= multiply; this->z *= multiply;
		return *this;
	}

	constexpr vector& operator/=(const float divide)
	{
		this->x /= divide; this->y /= divide; this->z /= divide;
		return *this;
	}

	vector operator+(const vector& add) const
	{
		return vector(this->x + add.x, this->y + add.y, this->z + add.z);
	}

	vector operator-(const vector& subtract) const
	{
		return vector(this->x - subtract.x, this->y - subtract.y, this->z - subtract.z);
	}

	vector operator*(const vector& multiply) const
	{
		return vector(this->x * multiply.x, this->y * multiply.y, this->z * multiply.z);
	}

	vector operator/(const vector& divide) const
	{
		return vector(this->x / divide.x, this->y / divide.y, this->z / divide.z);
	}

	vector operator+(const float add) const
	{
		return vector(this->x + add, this->y + add, this->z + add);
	}

	vector operator-(const float subtract) const
	{
		return vector(this->x - subtract, this->y - subtract, this->z - subtract);
	}

	vector operator*(const float multiply) const
	{
		return vector(this->x * multiply, this->y * multiply, this->z * multiply);
	}

	vector operator/(const float divide) const
	{
		return vector(this->x / divide, this->y / divide, this->z / divide);
	}

	[[nodiscard]] bool is_equal(const vector& equal) const
	{
		return (std::fabsf(this->x - equal.x) < std::numeric_limits<float>::epsilon() &&
			std::fabsf(this->y - equal.y) < std::numeric_limits<float>::epsilon() &&
			std::fabsf(this->z - equal.z) < std::numeric_limits<float>::epsilon());
	}

	[[nodiscard]] bool is_zero() const
	{
		return (std::fpclassify(this->x) == FP_ZERO &&
			std::fpclassify(this->y) == FP_ZERO &&
			std::fpclassify(this->z) == FP_ZERO);
	}

	[[nodiscard]] vector_2d to_vector_2d() const
	{
		return vector_2d(this->x, this->y);
	}

	[[nodiscard]] float length() const
	{
		return std::sqrtf(this->length_sqr());
	}

	[[nodiscard]] constexpr float length_sqr() const
	{
		return dot_product(*this);
	}

	[[nodiscard]] float length_2d() const
	{
		return std::sqrtf(this->length_2d_sqr());
	}

	[[nodiscard]] constexpr float length_2d_sqr() const
	{
		return (this->x * this->x + this->y * this->y);
	}

	[[nodiscard]] float dist_to(const vector& end) const
	{
		return (*this - end).length();
	}

	[[nodiscard]] constexpr float dist_to_sqr(const vector& end) const
	{
		return (*this - end).length_sqr();
	}

	[[nodiscard]] vector normalized() const
	{
		vector vecOut = *this;
		vecOut.normalize_in_place();
		return vecOut;
	}

	float normalize_in_place()
	{
		const float length = this->length();
		const float radius = 1.0f / (length + std::numeric_limits<float>::epsilon());

		this->x *= radius;
		this->y *= radius;
		this->z *= radius;

		return length;
	}

	[[nodiscard]] constexpr float dot_product(const vector& dot) const
	{
		return (this->x * dot.x + this->y * dot.y + this->z * dot.z);
	}

	[[nodiscard]] constexpr vector cross_product(const vector& cross) const
	{
		return vector(this->y * cross.z - this->z * cross.y, this->z * cross.x - this->x * cross.z, this->x * cross.y - this->y * cross.x);
	}

public:
	float x, y, z;
};

class vector_4d
{
public:
	constexpr vector_4d(float x = 0.f, float y = 0.f, float z = 0.f, float w = 0.f) :
		x(x), y(y), z(z), w(w) { }

public:
	float x, y, z, w;
};

class __declspec(align(16)) vector_aligned : public vector
{
public:
	vector_aligned() = default;

	explicit vector_aligned(const vector& vecBase)
	{
		this->x = vecBase.x; this->y = vecBase.y; this->z = vecBase.z; this->w = 0.f;
	}

	constexpr vector_aligned& operator=(const vector& vecBase)
	{
		this->x = vecBase.x; this->y = vecBase.y; this->z = vecBase.z; this->w = 0.f;
		return *this;
	}

public:
	float w;
};