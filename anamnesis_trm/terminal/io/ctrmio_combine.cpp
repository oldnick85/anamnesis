#include "ctrmio_combine.h"

#include <iostream>
#include <sstream>

Result_t CTrmIO_Combine::ParseSamples(const std::string &str, std::list<std::string> &str_samples) const
{
    if (str.empty())
        return Result_t(RES_EMPTY_STRING);

    str_samples.clear();
    std::stringstream str_stream(str);
    std::string token;
    while(getline(str_stream, token, ' '))
    {
        str_samples.push_back(token);
    }
    return Result_t(RES_OK);
}
