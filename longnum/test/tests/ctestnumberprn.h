#ifndef CTESTPRINT_H
#define CTESTPRINT_H

#include "ctestcase.h"

/**
 * @brief CTestNumberPrn - тестирование строковых функций
 */
class CTestNumberPrn
		: public CTestCase
{
public:
	CTestNumberPrn() = default;
	virtual bool Test(sTestPerformance &test_perf) override final;
};

#endif // CTESTPRINT_H
