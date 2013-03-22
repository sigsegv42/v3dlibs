#ifndef INCLUDED_V3D_CAMERA
#define INCLUDED_V3D_CAMERA

#include "CameraProfile.h"

namespace v3D
{

	/**
	 *	A 3D viewing camera.
	 */
	class Camera
	{
		public:
			Camera();
			Camera(const CameraProfile & profile);
			virtual ~Camera();

			// get
			Matrix4	projection() const;
			Matrix4 view() const;

			/**
			 * Access the underlying camera profile
			 */
			CameraProfile & profile();

			Vector3 unproject(const Vector3 & point, int viewport[4]);
			Vector3 project(const Vector3 & point, int viewport[4]);

			/**
			 *	Create a projection matrix.
			 *	The resulting matrix can be retrieved by calling projection().
			 *	If the camera is set to orthographic then an orthographic projection will be created.
			 *	Otherwise a perspective projection will be used.
			 */
			void createProjection();
			/**
			 *	Create a viewing matrix.
			 *	The resulting matrix can be retrieved by calling view().
			 *	The viewing matrix contains the translation and rotation portion of  the 
			 *	camera transformation.
			 */
			void createView();

			// transformations
			/*
				dolly, truck, pedestal are types of translations with special restrictions
				pan and tilt are types of rotation with restrictions
			*/
			/**
			 *	Pan the camera.
			 *	Move horizontally around a fixed axis (the camera's y axis) - camera 
			 *	rotation & look at position changes but eye position doesn't - look left/right
			 */
			void pan(float angle);
			/**
			 *	Tilt the camera.
			 *	Move vertically around a fixed axis (camera's x axis) - look up/down
			 */
			void tilt(float angle);
			/**
			 *	Dolly the camera.
			 *	Move eye forward or backward along direction of view
			 *	same as pedestal but use direction vector instead of up vector
			 */
			void dolly(float d);
			/**
			 *	Truck the camera.
			 *	Move eye on axis perpendicular to direction of view and up axis - move 
			 *	left/right multiply delta value and right vector to get eye delta - 
			 *	right vector must be normalized - add eye delta to current eye position
			 */
			void truck(float d);
			/**
			 *	Zoom the camera.
			 *	Affects the camera lens to zoom in or out (dolly without moving camera)
			 */
			void zoom(float z);
			/**
			 *	Pedestal the camera.
			 *	Move eye on up axis - move up/down
			 *	same as truck but use up vector instead of right vector
			 */
			void pedestal(float d);

			bool orthographic() const;
			void orthographic(bool ortho);
			float orthoFactor();
			/**
			*	Rotate the camera by a given amount.
			*	The rotation tells how to transform the camera into the same space 
			*	defined by its normals. The normals are the up, right, and direction
			*	vectors. The default coordinate system with no rotation is a right-
			*	handed system with right +x, up +y, and direction +z.
			*	@param new_rot the new rotation value.
			*/
			void rotate(const Quaternion & new_rot);

		private:
			Vector3		lookAt_;
			Matrix4		projection_;
			Matrix4		view_;			// viewing transformation
			CameraProfile profile_;
	};

}; // end namespace v3D

#endif // INCLUDED_V3D_CAMERA
