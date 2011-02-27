#include "Bind.h"

using namespace v3D;

Bind::Bind(const EventInfo & evnt, const CommandInfo & command, const std::string & param) : 
	command_(command), 
	event_(evnt), 
	param_(param)
{
}


bool Bind::operator == (const EventInfo & e) const
{
	if (event_ == e)
		return true;
	return false;
}

CommandInfo Bind::command() const
{
	return command_;
}

EventInfo Bind::event() const
{
	return event_;
}

std::string Bind::param() const
{
	return param_;
}
