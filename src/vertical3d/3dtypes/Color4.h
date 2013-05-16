#ifndef INCLUDED_V3D_COLOR4
#define INCLUDED_V3D_COLOR4

namespace v3D
{

	class Color4
	{
		public:
			typedef enum
			{
				RED = 0,
				GREEN,
				BLUE,
				ALPHA
			} Component;

			Color4();
			Color4(float r, float g, float b, float a);
			Color4(float * color);

			float operator [] (unsigned int index) const;

			void scale(float s);

		private:
			float data_[4];
	};


}; // end namespace v3D

#endif // INCLUDED_V3D_COLOR4
