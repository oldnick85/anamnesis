#ifndef CTESTDIGITNUMBERSTR_H
#define CTESTDIGITNUMBERSTR_H

#include "ctestcase.h"
/*!
 * \brief CTestDigitNumberStr - тест строковых функций для многоразрядных чисел
 */
class CTestDigitNumberStr
        : public CTestCase
{
public:
	CTestDigitNumberStr() = default;
    /*!
     * \brief Test - запуск теста
     * \param[out] test_perf - сюда будут записаны данные о производительности
     * \return успех теста
     */
	virtual bool Test(sTestPerformance &test_perf) override final;
};

#endif // CTESTDIGITNUMBERSTR_H
