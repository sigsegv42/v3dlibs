#include "Vector2.h"

#ifndef USE_TEMPLATE_VECTOR

#include <cassert>

using namespace v3D;

Vector2::Vector2()
{
	vec_[0] = vec_[1] = 0.0f;
}

Vector2::Vector2(float x, float y)
{
	vec_[0] = x;
	vec_[1] = y;
}

bool Vector2::operator == (const Vector2 & v)
{
	if (vec_[0] == v.vec_[0] && vec_[1] == v.vec_[1])
		return true;
	return false;
}

Vector2 & Vector2::operator += (const Vector2 & v)
{
	vec_[0] += v.vec_[0];
	vec_[1] += v.vec_[1];

	return *this;
}

Vector2 & Vector2::operator *= (float f)
{
	vec_[0] *= f;
	vec_[1] *= f;

	return *this;
}

Vector2 & Vector2::operator -= (const Vector2 & v)
{
	vec_[0] -= v.vec_[0];
	vec_[1] -= v.vec_[1];

	return *this;
}

Vector2 Vector2::operator - () const
{
	return Vector2(-vec_[0], -vec_[1]);
}

float Vector2::operator[](unsigned int i) const
{
	assert (i < 2);
	return vec_[i];
}

float & Vector2::operator[](unsigned int i)
{
	assert (i < 2);
	return vec_[i];
}

#endif
