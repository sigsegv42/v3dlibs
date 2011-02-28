#include "InputEventAdapter.h"

#include <boost/lexical_cast.hpp>

InputEventAdapter::InputEventAdapter(boost::shared_ptr<v3D::KeyboardDevice> kb, boost::shared_ptr<v3D::MouseDevice> mouse)
{
	if(kb)
		kb->addEventListener(this, "event_adapter");
	if (mouse)
		mouse->addEventListener(this, "event_adapter");
}

void InputEventAdapter::connect(v3D::EventListener * target)
{
	targets_.push_back(target);
}

void InputEventAdapter::dispatch(const v3D::EventInfo & info) const
{
	std::vector<v3D::EventListener * >::const_iterator iter = targets_.begin();
	for (; iter != targets_.end(); iter++)
	{
		(*iter)->notify(info);
	}
}

void InputEventAdapter::motion(unsigned int x, unsigned int y)
{
	std::string name = "mouse::";
	name += "motion";
	v3D::EventInfo e(name, v3D::EventInfo::MATCH_STATE_ANY);
	dispatch(e);
}

void InputEventAdapter::buttonPressed(unsigned int button)
{
	std::string name = "mouse::";
	name += "button_";
	name += boost::lexical_cast<std::string>(button);
	v3D::EventInfo e(name, v3D::EventInfo::MATCH_STATE_ON);
	dispatch(e);
}

void InputEventAdapter::buttonReleased(unsigned int button)
{
	std::string name = "mouse::";
	name += "button_";
	name += boost::lexical_cast<std::string>(button);
	v3D::EventInfo e(name, v3D::EventInfo::MATCH_STATE_OFF);
	dispatch(e);
}

void InputEventAdapter::keyPressed(const std::string & key)
{
	v3D::EventInfo e(key, v3D::EventInfo::MATCH_STATE_ON);
	dispatch(e);
}

void InputEventAdapter::keyReleased(const std::string & key)
{
	v3D::EventInfo e(key, v3D::EventInfo::MATCH_STATE_OFF);
	dispatch(e);
}
