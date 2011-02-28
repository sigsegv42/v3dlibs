#ifndef INCLUDED_V3D_SCENEVISITOR
#define INCLUDED_V3D_SCENEVISITOR

#include <boost/shared_ptr.hpp>

namespace v3D
{

	class BRep;

	/**
	 * The interface for a scene visitor.
	 * Visitors may be interested in certain kinds of nodes within a scene database.
	 */
	class SceneVisitor
	{
		public:
			/*
			a generic version my specify a bunch of node types (or the types might be specified somewhere else) with pow2
			values that can be combined into a single flag value:

			typedef enum NodeType { MESH_SHAPE_NODE = 1, LIGHT_NODE = 2, CAMERA_NODE = 4 } NodeType;

			with a constructor that specifies what kind of nodes this visitor wants to visit:
			SceneVisitor(unsigned int nodeFlags);

			and a generic visit method:
			virtual void visit(const boost::shared_ptr<ComponentNode> & node) = 0;

			specific visitors can be derived, implementing whatever functionality they require.
			*/
			virtual ~SceneVisitor() { }

			virtual void visit(const boost::shared_ptr<BRep> & mesh) = 0;
	};


}; // end namespace v3D

#endif // INCLUDED_V3D_SCENEVISITOR
