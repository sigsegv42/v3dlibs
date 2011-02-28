#include "FontCache.h"

using namespace v3D;

FontCache::FontCache()
{
}

FontCache::~FontCache()
{
/*
	std::map<std::string, boost::shared_ptr<Font2D> >::iterator it = _fonts.begin();
	for (; it != _fonts.end(); it++)
	{
		it->second->destroy();
	}
*/
}

bool FontCache::load(const std::string & name, const std::string & face, unsigned int size)
{
	boost::shared_ptr<Font2D> font(new Font2D(face, size));
	if (!font->build())
		return false;
	_fonts[name] = font;
	return true;
}

boost::shared_ptr<Font2D> FontCache::get(const std::string & name)
{
	std::map<std::string, boost::shared_ptr<Font2D> >::iterator it = _fonts.find(name);
	boost::shared_ptr<Font2D> font;
	if (it != _fonts.end())
		font = it->second;
	return font;
}

