#ifndef INCLUDED_V3D_VECTOR2
#define INCLUDED_V3D_VECTOR2

#ifndef USE_TEMPLATE_VECTOR

namespace v3D
{

	class Vector2
	{
		public:
			Vector2();
			Vector2(float x, float y);

			Vector2 & operator += (const Vector2 & v);
			Vector2 & operator -= (const Vector2 & v);
			Vector2 & operator *= (float f);

			Vector2 operator - () const;

			bool operator == (const Vector2 & v);

			float operator[](unsigned int i) const;
			float & operator[](unsigned int i);

		private:
			float vec_[2];
	};

}; // end namespace v3D

#endif 

#endif  // INCLUDED_V3D_VECTOR2
