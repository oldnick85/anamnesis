#ifndef CTRMIO_H
#define CTRMIO_H

#include <vector>
#include "common.h"

/*!
 * \brief CTrmIO - класс ввода-вывода терминала
 */
class CTrmIO
{
public:
    CTrmIO() = default;
    /*!
     * \brief InputStr - ввод строки
     * \param[out] str - сюда будет записана введённая строка
     * \param[in] dflt - значение по умолчанию
     * \return успех ввода
     */
    bool InputStr(std::string &str, const std::string dflt = "") const;
    /*!
     * \brief InputInt - ввод целого числа
     * \param[out] v - сюда будет записано введённое число
     * \param[in] dflt - значение по умолчанию
     * \return успех ввода
     */
    bool InputInt(int &v, const int dflt = -1) const;
    /*!
     * \brief InputVecInt - ввод нескольких целых чисел
     * \param[out] v - сюда будут записаны введённые числа
     * \param[in] dflt - значение по умолчанию
     * \return успех ввода
     */
    bool InputVecInt(std::vector<int> &v, const std::vector<int> dflt = {}) const;
    /*!
     * \brief ClearScreen - очистить терминал
     */
    void ClearScreen() const;
};

#endif // CTRMIO_H
