#ifndef CTRMIO_COMBINE_H
#define CTRMIO_COMBINE_H

#include "common.h"
#include "../select/result/result.h"

/*!
 * \brief CTrmIO_Combine - класс обработки строк ввода-вывода для комбинатора вариантов
 */
class CTrmIO_Combine
{
public:
    CTrmIO_Combine() = default;
    ~CTrmIO_Combine() = default;
protected:
    /*!
     * \brief ParseSamples - распарсить введённую строку на семплы
     * \param[in] str - строка для парсинга
     * \param[out] str_samples - список семплов
     * \return успех парсинга
     */
    Result_t ParseSamples(const std::string &str, std::list<std::string> &str_samples) const;
};

#endif // CTRMIO_COMBINE_H
