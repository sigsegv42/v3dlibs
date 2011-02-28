#ifndef INCLUDED_V3D_FILE_LOG
#define INCLUDED_V3D_FILE_LOG

#include <string>
#include <fstream>

namespace v3D
{

	class FileLog  
	{
		public:
			FileLog(const std::wstring & filename);
			virtual ~FileLog();

			void write(const std::string & line);

		protected:
			bool open();
			bool close();

		protected:
			std::wstring	logName_;
			std::ofstream	handle_;
	};

}; // end namespace v3D

#endif // INCLUDED_V3D_FILE_LOG
