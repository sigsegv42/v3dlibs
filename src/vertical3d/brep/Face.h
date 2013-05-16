#ifndef INCLUDED_V3D_BREP_FACE
#define INCLUDED_V3D_BREP_FACE

#include "../3dtypes/Vector3.h"

namespace v3D
{

	class Face
	{
		public:
			Face();
			Face(const Vector3 & normal, unsigned int edge);
			~Face();

			/*
			bool selected(void) const;
			void selected(bool sel);
			*/

			Vector3 normal(void) const;
			void normal(const Vector3 & n);
			unsigned int edge(void) const;
			void edge(unsigned int e);

		private:
			Vector3	normal_;
			unsigned int edge_;
	};

}; // end namespace v3D

#endif // INCLUDED_V3D_BREP_FACE
