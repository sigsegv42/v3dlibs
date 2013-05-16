#ifndef INCLUDED_V3D_BREP_VERTEX
#define INCLUDED_V3D_BREP_VERTEX

#include "../3dtypes/Vector3.h"

namespace v3D
{

	class Vertex
	{
		public:
			Vertex();
			Vertex(const Vector3 & p);
			~Vertex();

			bool operator == (const Vertex & v);
			bool operator == (const Vector3 & v);

			unsigned int edge(void) const;
			void edge(unsigned int e);
			Vector3 point(void) const;
			void point(const Vector3 & p);

		private:
			Vector3	point_;
			unsigned int edge_;
	};

}; // end namespace v3D

#endif // INCLUDED_V3D_BREP_VERTEX
