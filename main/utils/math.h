#pragma once
#include <directxmath.h>
#include "../sdk/vector.h"
#include "../sdk/qangle.h"
#include "../sdk/matrix.h"

#define M_PI DirectX::XM_PI
#define M_RADPI	180.f / M_PI

#define M_RAD2DEG( x ) DirectX::XMConvertToDegrees( x )
#define M_DEG2RAD( x ) DirectX::XMConvertToRadians( x )

namespace math
{
	void vector_angles(const vector& forward, qangle& view_angle);
	void angle_vectors(const qangle& angles, vector* forward, vector* right = nullptr, vector* up = nullptr);
	vector vector_transform(const vector& vec_transform, const matrix3x4_t& matrix);
	qangle calc_angle(const vector& start, const vector& angle);
}