#include "BindLoader.h"

using namespace v3D;

bool utility::load_binds(const PropertyTree & tree, CommandDirectory * directory)
{
	const PropertyTree & binds = tree.find("config.keys");

	// <bind event="w" scope="pong" command="leftPaddleUp" param="value" catch="any" />
	std::string event_name, command, val, scope, param;
	EventInfo::MatchState flag = EventInfo::MATCH_STATE_NONE;
	PropertyTree::const_iterator iter = binds.begin();
	for ( ; iter != binds.end(); iter++)
	{
		event_name = iter->get("<xmlattr>.event");
		command = iter->get("<xmlattr>.command");
		scope = iter->get("<xmlattr>.scope");
		val = iter->get("<xmlattr>.catch");
		param = iter->get("<xmlattr>.param");

		if (val == "on")
			flag = EventInfo::MATCH_STATE_ON;
		else if (val == "off")
			flag = EventInfo::MATCH_STATE_OFF;
		else if (val == "any")
			flag = EventInfo::MATCH_STATE_ANY;

		directory->bind(EventInfo(event_name, flag), 
						CommandInfo(command, scope), param);
	}
	return true;
}
