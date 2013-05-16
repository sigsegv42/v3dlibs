#ifndef INCLUDED_V3D_BREP_HALFEDGE
#define INCLUDED_V3D_BREP_HALFEDGE

namespace v3D
{

	class HalfEdge
	{
		public:
			HalfEdge();
			HalfEdge(unsigned int vert);
			HalfEdge(const HalfEdge & e);
			~HalfEdge();

			bool operator == (const HalfEdge & e);
			HalfEdge & operator = (const HalfEdge & e);

			unsigned int vertex(void) const;
			unsigned int face(void) const;
			unsigned int pair(void) const;
			unsigned int next(void) const;

			void vertex(unsigned int vert);
			void face(unsigned int f);
			void pair(unsigned int e);
			void next(unsigned int e);

		private:
			unsigned int	vertex_;	// vertex at end of half edge
			unsigned int	face_;	// face to left of edge
			unsigned int	pair_;	// symetric half edge
			unsigned int	next_;	// next CCW half edge 
	};

}; // end namespace v3D

#endif // INCLUDED_V3D_BREP_HALFEDGE
