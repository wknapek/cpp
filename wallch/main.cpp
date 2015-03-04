#include <iostream>
#include "MySystemTools.h"

using namespace std;

int main()
{
	int iret = 0;
	MySystemTool test;
	test.GetDirectoryFiles("/home/tapety-NG");
	iret = test.SetWallpaper();
    return iret;
}
