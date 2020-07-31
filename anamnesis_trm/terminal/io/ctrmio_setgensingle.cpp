#include "ctrmio_setgensingle.h"

Result_t CTrmIO_SetgenSingle::ParseSample(const std::string &str, uint64 &value) const
{
    if (str.empty())
        return Result_t(RES_EMPTY_STRING);
    value = static_cast<uint64>(std::stoi(str));
    return Result_t(RES_OK);
}
