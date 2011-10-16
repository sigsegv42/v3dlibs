#include <boost/test/unit_test.hpp>

#include "../3dtypes/AABBox.h"

BOOST_AUTO_TEST_CASE( aabbox_test )
{
	v3D::AABBox box;

	// set box minimum
	v3D::Vector3 min(5.0f, 4.0f, 3.0f);
	box.min(min);

	// test box minimum set/get
	v3D::Vector3 min_check = box.min();
	BOOST_CHECK_EQUAL((min == min_check), true);

	// set box maximum
	v3D::Vector3 max(10.0f, 15.0f, 20.0f);
	box.max(max);

	// test box maximum set/get
	v3D::Vector3 max_check = box.max();
	BOOST_CHECK_EQUAL((max == max_check), true);

	// test box origin
	v3D::Vector3 origin = box.origin();
	BOOST_CHECK_EQUAL(origin[0], 5.0f);
	BOOST_CHECK_EQUAL(origin[1], 11.0f);
	BOOST_CHECK_EQUAL(origin[2], 17.0f);

}