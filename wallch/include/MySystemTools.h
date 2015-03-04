#ifndef MYSYSTEMTOOL_H
#define MYSYSTEMTOOL_H


#include <vector>
#include <string>
#include <boost/filesystem.hpp>

class MySystemTool
{
	public:
		MySystemTool();
		~MySystemTool();
		bool GetDirectoryFiles(std::string sDirPath);
		int SetWallpaper();
	protected:
		bool getSettings();
		std::vector<boost::filesystem::path> sDirList; //list of wallpapers files
		std::string  						 sRootWallpeperPath;
		int 								 iSleep;
	private:
};

#endif // MYSYSTEMTOOL_H
