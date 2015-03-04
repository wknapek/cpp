#include "MySystemTools.h"
#include <ctime>
#include <fstream>

using namespace std;
using namespace boost::filesystem;

MySystemTool::MySystemTool()
{

}

MySystemTool::~MySystemTool()
{

}

bool MySystemTool::GetDirectoryFiles(string sDirPath)
{
	path wallDir(sDirPath);
	if(!exists(wallDir) || !is_directory(wallDir))
	{
		return false;
	}
	copy(directory_iterator(wallDir), directory_iterator(), back_inserter(sDirList));
	return true;
}


int MySystemTool::SetWallpaper()
{
	getSettings();
	srand(time(NULL));
	int iwallpnr = rand() % sDirList.size();
	string spath = sDirList.at(iwallpnr).string();
	spath.insert(0, "gsettings set org.mate.background picture-filename ");
	return system(spath.c_str());
}

bool MySystemTool::getSettings()
{
	ifstream settings("/home/cpp/wallch/bin/Debug/config.cfg");
	string   tmp;
	string   interpreter;
	bool 	 bret = true;
	while(getline(settings,interpreter))
	{
		if( interpreter.at(0) != '#')
		{
			tmp += interpreter + '\n';
		}
		else
		{
			interpreter.erase();
		}
	}
	sRootWallpeperPath = tmp.substr(0, sRootWallpeperPath.find('\n'));
	cout<<sRootWallpeperPath<<endl;
	iSleep = atoi(tmp.substr(sRootWallpeperPath.find('\n'),sRootWallpeperPath.rfind('\n')).c_str());
	cout<<iSleep<<endl;
	bret = true;
	return bret;
}
