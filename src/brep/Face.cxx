#include "Face.h"

using namespace v3D;

Face::Face()
{
}

Face::Face(const Vector3 & normal, unsigned int edge) : normal_(normal), edge_(edge)
{
}

Face::~Face()
{
}

Vector3 Face::normal(void) const
{
	return normal_;
}

void Face::normal(const Vector3 & n)
{
	normal_ = n;
}

unsigned int Face::edge(void) const
{
	return edge_;
}

void Face::edge(unsigned int e)
{
	edge_ = e;
}
