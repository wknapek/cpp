#include "infocollector.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <ctime>
#include <time.h>
#include <math.h>

using namespace std;
using namespace boost::filesystem;


infocollector::infocollector()
{
    strFileName = "netstat.ini";
    resault = 0;
    TimeFromFile = "";
    tmpDownData = 0;

    if(boost::filesystem::exists( strFileName ) )
    {
        DataFile.open(strFileName);
        m_bfileExist = true;
        GetTimeAndDataFromFile();
    }
    else
    {
        m_bfileExist = false;
    }
}

///////////////////////////////////////////////////////////////////
/// \brief infocollector::GetData
/// \return
//////////////////////////////////////////////////////////////////
infocollector::~infocollector()
{
    WriteDataAndTimeToFile();
}

bool infocollector::GetData()
{
    path netDir("/sys/class/net");
    FILE *output;
    GetTimeStamp();
    string filepath;
    char chValue[500];
    for(directory_iterator it(netDir); it != directory_iterator() ; ++it)
    {
       if(it->path().filename().string().find("lo") == string::npos)
       {
            interfaces.push_back(*it);
       }
    }
    for(unsigned int iter = 0; iter < interfaces.size(); ++iter)
    {
        filepath = "cat /sys/class/net/" + interfaces.at(iter).filename().string() + endOfPathD;
        output = popen(filepath.c_str(), "r");
        if(output != NULL)
        {
            fread(chValue, 500, 1, output);
            downData = stod(chValue);
            downData = ceil( downData/1048576 );
        }
        else
        {
            return false;
        }
        chValue[0] = 0;
        filepath.clear();
        filepath = "cat /sys/class/net/" + interfaces.at(iter).filename().string() + endOfPathU;
        output = popen(filepath.c_str(), "r");
        if(output != NULL)
        {
            fread(chValue, 500, 1, output);
            upData = stoi(chValue);
            upData = upData/1048576;
        }
        else
        {
            return false;
        }
    }
    return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////

void infocollector::analizer()
{
    m_blastmonth = CompareTime(TimeFromFile);
    GetData();
    if(m_blastmonth)
    {
        tmpDownData = resault + downData;
    }
    else
    {
        tmpDownData = downData;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////
/// \brief infocollector::GetTimeStamp
/// \return
////////////////////////////////////////////////////////////////////////////////////////////

bool infocollector::GetTimeStamp()
{
    time_t now = time(0);
    struct tm *localStamp = localtime(&now);
    strTimeStamp = "#" +  to_string(localStamp->tm_mday);
    strTimeStamp += ":" + to_string(localStamp->tm_mon + 1);
    strTimeStamp += ":" + to_string(localStamp->tm_year - 100 );// if no then yer = eg. 114
    timeNow = *localStamp;
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////
/// \brief infocollector::CompareTime
/// \param strTime
/// \return
////////////////////////////////////////////////////////////////////////////////////////////

int infocollector::CompareTime(string strTime)
{
    struct tm time;
    strptime(strTime.c_str(), "%d:%m:%y", &time);
    GetTimeStamp();
    if(timeNow.tm_year > time.tm_year)
    {
        return 0;
    }
    else
    {
        if(timeNow.tm_mon > time.tm_mon )
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }

}

////////////////////////////////////////////////////////////////////////////////////////////
/// \brief infocollector::GetTimeAndDataFromFile
/// \return
////////////////////////////////////////////////////////////////////////////////////////////

bool infocollector::GetTimeAndDataFromFile()
{
    if(!m_bfileExist)
    {
        return false;
    }
    string line;
    string strdata;
    strdata.empty();
    line.empty();
    //bool lock = false;
    while(getline(DataFile, line))
    {
        strdata += line + "|";
    }
    cout<<strdata;
    int begPos = strdata.rfind("#");
    int endPos = strdata.find("|",begPos);
    string data = strdata.substr(begPos + 1,endPos - begPos - 1);
    begPos = endPos;
    TimeFromFile = data;
    int test = strdata.length() - begPos;
    string value = strdata.substr(begPos + 1,test - 2);
    cout<<value;
    long int DownloadValFromFile = stoi(value);
    resault += DownloadValFromFile; //to zrbić dodawanie pobrania do głównego

    strdata.empty();
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////
/// \brief infocollector::WriteDataAndTimeToFile
/// \return
//////////////////////////////////////////////////////////////////////////////////////////

bool infocollector::WriteDataAndTimeToFile()
{
    GetTimeStamp();
    ofstream FileData(strFileName, std::ios_base::app);
    FileData<< + "#" + strTimeStamp + "\n" + to_string(tmpDownData) + "\n";
    FileData.close();
    return true;
}
