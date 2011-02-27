#ifndef INCLUDED_V3D_COLOR3
#define INCLUDED_V3D_COLOR3

namespace v3D
{

	/**
	 * A 3 component color class.
	 */
	class Color3
	{
		public:

			/**
			 * Color component enumeration
			 */
			typedef enum
			{
				RED = 0,	/**< red component **/
				GREEN,		/**< green component **/
				BLUE		/**< blue component **/
			} Component;

			Color3();
			Color3(float val);
			Color3(float r, float g, float b);
			
			Color3 & operator = (const Color3 & c);
			Color3 & operator += (const Color3 & c);
			float operator [] (unsigned int i) const;
			float & operator[](unsigned int i);

		private:
			float data_[3];
	};

	const Color3 operator * (const Color3 & lhs, float f);
	const Color3 operator / (const Color3 & lhs, float f);
	const Color3 operator + (const Color3 & lhs, const Color3 & rhs);
	const Color3 operator - (const Color3 & lhs, const Color3 & rhs);

}; // end namespace v3D

#endif // INCLUDED_V3D_COLOR3
