#define BOOST_TEST_MODULE Color3 test
#include <boost/test/unit_test.hpp>

#include "../3dtypes/Color3.h"

BOOST_AUTO_TEST_CASE( color3_test )
{
	v3D::Color3 color;

	// test default constructor
	BOOST_CHECK_EQUAL(color[0], 0.0f);
	BOOST_CHECK_EQUAL(color[1], 0.0f);
	BOOST_CHECK_EQUAL(color[2], 0.0f);

	// test constants map to correct indices
	BOOST_CHECK_EQUAL(v3D::Color3::RED, 0);
	BOOST_CHECK_EQUAL(v3D::Color3::GREEN, 1);
	BOOST_CHECK_EQUAL(v3D::Color3::BLUE, 2);

	// test single value constructor
	v3D::Color3 color2(1.0f);

	BOOST_CHECK_EQUAL(color2[v3D::Color3::RED], 1.0f);
	BOOST_CHECK_EQUAL(color2[v3D::Color3::GREEN], 1.0f);
	BOOST_CHECK_EQUAL(color2[v3D::Color3::BLUE], 1.0f);

	// test assignment
	color = color2;
	BOOST_CHECK_EQUAL(color[0], 1.0f);
	BOOST_CHECK_EQUAL(color[1], 1.0f);
	BOOST_CHECK_EQUAL(color[2], 1.0f);

	// test addition
	v3D::Color3 color3;
	color3 = color + color2;
	BOOST_CHECK_EQUAL(color3[0], 2.0f);
	BOOST_CHECK_EQUAL(color3[1], 2.0f);
	BOOST_CHECK_EQUAL(color3[2], 2.0f);

	color += color3;
	BOOST_CHECK_EQUAL(color[0], 3.0f);
	BOOST_CHECK_EQUAL(color[1], 3.0f);
	BOOST_CHECK_EQUAL(color[2], 3.0f);

	// test subtraction
	color3 = color - color2;
	BOOST_CHECK_EQUAL(color3[0], 2.0f);
	BOOST_CHECK_EQUAL(color3[1], 2.0f);
	BOOST_CHECK_EQUAL(color3[2], 2.0f);
}
