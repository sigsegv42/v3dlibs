#include <boost/test/unit_test.hpp>

#include "../font/Font2D.h"

BOOST_AUTO_TEST_CASE( font_test )
{
	v3D::Font2D font;
	font.size(12);

	int size = font.size();
	BOOST_CHECK_EQUAL(size, 12);

	font.style(v3D::Font2D::STYLE_BOLD);
	unsigned int style = font.style();
	BOOST_CHECK_EQUAL(style, v3D::Font2D::STYLE_BOLD);

	std::string fontface("Comic Sans");
	font.typeface(fontface);
	std::string checkface = font.typeface();
	BOOST_CHECK_EQUAL((fontface == checkface), true);
}