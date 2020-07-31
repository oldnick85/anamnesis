#ifndef CDIGITNUMBER_H
#define CDIGITNUMBER_H

#include "list"
#include "cnumber.h"

/**
 * @brief CDigitNumber - число, представленное в виде набора цифр, каждая в своей системе счисления
 */
class CDigitNumber
{
public:
    CDigitNumber() = default;

    /**
     * @brief sDigit - разряд числа, цифра в определённой системе счисления
     */
    struct sDigit
    {
        /*!
     * \brief Valid - предикат валидности
     * \return валидность разряда
     */
        bool Valid() const
        {
            return ((base > 0) and (base > num));
        }
        /*!
     * \brief PrintHex - вывод в строку
     * \return строка, описывающая разряд
     */
        std::string PrintHex() const
        {
            std::string str;
            str = "[" + num.PrintBin() + ":" + base.PrintBin() + "]";
            return str;
        }
        /*!
     * \brief FromHex - ввод из строки
     * \param[in,out] str - строка с текстовым представлением разряда
     * \return успех парсинга
     * \remark будет принято первое найденное значение и вырезано из строки
     */
        bool FromHex(std::string &str)
        {
            if (str.empty()) return false;
            auto first_brace = str.find('[');
            if (first_brace == std::string::npos) return false;
            auto second_brace = str.find(']');
            if (second_brace == std::string::npos) return false;
            if (first_brace >= second_brace) return false;
            std::string dg_str = str.substr(first_brace + 1, second_brace - first_brace - 1);
            if (dg_str.empty()) return false;
            str.erase(first_brace + 1, second_brace - first_brace - 1);

            return true;
        }

        CNumber		num;            ///< значение разряда
        CNumber		base;           ///< основание разряда
    };

    /*!
     * \brief AddDigit - добавить разряд в число
     * \param[in] digit
     * \return успех добавления
     * \remark разряд добавляется спереди
     */
    bool AddDigit(const sDigit &digit);
    /*!
     * \brief Clear - чистить число
     */
    void Clear();
    /*!
     * \brief GetNumber - получить значение многоразрядного числа в длинной арифметике
     * \return длинное число
     */
    CNumber GetNumber() const;
    /*!
     * \brief PrintHex - вывести в шестнадцатеричном виде
     * \return строка с шестнадцатеричным представлением
     */
    std::string PrintHex() const;
    /*!
     * \brief FromHex - считать из шестнадцатеричного вида
     * \param[in] str - строка с шестнадцатеричным представлением
     * \return успех парсинга
     */
    bool FromHex(const std::string str);

private:
    std::list<sDigit>	m_digits;
};

#endif // CDIGITNUMBER_H
