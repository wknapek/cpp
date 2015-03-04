#ifndef INFOCOLLECTOR_H
#define INFOCOLLECTOR_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/filesystem.hpp>

class infocollector
{
    long int resault;
    long int upData;
    long int downData;
    long int tmpDownData;
    bool m_bfileExist;
    bool m_blastmonth;
    std::string strTimeStamp;
    std::string strFileName;
    std::vector<boost::filesystem::path> interfaces;
    std::string endOfPathD = "/statistics/rx_bytes";
    std::string endOfPathU = "/statistics/tx_bytes";
    std::ifstream DataFile;
    std::string TimeFromFile;
    struct tm timeNow;
public:
    infocollector();
    ~infocollector();
    bool GetData();
    void analizer();
    bool GetTimeStamp();
    bool GetTimeAndDataFromFile();//to przetestowac
    bool WriteDataAndTimeToFile();
    int  CompareTime(std::string strTime);
};

#endif // INFOCOLLECTOR_H
