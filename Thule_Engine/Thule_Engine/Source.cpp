#include "Source.h"

float constrainAngle(float rad_angle)
{
	float new_angle = fmod(rad_angle, 2 * PI);
	if (new_angle < 0)
		new_angle += 2 * PI;
	return new_angle;
}

//approaches end from start with step intervals
float lerp(float step, float start, float end)
{
	return start + (end - start) * step;
}