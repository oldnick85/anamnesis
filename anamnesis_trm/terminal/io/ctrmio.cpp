#include <iostream>
#include <cstring>

#include "ctrmio.h"

bool CTrmIO::InputStr(std::string &str, const std::string dflt) const
{
    std::getline(std::cin, str);
    if (str.empty())
    {
        str = dflt;
        return false;
    }
    return true;
}

bool CTrmIO::InputInt(int &v, const int dflt) const
{
    std::string str;
    InputStr(str);
    try
    {
        v = std::stoi(str);
    }
    catch (...)
    {
        v = dflt;
        return false;
    }
    return true;
}

bool CTrmIO::InputVecInt(std::vector<int> &v, const std::vector<int> dflt) const
{
    v.clear();
    std::string str;
    InputStr(str);

    char s[256];
    strncpy(s, str.c_str(), sizeof(s));
    s[sizeof(s)-1] = 0;

    char *pch = strtok(s, " ,.;");
    while (pch != nullptr)
    {
        try
        {
            auto i = std::stoi(pch);
            v.push_back(i);
        }
        catch (...)
        {
            v = dflt;
            //return false;
        }
        pch = strtok(nullptr, " ,.;");
    }

    return true;
}

void CTrmIO::ClearScreen() const
{
    //int res;
    //res = system("cls");      // Windows
    //res = system("clear");      // POSIX
    //if (res != 0) printf("ERROR clearing screen");
}
