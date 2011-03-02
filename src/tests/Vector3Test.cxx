#include <boost/test/unit_test.hpp>

#include "../3dtypes/Vector3.h"

BOOST_AUTO_TEST_CASE( vector3_test )
{
	// test default constructor
	v3D::Vector3 vector;
	BOOST_CHECK_EQUAL(vector[0], 0.0f);
	BOOST_CHECK_EQUAL(vector[1], 0.0f);
	BOOST_CHECK_EQUAL(vector[2], 0.0f);

	v3D::Vector3 vector2(3.0f);
	BOOST_CHECK_EQUAL(vector[0], 3.0f);
	BOOST_CHECK_EQUAL(vector[1], 3.0f);
	BOOST_CHECK_EQUAL(vector[2], 3.0f);

	// test comparison operators
	BOOST_CHECK_EQUAL((vector != vector2), true);

	// test addition
	vector += vector2;

	BOOST_CHECK_EQUAL((vector == vector2), true);

	// test contructor 3rd form
	v3D::Vector3 vector3(3.0f, 7.0f, 11.0f);
	BOOST_CHECK_EQUAL(vector[0], 3.0f);
	BOOST_CHECK_EQUAL(vector[1], 7.0f);
	BOOST_CHECK_EQUAL(vector[2], 11.0f);

}