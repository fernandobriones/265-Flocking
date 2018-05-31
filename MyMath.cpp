#include "MyMath.h"
#include "cmath"
#include "Global.h"

using namespace sf;

float magnitude(Vector2f vector)
{
	return sqrtf((vector.x*vector.x) + (vector.y*vector.y));
}

Vector2f normalize(Vector2f vector)
{
	float mag = magnitude(vector);
	if (mag == 0)
		return Vector2f(0, 0);
	vector.x = vector.x / mag;
	vector.y = vector.y / mag;
	return vector;
}

void limit(Vector2f & vector, float limit)
{
	if (magnitude(vector) > limit)
	{
		vector = normalize(vector);
		vector.x *= limit;
		vector.y *= limit;

	}
}

float heading(Vector2f vector)
{
	float result = atan2(vector.y, vector.x);
	result = result * (float)(180 / pi);
	return result;
}