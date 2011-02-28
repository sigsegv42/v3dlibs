#ifndef INCLUDED_V3D_MOUSEEVENTLISTENER
#define INCLUDED_V3D_MOUSEEVENTLISTENER


namespace v3D
{

	/**
	 * An event listener for mouse events.
 	 */
	class MouseEventListener
	{
		public:
			virtual ~MouseEventListener() { }

			virtual void motion(unsigned int x, unsigned int y) = 0;
			virtual void buttonPressed(unsigned int button) = 0;
			virtual void buttonReleased(unsigned int button) = 0;
	};


}; // end namespace v3D


#endif // INCLUDED_V3D_MOUSEEVENTLISTENER
