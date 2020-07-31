#ifndef CNUMBER_H
#define CNUMBER_H

#include <list>
#include <stdint.h>
#include <string>

using uint = unsigned int;
using uint32 = uint32_t;
using uint64 = uint64_t;

/*!
 * CNumber - класс числа для длинной арифметики
 */
class CNumber
{
public:
	CNumber() = default;
    /*!
     * \brief CNumber - конструктор из целого числа
     * \param[in] n - целое инициирующее число
     */
    CNumber(const uint64 n) {FromUint(n);}
    /*!
     * \brief PushDigitRight - вставка двоичного разряда справа
     * \param[in] d - двоичный разряд
     */
    void PushDigitRight(const bool d);
    /*!
     * \brief PushDigitRight - вставка двоичного разряда слева
     * \param[in] d - двоичный разряд
     */
    void PushDigitLeft(const bool d);
    /*!
     * \brief PopDigitRight - вырезать двоичный разряд справа
     * \return двоичный разряд
     */
    uint PopDigitRight();
    /*!
     * \brief PopDigitLeft - вырезать двоичный разряд слева
     * \return двоичный разряд
     */
    uint PopDigitLeft();
    /*!
     * \brief operator << - поразрядный сдвиг влево
     * \param[in] rhs - на сколько разрядов сдвигать
     * \return результат сдвига
     */
    const CNumber operator<<(const uint rhs) const;
    /*!
     * \brief operator >> - поразрядный сдвиг вправо
     * \param[in] rhs - на сколько разрядов сдвигать
     * \return результат сдвига
     */
    const CNumber operator>>(const uint rhs) const;
    /*!
     * \brief operator <<= - поразрядный сдвиг влево с присвоением
     * \param[in] rhs - на сколько разрядов сдвигать
     * \return результат сдвига
     */
    CNumber& operator<<=(const uint rhs);
    /*!
     * \brief operator >>= - поразрядный сдвиг вправо с присвоением
     * \param[in] rhs - на сколько разрядов сдвигать
     * \return результат сдвига
     */
    CNumber& operator>>=(const uint rhs);
    /*!
     * \brief operator += - сложение с присвоением
     * \param[in] right - второе слагаемое
     * \return результат сложения
     */
	CNumber& operator+=(const CNumber& right);
    /*!
     * \brief operator + - сложение
     * \param[in] rv - второе слагаемое
     * \return результат сложения
     */
	const CNumber operator+(const CNumber& rv) const;
    /*!
     * \brief operator -= - вычитание с присвоением
     * \param[in] right - вычитаемое
     * \return результат вычитания
     */
    CNumber& operator-=(const CNumber& right);
    /*!
     * \brief operator - вычитание
     * \param[in] rv - вычитаемое
     * \return результат вычитания
     */
    const CNumber operator-(const CNumber& rv) const;
    /*!
     * \brief operator *= - умножение с присвоением
     * \param[in] rv - второй сомножитель
     * \return результат умножения
     */
	CNumber& operator*=(const CNumber& rv);
    /*!
     * \brief operator * - умножение
     * \param[in] rv - второй сомножитель
     * \return результат умножения
     */
	const CNumber operator*(const CNumber& rv) const;
    /*!
     * \brief operator /= - деление с присвоением
     * \param[in] rv - делитель
     * \return результат деления
     */
    CNumber& operator/=(const CNumber& rv);
    /*!
     * \brief operator / - деление
     * \param[in] rv - делитель
     * \return результат деления
     */
    const CNumber operator/(const CNumber& rv) const;
    /*!
     * \brief operator %= - остаток от деления с присвоением
     * \param[in] rv - делитель
     * \return остаток от деления
     */
    CNumber& operator%=(const CNumber& rv);
    /*!
     * \brief operator % -  остаток от деления
     * \param[in] rv - делитель
     * \return остаток от деления
     */
    const CNumber operator%(const CNumber& rv) const;
    /**
     * @brief Divide - деление с остатком
     * @param[in] divider - делитель
     * @return пара: результат и остаток от деления
     */
    std::pair<CNumber, CNumber> Divide(const CNumber &divider);
    /*!
     * \brief operator == - равно
     * \param[in] rhs - сравниваемое значение
     * \return результат сравнения
     */
	bool operator==(const CNumber& rhs) const;
    /*!
     * \brief operator != - не равно
     * \param[in] rhs - сравниваемое значение
     * \return результат сравнения
     */
	bool operator!=(const CNumber& rhs) const;
    /*!
     * \brief operator < меньше
     * \param[in] rhs - сравниваемое значение
     * \return результат сравнения
     */
	bool operator<(const CNumber& rhs) const;
    /*!
     * \brief operator > - больше
     * \param[in] rhs - сравниваемое значение
     * \return результат сравнения
     */
	bool operator>(const CNumber& rhs) const;
    /*!
     * \brief operator <= - меньше или равно
     * \param[in] rhs - сравниваемое значение
     * \return результат сравнения
     */
    bool operator<=(const CNumber& rhs) const;
    /*!
     * \brief operator >= - больше или равно
     * \param[in] rhs - сравниваемое значение
     * \return результат сравнения
     */
    bool operator>=(const CNumber& rhs) const;
    /*!
     * \brief operator ^= - побитовый xor с присвоением
     * \param[in] rv - второй операнд
     * \return результат побитовой операции
     */
	CNumber& operator^=(const CNumber& rv);
    /*!
     * \brief operator ^ - побитовый xor
     * \param[in] rhs - второй операнд
     * \return результат побитовой операции
     */
	const CNumber operator^(const CNumber& rhs) const;
    /*!
     * \brief operator &= - побитовый and с присвоением
     * \param[in] rv - второй операнд
     * \return результат побитовой операции
     */
    CNumber& operator &=(const CNumber& rv);
    /*!
     * \brief operator & - побитовый and
     * \param[in] rhs - второй операнд
     * \return результат побитовой операции
     */
	const CNumber operator&(const CNumber& rhs) const;
    /*!
     * \brief operator |= - побитовый or с присвоением
     * \param[in] rv - второй операнд
     * \return результат побитовой операции
     */
	CNumber& operator|=(const CNumber& rv);
    /*!
     * \brief operator | - побитовый or
     * \param[in] rhs - второй операнд
     * \return результат побитовой операции
     */
	const CNumber operator|(const CNumber& rhs) const;
    /*!
     * \brief operator ++ - прединкремент
     * \return результат инкремента
     */
	CNumber& operator++();
    /*!
     * \brief operator ++ - постинкремент
     * \return значение до инкрементирования
     */
	CNumber operator++(int);
    /*!
     * \brief operator -- - преддекремент
     * \return результат декремента
     */
    CNumber& operator--();
    /*!
     * \brief operator -- - постдекремент
     * \return значение до декрементирования
     */
    CNumber operator--(int);
    /*!
     * \brief Factorial - факториал
     * \return значение факториала
     */
	CNumber Factorial() const;
    /*!
     * \brief ToUint64 - вывод в виде 64-битного числа
     * \return значение
     */
	uint64 ToUint64() const;
    /*!
     * \brief PrintBin - вывод в строку в двоичном виде
     * \return строка с числом
     */
	std::string PrintBin() const;
    /*!
     * \brief PrintDec - вывод в строку в десятичном виде
     * \return строка с числом
     */
    std::string PrintDec() const;
    /*!
     * \brief PrintHex - вывод в строку в шестнадцатеричном виде
     * \return строка с числом
     */
    std::string PrintHex() const;
    /*!
     * \brief Print - вывод в строку в заданной системе счисления
     * \param[in] base
     * \return строка с числом
     */
    std::string Print(const uint base) const;
    /*!
     * \brief FromStringBin - ввод из строки в двоичном виде
     * \param[in] str - строка с числом в двоичном виде
     * \return успех парсинга строки
     */
	bool FromStringBin(const std::string &str);
    /*!
     * \brief FromString - ввод из строки в заданной системе счисления
     * \param[in] str - строка с числом в заданной системе счисления
     * \param[in] base - основание системы счисления
     * \return успех парсинга строки
     */
	bool FromString(const std::string &str, const uint base);
    /*!
     * \brief BitsCount - количество бит, необходимых для представления числа
     * \return количество бит
     */
    uint64 BitsCount() const;
	
private:
    void FromUint(uint64 n);
	void TruncFirstZeros();
	
	std::list<uint>		m_binary;		///< список двоичных цифр числа (хранятся начиная с младшего разряда, т.е. младший разряд в list.begin)
};

#endif // CNUMBER_H
