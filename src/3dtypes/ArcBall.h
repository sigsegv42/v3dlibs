#ifndef INCLUDED_V3D_ARCBALL
#define INCLUDED_V3D_ARCBALL

#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"

namespace v3D
{
	/**
	 * ArcBall camera rotation utility.
	 */
	class ArcBall
	{
		public:
			ArcBall();
			~ArcBall();

			void click(const Vector2 & point);
			Quaternion drag(const Vector2 & point);
			Vector3 map(const Vector2 & new_point);
			void bounds(float width, float height);

		private:	
			Vector3		start_;
			Vector3		end_;
			float		width_;
			float		height_;
	};

}; // end namespace v3D



#endif // INCLUDED_V3D_ARCBALL
