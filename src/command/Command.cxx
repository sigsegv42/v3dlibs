#include "Command.h"

using namespace v3D;

Command::Command(const std::string & name, const std::string & scope, const CommandHandlerType::slot_function_type & slot) 
	: info_(name, scope)
{
	connection_ = handler_.connect(slot);
}

bool Command::operator == (const CommandInfo & cmd) const
{
	if (cmd == info_)
		return true;
	return false;
}

bool Command::exec(const std::string & param)
{
	bool result = handler_(info_, param);
	return result;
}

void Command::disconnect()
{
	if (!handler_.empty())
		connection_.disconnect();
}

void Command::enable()
{
	if (!handler_.empty())
		connection_.unblock();
}

void Command::disable()
{
	if (!handler_.empty())
		connection_.block();
}
