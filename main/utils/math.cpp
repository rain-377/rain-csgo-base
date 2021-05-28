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

qangle math::calc_angle(const vector& start, const vector& end)
{
	qangle view_angle;
	const vector delta = end - start;
	vector_angles(delta, view_angle);
	view_angle.normalize();

	return view_angle;
}