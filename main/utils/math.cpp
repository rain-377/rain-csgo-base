#include "math.h"

void math::vector_angles(const vector& forward, qangle& view_angle)
{
	float pitch, yaw;

	if (forward.x == 0.f && forward.y == 0.f)
	{
		pitch = (forward.z > 0.f) ? 270.f : 90.f;
		yaw = 0.f;
	}
	else
	{
		pitch = std::atan2f(-forward.z, forward.length_2d()) * 180.f / M_PI;

		if (pitch < 0.f)
			pitch += 360.f;

		yaw = std::atan2f(forward.y, forward.x) * 180.f / M_PI;

		if (yaw < 0.f)
			yaw += 360.f;
	}

	view_angle.x = pitch;
	view_angle.y = yaw;
	view_angle.z = 0.f;
}

void math::angle_vectors(const qangle& angles, vector* forward, vector* right, vector* up) {
	float sp, sy, sr, cp, cy, cr;

	DirectX::XMScalarSinCos(&sp, &cp, M_DEG2RAD(angles.x));
	DirectX::XMScalarSinCos(&sy, &cy, M_DEG2RAD(angles.y));
	DirectX::XMScalarSinCos(&sr, &cr, M_DEG2RAD(angles.z));

	if (forward)
	{
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if (right)
	{
		right->x = -1 * sr * sp * cy + -1 * cr * -sy;
		right->y = -1 * sr * sp * sy + -1 * cr * cy;
		right->z = -1 * sr * cp;
	}

	if (up)
	{
		up->x = cr * sp * cy + -sr * -sy;
		up->y = cr * sp * sy + -sr * cy;
		up->z = cr * cp;
	}
}

qangle math::calc_angle(const vector& start, const vector& end)
{
	qangle view_angle;
	const vector delta = end - start;
	vector_angles(delta, view_angle);
	view_angle.normalize();

	return view_angle;
}