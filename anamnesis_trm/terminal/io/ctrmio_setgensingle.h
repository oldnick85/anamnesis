#ifndef CTRMIO_SETGENSINGLE_H
#define CTRMIO_SETGENSINGLE_H

#include "common.h"
#include "../select/result/result.h"

/*!
 * \brief CTrmIO_SetgenSingle - класс обработки строк ввода-вывода для одиночного генератора вариантов
 */
class CTrmIO_SetgenSingle
{
public:
    CTrmIO_SetgenSingle() = default;
    ~CTrmIO_SetgenSingle() = default;
protected:
    /*!
     * \brief ParseSample - распарсить введённую строку
     * \param[in] str - строка для парсинга
     * \param[out] value - сгенерированное значение
     * \return успех парсинга
     */
    Result_t ParseSample(const std::string &str, uint64 &value) const;
};

#endif // CTRMIO_SETGENSINGLE_H
