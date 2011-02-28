#include "Vertex.h"

using namespace v3D;

Vertex::Vertex()
{
}

Vertex::Vertex(const Vector3 & p) : point_(p)
{
}

Vertex::~Vertex()
{
}

bool Vertex::operator == (const Vertex & v)
{
	return (point_ == v.point_);
}

bool Vertex::operator == (const Vector3 & v)
{
	return (point_ == v);
}

unsigned int Vertex::edge(void) const
{
	return edge_;
}

void Vertex::edge(unsigned int e)
{
	edge_ = e;
}

Vector3 Vertex::point(void) const
{
	return point_;
}

void Vertex::point(const Vector3 & p)
{
	point_ = p;
}
