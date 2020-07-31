#include "ctrmio_setgendouble.h"

Result_t CTrmIO_SetgenDouble::ParseSample(const std::string &str, std::pair<uint64, uint64> &value) const
{
    if (str.empty())
        return Result_t(RES_EMPTY_STRING);
    auto delim_pos = str.find(':');
    if (delim_pos == std::string::npos)
        return Result_t(RES_NO_DELIMETER);
    if (delim_pos == 0)
        return Result_t(RES_NO_VALUE_IN_TOKEN, 1);
    if (delim_pos == str.size()-1)
        return Result_t(RES_NO_VALUE_IN_TOKEN, 2);

    auto str1 = str.substr(0, delim_pos);
    auto val1 = static_cast<uint64>(std::stoi(str1));
    value.first = val1;

    auto str2 = str.substr(delim_pos+1);
    auto val2 = static_cast<uint64>(std::stoi(str2));
    value.second = val2;

    return Result_t(RES_OK);
}
