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

	// test setting box extents
	v3D::Vector3 min_extent(3.0f, 9.0f, 11.0f);
	v3D::Vector3 max_extent(11.0f, 17.0f, 23.0f);
	box.extents(min_extent, max_extent);
	min_check = box.min();
	BOOST_CHECK_EQUAL((min_extent == min_check), true);
	max_check = box.max();
	BOOST_CHECK_EQUAL((max_extent == max_check), true);


	// test extending box
	v3D::Vector3 point(17.0f, 3.0f, 34.0f);
	box.extend(point);
	min_check = box.min();
	min_extent = v3D::Vector3(3.0f, 3.0f, 11.0f);
	BOOST_CHECK_EQUAL((min_extent == min_check), true);
	max_check = box.max();
	max_extent = v3D::Vector3(17.0f, 17.0f, 34.0f);
	BOOST_CHECK_EQUAL((max_extent == max_check), true);

	// test other branches of extend operation
	point = v3D::Vector3(1.0f, 27.0f, 7.0f);
	box.extend(point);
	min_check = box.min();
	min_extent = v3D::Vector3(1.0f, 3.0f, 7.0f);
	BOOST_CHECK_EQUAL((min_extent == min_check), true);
	max_check = box.max();
	max_extent = v3D::Vector3(17.0f, 27.0f, 34.0f);
	BOOST_CHECK_EQUAL((max_extent == max_check), true);
}
