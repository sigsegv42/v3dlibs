#ifndef INCLUDED_V3D_EVENTLISTENER
#define INCLUDED_V3D_EVENTLISTENER

#include "EventInfo.h"

namespace v3D
{

	/** 
	 * An Abstract Base Class for any derived class which wants to listen and
	 * be notified of events.
	 */
	class EventListener
	{
		public:
			virtual ~EventListener() { }

			/**
			 * Event notification method.
			 * @param e the event that has occurred.
			 */
			virtual void notify(const EventInfo & e) = 0;

	};

}; // end namespace v3D

#endif // INCLUDED_V3D_EVENTLISTENER
