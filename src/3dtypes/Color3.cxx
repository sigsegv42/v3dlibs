#include "Color3.h"

#include <cassert>

using namespace v3D;

Color3::Color3(float r, float g, float b)
{
	data_[RED] = r;
	data_[GREEN] = g;
	data_[BLUE] = b;
}

Color3::Color3(float val)
{
	data_[RED] = data_[GREEN] = data_[BLUE] = val;
}

Color3::Color3()
{
	data_[RED] = data_[GREEN] = data_[BLUE] = 0.0f;
}

Color3 & Color3::operator = (const Color3 & c)
{
	data_[RED] = c.data_[RED];
	data_[GREEN] = c.data_[GREEN];
	data_[BLUE] = c.data_[BLUE];

	return *this;
}

Color3 & Color3::operator += (const Color3 & c)
{
	data_[RED] += c.data_[RED];
	data_[GREEN] += c.data_[GREEN];
	data_[BLUE] += c.data_[BLUE];

	return *this;
}

float Color3::operator [] (unsigned int i) const
{
	assert (i < 3);
	return data_[i];
}

float & Color3::operator[](unsigned int i)
{
	assert (i < 3);
	return data_[i];
}

const Color3 operator * (const Color3 & lhs, float f)
{
	Color3 c = lhs;
	c[0] *= f;
	c[1] *= f;
	c[2] *= f;

	return c;
}

const Color3 operator / (const Color3 & lhs, float f)
{
	Color3 c = lhs;
	c[0] /= f;
	c[1] /= f;
	c[2] /= f;

	return c;
}

const Color3 operator + (const Color3 & lhs, const Color3 & rhs)
{
	Color3 c = lhs;
	c[0] += rhs[0];
	c[1] += rhs[1];
	c[2] += rhs[2];

	return c;
}

const Color3 operator - (const Color3 & lhs, const Color3 & rhs)
{
	Color3 c = lhs;
	c[0] -= rhs[0];
	c[1] -= rhs[1];
	c[2] -= rhs[2];

	return c;
}
