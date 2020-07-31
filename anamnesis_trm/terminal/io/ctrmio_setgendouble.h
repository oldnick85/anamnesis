#ifndef CTRMIO_SETGENDOUBLE_H
#define CTRMIO_SETGENDOUBLE_H

#include "common.h"
#include "../select/result/result.h"

/*!
 * \brief CTrmIO_SetgenDouble - класс обработки строк ввода-вывода для двойного генератора вариантов
 */
class CTrmIO_SetgenDouble
{
public:
    CTrmIO_SetgenDouble() = default;
    ~CTrmIO_SetgenDouble() = default;
protected:
    /*!
     * \brief ParseSample - распарсить введённую строку
     * \param[in] str - строка для парсинга
     * \param[out] value - сгенерированное значение
     * \return успех парсинга
     */
    Result_t ParseSample(const std::string &str, std::pair<uint64, uint64> &value) const;
};

#endif // CTRMIO_SETGENDOUBLE_H
