#ifndef INCLUDED_V3D_SCENE
#define INCLUDED_V3D_SCENE

#include "../3dtypes/CameraProfile.h"
#include "../3dtypes/Camera.h"

#include <vector>
#include <boost/shared_ptr.hpp>

namespace v3D
{

	class BRep;
	class SceneVisitor;

	/**
	 *	The Scene class.
	 *	The scene traditionally represents the root of a scene graph type structure. In a component based design
	 *  it might make sense that the scene represents more of a database type structure instead. The interface for
	 *  the scene might then be methods for performing queries on the database - e.g. adding new component nodes,
	 *  selecting existing component nodes, deleting component nodes, updating component nodes (Updating might not 
	 *  be a required action since nodes can be updated directly after they are selected). It might also be possible
	 *  to replace the selection concept with the visitor pattern instead - the action visits the object instead.
	 *  
	 *	A scene stores a collection of nodes
	 *		geometry (meshes, curves ...) or shape nodes
	 *		cameras
	 *		lights
	 *		groups
	 */
	class Scene
	{
		public:
			/*
			   allow storing raw meshes temporarily. this might eventually use something 
			   like a ShapeNode that can be inserted with a generic addNode method.
			*/
			void addBRep(const boost::shared_ptr<BRep> & brep);
			/*
				similar to the addBRep method but for camera profiles. except instead of a shape node
				this might be for something called e.g. a TemplateNode. 
			*/
			void addCameraProfile(const CameraProfile & profile);

			/**
			 * Accept a scene visitor to iterate over the scene
			 * @param visitor a pointer to the scene visitor
			 */
			void accept(SceneVisitor * visitor);

		private:
			std::vector< boost::shared_ptr<BRep> >	meshes_;
			std::vector< boost::shared_ptr<Camera> > cameras_;
			std::vector<CameraProfile> cameraProfiles_;
	};

}; // end namespace v3D

#endif // INCLUDED_V3D_SCENE
