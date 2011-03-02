#include <boost/test/unit_test.hpp>

#include "../3dtypes/Vector2.h"

BOOST_AUTO_TEST_CASE( vector2_test )
{
	// test default constructor
	v3D::Vector2 vector;
	BOOST_CHECK_EQUAL(vector[0], 0.0f);
	BOOST_CHECK_EQUAL(vector[1], 0.0f);

	// test second constructor
	v3D::Vector2 vector2(5.0f, 9.0f);
	BOOST_CHECK_EQUAL(vector2[0], 5.0f);
	BOOST_CHECK_EQUAL(vector2[1], 9.0f);

	// test comparison
	BOOST_CHECK_EQUAL((vector == vector2), false);

	// test assignment
	vector[0] = 5.0f;
	vector[1] = 9.0f;
	BOOST_CHECK_EQUAL((vector == vector2), true);

	// test addition
	vector += vector2;
	BOOST_CHECK_EQUAL(vector[0], 10.0f);
	BOOST_CHECK_EQUAL(vector[1], 18.0f);

	// test scaling
	vector2 *= 3.0f;
	BOOST_CHECK_EQUAL(vector2[0], 15.0f);
	BOOST_CHECK_EQUAL(vector2[1], 27.0f);

	// test subtraction
	vector2 -= vector;
	BOOST_CHECK_EQUAL(vector2[0], 5.0f);
	BOOST_CHECK_EQUAL(vector2[1], 9.0f);

	// test negate
	vector = -vector2;
	BOOST_CHECK_EQUAL(vector[0], -5.0f);
	BOOST_CHECK_EQUAL(vector[1], -9.0f);

}