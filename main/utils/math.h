#pragma once
#include <directxmath.h>
#include "../sdk/vector.h"
#include "../sdk/qangle.h"

#define M_PI DirectX::XM_PI
#define M_RADPI	180.f / M_PI

namespace math
{
	void vector_angles(const vector& forward, qangle& view_angle);
	qangle calc_angle(const vector& start, const vector& angle);
}