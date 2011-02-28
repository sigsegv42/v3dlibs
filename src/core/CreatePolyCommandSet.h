#ifndef INCLUDED_V3D_CREATEPOLYCOMMANDSET
#define INCLUDED_V3D_CREATEPOLYCOMMANDSET

#include <boost/shared_ptr.hpp>

namespace v3D
{
	class BRep;

	boost::shared_ptr<v3D::BRep> create_poly_cube();
	boost::shared_ptr<v3D::BRep> create_poly_plane();
	boost::shared_ptr<v3D::BRep> create_poly_cylinder();
	boost::shared_ptr<v3D::BRep> create_poly_cone();

}; // end namespace v3D

#endif // INCLUDED_V3D_CREATEPOLYCOMMANDSET
