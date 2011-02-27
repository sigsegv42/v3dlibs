#include "AABBox.h"

using namespace v3D;

AABBox::AABBox()
{
}

AABBox::~AABBox()
{
}

Vector3 AABBox::min() const
{
	return min_;
}

Vector3 AABBox::max() const
{
	return max_;
}

void AABBox::min(const Vector3 & v)
{
	min_ = v;
}

void AABBox::max(const Vector3 & v)
{
	max_ = v;
}

Vector3 AABBox::origin() const
{
	return (max_ - min_);
}

void AABBox::vertices(Vector3 * v) const
{
}

// set min & max extents
void AABBox::extents(const Vector3 & min, const Vector3 & max)
{
	min_ = min;
	max_ = max;
}

void AABBox::extend(const Vector3 & point)
{
	if (point[0] < min_[0])
		min_[0] = point[0];
	if (point[1] < min_[1])
		min_[1] = point[1];
	if (point[2] < min_[2])
		min_[2] = point[2];

	if (point[0] > max_[0])
		max_[0] = point[0];
	if (point[1] > max_[1])
		max_[1] = point[1];
	if (point[2] > max_[2])
		max_[2] = point[2];
}

