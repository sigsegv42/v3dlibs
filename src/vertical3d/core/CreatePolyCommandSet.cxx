/*
	Copyright (C) 2008-2009 by Josh Farr
	j.wgasa_at_gmail_dot_com

	This file is part of Vertical|3D.
*/
#include <cmath>

#include "CreatePolyCommandSet.h"
#include "../brep/BRep.h"
#include "../3dtypes/3dtypes.h"

using namespace v3D;

boost::shared_ptr<v3D::BRep> v3D::create_poly_cube()
{
	float length = 1.0;
	float height = 1.0;
	float width  = 1.0;
	length /= 2.0;
	height /= 2.0;
	width  /= 2.0;
	boost::shared_ptr<v3D::BRep> mesh(new v3D::BRep());

	// start new polygon - front
	std::vector<v3D::Vector3> points;
	v3D::Vector3 norm(0.0, 0.0, -1.0);
	// add 4 vertices
	points.push_back(v3D::Vector3(-width, -height, -length));
	points.push_back(v3D::Vector3( width, -height, -length));
	points.push_back(v3D::Vector3( width,  height, -length));
	points.push_back(v3D::Vector3(-width,  height, -length));
	mesh->addFace(points, norm);

	// next polygon - right
	points.clear();
	norm = v3D::Vector3(1.0, 0.0, 0.0);
	points.push_back(v3D::Vector3(width,  -height, -length));
	points.push_back(v3D::Vector3( width, -height,  length));
	points.push_back(v3D::Vector3( width,  height,  length));
	points.push_back(v3D::Vector3( width,  height, -length));
	mesh->addFace(points, norm);

	// next polygon - top
	points.clear();
	norm = v3D::Vector3(0.0, 1.0, 0.0);
	points.push_back(v3D::Vector3(-width,  height, -length));
	points.push_back(v3D::Vector3( width,  height, -length));
	points.push_back(v3D::Vector3( width,  height,  length));
	points.push_back(v3D::Vector3(-width,  height,  length));
	mesh->addFace(points, norm);

	// next polygon - left
	points.clear();
	norm = v3D::Vector3(-1.0, 0.0, 0.0);
	points.push_back(v3D::Vector3(-width, -height,  length));
	points.push_back(v3D::Vector3(-width, -height, -length));
	points.push_back(v3D::Vector3(-width,  height, -length));
	points.push_back(v3D::Vector3(-width,  height,  length));
	mesh->addFace(points, norm);

	// next polygon - back
	points.clear();
	norm = v3D::Vector3(0.0, 0.0, 1.0);
	points.push_back(v3D::Vector3( width, -height,  length));
	points.push_back(v3D::Vector3(-width, -height,  length));
	points.push_back(v3D::Vector3(-width,  height,  length));
	points.push_back(v3D::Vector3( width,  height,  length));
	mesh->addFace(points, norm);

	// next polygon - bottom
	points.clear();
	norm = v3D::Vector3(0.0, -1.0, 0.0);
	points.push_back(v3D::Vector3( width, -height, -length));
	points.push_back(v3D::Vector3(-width, -height, -length));
	points.push_back(v3D::Vector3(-width, -height,  length));
	points.push_back(v3D::Vector3( width, -height,  length));
	mesh->addFace(points, norm);

	return mesh;
}

boost::shared_ptr<v3D::BRep> v3D::create_poly_plane()
{
	float length = 1.0;
	float width  = 1.0;
	length /= 2.0;
	width  /= 2.0;

	boost::shared_ptr<v3D::BRep> mesh(new v3D::BRep());

	v3D::Vector3 norm(0.0, 1.0, 0.0);

	// add 4 vertices
	std::vector<v3D::Vector3> vertices;
	vertices.push_back(Vector3(-width, 0.0, -length));
	vertices.push_back(Vector3( width, 0.0, -length));
	vertices.push_back(Vector3( width, 0.0,  length));
	vertices.push_back(Vector3(-width, 0.0,  length));
	mesh->addFace(vertices, norm);

	return mesh;
}

boost::shared_ptr<v3D::BRep> v3D::create_poly_cone()
{
	int sides = 8;
	float height = 1.0;
	float radius = 0.5;

	float delta = 2.0 * PI / sides;

	boost::shared_ptr<v3D::BRep> mesh(new v3D::BRep());

	// create points in cone
	std::vector<v3D::Vector3> points;
	for (int k = 0; k <= sides; k++)
	{
		v3D::Vector3 p;
		int v;
		p[0] = cos(delta * k) * radius;
		p[1] = sin(delta * k) * radius;
		points.push_back(p);
	}
	// top point
	v3D::Vector3 v3(0.0, 0.0, height);
	points.push_back(v3);

	// create polygons in cone
	for (int k = 1; k <= sides; k++)
	{
		v3D::Vector3 norm(1.0, 0.0, 0.0);
		std::vector<v3D::Vector3> face;
		v3D::Vector3 v1, v2;
		v1 = points[k-1];
		if (k == points.size())
		{
			v2 = points[0];
		}
		else
		{
			v2 = points[k];
		}

		// add vertices to polygon
		face.push_back(v1);
		face.push_back(v2);
		face.push_back(v3);

		// add polygon to mesh
		mesh->addFace(face, norm);
	}

	return mesh;
}

boost::shared_ptr<v3D::BRep> v3D::create_poly_cylinder()
{
	int sides = 8;
	float height = 1.0;
	float radius = 0.5;

	float delta = 2.0 * PI / sides;

	boost::shared_ptr<v3D::BRep> mesh(new v3D::BRep());

	// create points in cylinder
	std::vector<v3D::Vector3> points;
	std::vector<v3D::Vector3> points_top;
	for (int k = 0; k <= sides; k++)
	{
		v3D::Vector3 p;
		p[0] = cos(delta * k) * radius;
		p[1] = sin(delta * k) * radius;
		p[2] = 0.0;
		points.push_back(p);
		// corresponding top point
		p[2] += height;
		points_top.push_back(p);
	}

	// create each polygon side of the cylinder
	for (int k = 1; k <= sides; k++)
	{
		std::vector<Vector3> face;
		v3D::Vector3 v1, v2, v3, v4;
		v3D::Vector3 norm(1.0, 0.0, 0.0);

		// get vertex indices
		v1 = points[k - 1];
		if (k == points.size())
		{
			v2 = points[0];
		}
		else
		{
			v2 = points[k];
		}
		// top two points (z + height)
		if (k == points_top.size())
		{
			v3 = points_top[0];
		}
		else
		{
			v3 = points_top[k];
		}
		v4 = points_top[k - 1];

		// add vertices to polygon
		face.push_back(v1);
		face.push_back(v2);
		face.push_back(v3);
		face.push_back(v4);

		// add polygon to mesh
		mesh->addFace(face, norm);
	}

	return mesh;
}
