#ifndef INCLUDED_V3D_BREP_HALFEDGEBREP
#define INCLUDED_V3D_BREP_HALFEDGEBREP

#include "Vertex.h"
#include "HalfEdge.h"
#include "Face.h"

#include "../3dtypes/AABBox.h"

#include <boost/shared_ptr.hpp>
#include <vector>

namespace v3D
{

	class BRep
	{
		public:
			BRep();
			~BRep();

			static const unsigned int INVALID_ID;

			class edge_iterator
			{
				public:
					edge_iterator();
					edge_iterator(boost::shared_ptr<BRep> brep, unsigned int face);
					~edge_iterator();
		
					HalfEdge * operator * ();
					edge_iterator operator++ (int);
		
					void reset(boost::shared_ptr<BRep> brep, unsigned int face);
					boost::shared_ptr<BRep> brep(void) const;

				private:
					HalfEdge * edge_;
					unsigned int firstEdge_;
					boost::shared_ptr<BRep> brep_;
			};

			class vertex_iterator
			{
				public:
					vertex_iterator();
					vertex_iterator(boost::shared_ptr<BRep> brep, unsigned int face);
					~vertex_iterator();

					Vertex * operator * ();
					vertex_iterator operator++ (int);

					void reset(boost::shared_ptr<BRep> brep, unsigned int face);

				private:
					edge_iterator	iterator_;
			};

			HalfEdge * edge(unsigned int e);
			Face * face(unsigned int f);
			Vertex * vertex(unsigned int vert);

			AABBox bound(void) const;

			void addFace(const std::vector<Vector3> & vertices, const Vector3 & normal);
			void addEdge(const Vector3 & point);

			void splitEdge(unsigned int edge, const Vector3 & point);
			void extrudeFace(unsigned int face);
			void splitFace(unsigned int face, unsigned int leftEdge, unsigned int rightEdge, const Vector3 & leftPoint, const Vector3 & rightPoint);

			unsigned int vertexCount(void) const;
			unsigned int edgeCount(void) const;
			unsigned int faceCount(void) const;

			unsigned int addVertex(const Vertex & v);
			unsigned int addEdge(const HalfEdge & e);
			unsigned int addFace(const Face & f);

		protected:
			unsigned int addVertex(const Vector3 & v);
			unsigned int addEdge(unsigned int vertex);
			unsigned int findPair(unsigned int edge, unsigned int prevEdge);

		private:
			std::vector<Vertex> vertices_;
			std::vector<Face> faces_;
			std::vector<HalfEdge> edges_;
	};

	/**
	 * Get the mid point of the face of a mesh
	 * @param mesh the brep
	 * @param face the face number to get the center of
	 * @return the point located in the middle of the face
	 */
	Vector3 center(boost::shared_ptr<BRep> mesh, unsigned int face);
	/**
	 * Get the UV vectors for a mesh face
	 * @param mesh the mesh to use
	 * @param face the face number to get the coordinates for
	 * @param u the address of a vector to store the results in
	 * @param v the address of a vector to store the results in
	 */
	void faceUV(boost::shared_ptr<BRep> mesh, unsigned int face, Vector3 & u, Vector3 & v);

}; // end namespace v3D

#endif // INCLUDED_V3D_BREP_HALFEDGEBREP
