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

bool isInRange(float x, float min, float max)
{
	return (x>min)&&(x<max);
}

sf::FloatRect scaleToFit(const sf::Vector2u windowDim)
{
	if (windowDim.x * SCREEN_WH_RATIO > windowDim.y) //window is horizontaly elongated
	{
		float x = .5f - (windowDim.y / (float)windowDim.x) / (SCREEN_WH_RATIO + SCREEN_WH_RATIO);
		float w = (.5f - x) * 2.f;
		return sf::FloatRect(x, .0f, w, 1.0f);
	}
	else
	{
		float y = .5f - (windowDim.x / (float)windowDim.y) * (SCREEN_WH_RATIO/2);
		float h = (.5f - y) * 2.f;
		return sf::FloatRect(.0f, y, 1.0f, h); //window is verticaly elongated
	}
}
