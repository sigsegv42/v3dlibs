#include "FileLog.h"

using namespace v3D;

FileLog::FileLog(const std::wstring & filename)
{
	logName_ = filename;
	open();
}

FileLog::~FileLog()
{
	close();
}


bool FileLog::open()
{
	handle_.open(logName_.c_str(), std::ios_base::out | std::ios_base::app);

	return true;
}

bool FileLog::close()
{
	handle_.close();
	return true;
}


void FileLog::write(const std::string & line)
{
	handle_ << line << std::endl;
}

