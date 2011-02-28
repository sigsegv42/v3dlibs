#ifndef INCLUDED_V3D_INPUTDEVICE
#define INCLUDED_V3D_INPUTDEVICE

namespace v3D
{


	class InputDevice
	{
		public:
			virtual ~InputDevice() { }

			virtual bool tick() = 0;
	};

}; // end namespace v3D

#endif // INCLUDED_V3D_INPUTDEVICE
