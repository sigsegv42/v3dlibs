#include <boost/test/unit_test.hpp>

#include "../image/ImageFactory.h"

BOOST_AUTO_TEST_CASE( imagereader_test )
{
	v3D::ImageFactory factory;

	std::string bmpFilename("data/2x2x24_red.bmp");
	boost::shared_ptr<v3D::Image> image = factory.read(bmpFilename);
	BOOST_CHECK_EQUAL(image->width(), 2);
	BOOST_CHECK_EQUAL(image->height(), 2);
	BOOST_CHECK_EQUAL(image->bpp(), 24);
	BOOST_CHECK_EQUAL((*image)[0], 0xff);
	BOOST_CHECK_EQUAL((*image)[1], 0);
	BOOST_CHECK_EQUAL((*image)[2], 0);

	std::string jpgFilename("data/2x2x24_green.jpg");
	boost::shared_ptr<v3D::Image> jpgImage = factory.read(jpgFilename);
	BOOST_CHECK_EQUAL(jpgImage->width(), 2);
	BOOST_CHECK_EQUAL(jpgImage->height(), 2);
	BOOST_CHECK_EQUAL(jpgImage->bpp(), 24);
	BOOST_CHECK_EQUAL((*jpgImage)[0], 0);
	BOOST_CHECK_EQUAL((*jpgImage)[1], 0xff);
	BOOST_CHECK_EQUAL((*jpgImage)[2], 0x1);

}
