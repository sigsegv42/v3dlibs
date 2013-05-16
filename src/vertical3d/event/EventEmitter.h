/**
 * (c) Joshua Farr <j.wgasa@gmail.com>
 */

#pragma once

#include "EventInfo.h"

#include <boost/shared_ptr.hpp>
#include <vector>
#include <list>

namespace v3D
{

	class EventListener;

	class EventEmitter
	{
		public:
			void on(const EventInfo & ev, boost::shared_ptr<EventListener> listener);
			void addListener(const EventInfo & ev, boost::shared_ptr<EventListener> listener);
			void removeListener(const EventInfo & ev, boost::shared_ptr<EventListener> listener);
			void once(const EventInfo & ev, boost::shared_ptr<EventListener> listener);

			void emit(EventInfo e);

		private:
			std::list< std::pair< EventInfo, std::vector< boost::shared_ptr<EventListener> > > > listeners_;
	};


};